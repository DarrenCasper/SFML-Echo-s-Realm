#include "Game_State.h"
#include <iostream>
#include "Cloud.hpp"
#include "RealmPlatform.hpp"
#include "DisappearPlatform.hpp"
#include "Realm.hpp"
#include "player.hpp"

Game_State::Game_State()
    : currentRealm(Realm::Light), rKeyPrev(false), gravity(0.5f)
{
    
    // Backgrounds
    if (!backgroundTexture1.loadFromFile("img/game_background_1/layers/rocks_2.png"))
        std::cerr << "Failed to load rocks_2.png" << std::endl;
    backgroundSprite1.setTexture(backgroundTexture1);

    if (!backgroundTexture2.loadFromFile("img/game_background_1/layers/sky.png"))
        std::cerr << "Failed to load sky.png" << std::endl;
    backgroundSprite2.setTexture(backgroundTexture2);

    if (!backgroundTexture3.loadFromFile("img/game_background_3/layers/ground_3.png"))
        std::cerr << "Failed to load ground_3.png" << std::endl;
    backgroundSprite3.setTexture(backgroundTexture3);

    if (!backgroundTexture4.loadFromFile("img/game_background_3/layers/sky.png"))
        std::cerr << "Failed to load sky.png" << std::endl;
    backgroundSprite4.setTexture(backgroundTexture4);

    // Decorations (clouds)
    decorations.emplace_back(std::make_unique<Cloud>("img/game_background_1/layers/clouds_2.png", sf::Vector2f(0, -250), 175.f));
    decorations.emplace_back(std::make_unique<Cloud>("img/game_background_1/layers/clouds_3.png", sf::Vector2f(500, -200), 200.f));
    decorations.emplace_back(std::make_unique<Cloud>("img/game_background_1/layers/clouds_2.png", sf::Vector2f(250, -250), 125.f));
    decorations.emplace_back(std::make_unique<Cloud>("img/game_background_1/layers/clouds_1.png", sf::Vector2f(750, -250), 150.f));

    // Platforms
    sf::RectangleShape platform1(sf::Vector2f(200.f, 20.f));
    platform1.setFillColor(sf::Color::White);
    platform1.setPosition(300.f, 700.f);
    platforms.push_back(new Platform(platform1.getSize(), platform1.getPosition(), platform1.getFillColor()));

    sf::RectangleShape platform2(sf::Vector2f(200.f, 20.f));
    platform2.setFillColor(sf::Color::White);
    platform2.setPosition(720.f, 620.f);
    platforms.push_back(new DisappearPlatform(platform2.getSize(), platform2.getPosition(), platform2.getFillColor(), 2.f, 3.f));

    sf::RectangleShape ground(sf::Vector2f(3000.f, 50.f));
    ground.setFillColor(sf::Color::White);
    ground.setPosition(0.f, 850.f);
    platforms.push_back(new Platform(ground.getSize(), ground.getPosition(), ground.getFillColor()));

    sf::RectangleShape realmPlat(sf::Vector2f(200.f, 20.f));
    realmPlat.setFillColor(sf::Color::White);
    realmPlat.setPosition(1000.f, 500.f);
    platforms.push_back(new RealmPlatform(realmPlat.getSize(), realmPlat.getPosition(), realmPlat.getFillColor(), Realm::Light));

    sf::RectangleShape realmPlat1(sf::Vector2f(200.f, 20.f));
    realmPlat1.setFillColor(sf::Color::White);
    realmPlat1.setPosition(1300.f, 500.f);
    platforms.push_back(new RealmPlatform(realmPlat1.getSize(), realmPlat1.getPosition(), realmPlat1.getFillColor(), Realm::Dark));

    
    view.setSize(1600.f, 900.f);
    view.setCenter(800.f, 450.f); 
}

Game_State::~Game_State() {
    for (auto* plat : platforms)
        delete plat;
}

void Game_State::handle_event(sf::Event event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
        if (!rKeyPrev) {
            currentRealm = (currentRealm == Realm::Light) ? Realm::Dark : Realm::Light;
        }
        rKeyPrev = true;
    } else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::R) {
        rKeyPrev = false;
    }
}

void Game_State::update() {
    float deltaTime = clock.restart().asSeconds();

    player.handleInput();
    player.update(deltaTime);
    player.checkCollision(platforms);
    
    // std::cout << "Player Position: (" << player.getPosition().x << ", " << player.getPosition().y << ")\n";
    // Debug Line (Previously used on gravity for delta time cuz player keep phasing)

    sf::Vector2f pos = player.getPosition();
    float playerWidth = player.getBounds().width;

    if (pos.x + playerWidth < 0)
        player.setPosition(1600, pos.y);
    else if (pos.x > 1600)
        player.setPosition(-playerWidth, pos.y);

    for (auto* plat : platforms)
        plat->update(deltaTime);
    for (auto* plat : platforms)
        plat->setRealm(currentRealm);

    for (auto& deco : decorations)
        deco->update(deltaTime);

    
}

void Game_State::render(sf::RenderWindow& window) {
    updateView(window, view);
    window.setView(view);

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u bgSize = (currentRealm == Realm::Light)
        ? backgroundTexture2.getSize()
        : backgroundTexture4.getSize();

    float scaleX = static_cast<float>(windowSize.x) / bgSize.x;
    float scaleY = static_cast<float>(windowSize.y) / bgSize.y;

    if (currentRealm == Realm::Light) {
        backgroundSprite2.setScale(scaleX, scaleY);
        backgroundSprite1.setScale(scaleX, scaleY);
        window.draw(backgroundSprite2);
        window.draw(backgroundSprite1);
    } else {
        backgroundSprite4.setScale(scaleX, scaleY);
        backgroundSprite3.setScale(scaleX, scaleY);
        window.draw(backgroundSprite4);
        window.draw(backgroundSprite3);
    }

    for (auto& deco : decorations)
        deco->draw(window);

    player.draw(window);

    for (auto* plat : platforms) {
        if (plat->isActive())
            plat->draw(window);
        else if (auto* realmPlat = dynamic_cast<RealmPlatform*>(plat))
            plat->drawGhost(window);
    }
}

int Game_State::get_next_state() {
    return GAME_STATE; // Stay in game; can later change to MENU_STATE etc.
}

void Game_State::updateView(sf::RenderWindow& window, sf::View& view) {
    const float ASPECT_RATIO = 16.f / 9.f;
    float width = static_cast<float>(window.getSize().x);
    float height = static_cast<float>(window.getSize().y);

    float windowRatio = width / height;
    float viewWidth = 1.f;
    float viewHeight = 1.f;
    float viewportX = 0.f;
    float viewportY = 0.f;

    if (windowRatio > ASPECT_RATIO) {
        viewWidth = ASPECT_RATIO / windowRatio;
        viewportX = (1.f - viewWidth) / 2.f;
    } else if (windowRatio < ASPECT_RATIO) {
        viewHeight = windowRatio / ASPECT_RATIO;
        viewportY = (1.f - viewHeight) / 2.f;
    }

    view.setViewport(sf::FloatRect(viewportX, viewportY, viewWidth, viewHeight));
}
