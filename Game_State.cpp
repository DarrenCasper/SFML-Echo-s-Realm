#include "Game_State.h"
#include <iostream>
#include "Cloud.hpp"
#include "RealmPlatform.hpp"
#include "DisappearPlatform.hpp"
#include "Realm.hpp"
#include "player.hpp"
#include "RealmObstacle.hpp"

Game_State::Game_State()
    : currentRealm(Realm::Light), rKeyPrev(false), gravity(0.5f)
{
    // Player Position
    player.setPosition(100.f, 700.f); // Ensure player starts at a valid
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
    platform1.setPosition(0.f, 600.f);
    platforms.push_back(new Platform(platform1.getSize(), platform1.getPosition(), platform1.getFillColor()));

    sf::RectangleShape platform3(sf::Vector2f(350.f, 20.f));
    platform3.setFillColor(sf::Color::White);
    platform3.setPosition(350.f, 600.f);
    platforms.push_back(new DisappearPlatform(platform3.getSize(), platform3.getPosition(), platform3.getFillColor(), 6.f, 3.f));

    sf::RectangleShape realmplatform4(sf::Vector2f(200.f, 20.f));
    realmplatform4.setFillColor(sf::Color::White);
    realmplatform4.setPosition(820.f, 600.f);
    platforms.push_back(new RealmPlatform(realmplatform4.getSize(), realmplatform4.getPosition(), realmplatform4.getFillColor(), Realm::Dark));

    sf::RectangleShape realmplatform5(sf::Vector2f(200.f, 20.f));
    realmplatform5.setFillColor(sf::Color::White);
    realmplatform5.setPosition(1150.f, 600.f);
    platforms.push_back(new RealmPlatform(realmplatform5.getSize(), realmplatform5.getPosition(), realmplatform5.getFillColor(), Realm::Light));

    sf::RectangleShape platform2(sf::Vector2f(450.f, 20.f));
    platform2.setFillColor(sf::Color::White);
    platform2.setPosition(350.f, 200.f);
    platforms.push_back(new DisappearPlatform(platform2.getSize(), platform2.getPosition(), platform2.getFillColor(), 9.f, 3.f));

    sf::RectangleShape ground(sf::Vector2f(3000.f, 50.f));
    ground.setFillColor(sf::Color::White);
    ground.setPosition(0.f, 850.f);
    platforms.push_back(new Platform(ground.getSize(), ground.getPosition(), ground.getFillColor()));

    sf::RectangleShape realmPlat(sf::Vector2f(200.f, 20.f));
    realmPlat.setFillColor(sf::Color::White);
    realmPlat.setPosition(1450.f, 750.f);
    platforms.push_back(new RealmPlatform(realmPlat.getSize(), realmPlat.getPosition(), realmPlat.getFillColor(), Realm::Light));

    sf::RectangleShape realmPlat1(sf::Vector2f(200.f, 20.f));
    realmPlat1.setFillColor(sf::Color::White);
    realmPlat1.setPosition(1450.f, 600.f);
    platforms.push_back(new RealmPlatform(realmPlat1.getSize(), realmPlat1.getPosition(), realmPlat1.getFillColor(), Realm::Dark));

    sf::RectangleShape realmPlat3(sf::Vector2f(200.f, 20.f));
    realmPlat3.setFillColor(sf::Color::White);
    realmPlat3.setPosition(0.f, 500.f);
    platforms.push_back(new RealmPlatform(realmPlat3.getSize(), realmPlat3.getPosition(), realmPlat3.getFillColor(), Realm::Light));

    sf::RectangleShape realmPlat4(sf::Vector2f(200.f, 20.f));
    realmPlat4.setFillColor(sf::Color::White);
    realmPlat4.setPosition(0.f, 200.f);
    platforms.push_back(new RealmPlatform(realmPlat4.getSize(), realmPlat4.getPosition(), realmPlat4.getFillColor(), Realm::Light));

    sf::RectangleShape realmPlat5(sf::Vector2f(200.f, 20.f));
    realmPlat5.setFillColor(sf::Color::White);
    realmPlat5.setPosition(0.f, 350.f);
    platforms.push_back(new RealmPlatform(realmPlat5.getSize(), realmPlat5.getPosition(), realmPlat5.getFillColor(), Realm::Dark));

    sf::RectangleShape realmPlat6(sf::Vector2f(320.f, 20.f));
    realmPlat6.setFillColor(sf::Color::White);
    realmPlat6.setPosition(900.f, 200.f);
    platforms.push_back(new RealmPlatform(realmPlat6.getSize(), realmPlat6.getPosition(), realmPlat6.getFillColor(), Realm::Dark));

    sf::RectangleShape platform4(sf::Vector2f(300.f, 20.f));
    platform4.setFillColor(sf::Color::White);
    platform4.setPosition(1300.f, 200.f);
    platforms.push_back(new Platform(platform4.getSize(), platform4.getPosition(), platform4.getFillColor()));


    // Realm Obstacles
    obstacles.push_back(new RealmObstacle({10.f, 100.f}, {500.f, 500.f}, Realm::Dark));
    obstacles.push_back(new RealmObstacle({10.f, 100.f}, {575.f, 100.f}, Realm::Light));
    obstacles.push_back(new RealmObstacle({10.f, 200.f}, {1300.f, 100.f}, Realm::Dark));

    // Star / End game goal
    goal.emplace_back(std::make_unique<Object>("Icons/Icon_Large_Star.png", sf::Vector2f(1450, 100)));


    //Spikes 
    spikes.emplace_back(std::make_unique<Object>("img/spike.png", sf::Vector2f(400.f, 820.f)));
    spikes.emplace_back(std::make_unique<Object>("img/spike.png", sf::Vector2f(650.f, 820.f)));
    spikes.emplace_back(std::make_unique<Object>("img/spike.png", sf::Vector2f(1000.f, 820.f)));
    spikes.emplace_back(std::make_unique<Object>("img/spike.png", sf::Vector2f(540.f, 570.f)));
    spikes.emplace_back(std::make_unique<Object>("img/spike.png", sf::Vector2f(900.f, 570.f)));
    spikes.emplace_back(std::make_unique<Object>("img/spike.png", sf::Vector2f(420.f, 170.f)));
    spikes.emplace_back(std::make_unique<Object>("img/spike.png", sf::Vector2f(620.f, 170.f)));

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
    player.checkObstacleCollision(obstacles);

    
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
    
    for(auto& g : goal){
        g->setScale(0.2f, 0.2f); 
        g->draw(window);
    }

    for (auto& spike : spikes) {
        spike->setScale(0.04f, 0.04f); 
        spike->draw(window);
    }

    player.draw(window);

    for (auto* plat : platforms) {
        if (plat->isActive())
            plat->draw(window);
        else if (auto* realmPlat = dynamic_cast<RealmPlatform*>(plat))
            plat->drawGhost(window);
    }

    for (auto& obs : obstacles)
        obs->setRealm(currentRealm);

    for (auto& obs : obstacles)
        obs->draw(window);

}

int Game_State::get_next_state() {
    if (goalReached) {
        if (goalClock.getElapsedTime().asSeconds() >= goalDelay) {
            goalReached = false; // reset for next time
            return MENU_STATE;
        }
        return GAME_STATE;
    }

    if(spikehit) {
        if (spikeClock.getElapsedTime().asSeconds() >= spikeDelay) {
            spikehit = false; // reset for next time
            return MENU_STATE;
        }
        return GAME_STATE;
    }
    // Check for goal collision
    for (auto it = goal.begin(); it != goal.end(); ++it) {
        if (player.getBounds().intersects((*it)->getBounds())) {
            std::cout << "Goal reached! Game Over!" << std::endl;
            player.setPosition(100.f, 700.f);
            goal.erase(it);
            goalReached = true;
            goalClock.restart();
            return GAME_STATE; 
        }
    }

    // Check for spike collision
    for (auto& spike : spikes) {
        if (player.getBounds().intersects(spike->getBounds())) {
           player.setPosition(100.f, 700.f);
            std::cout << "Player hit a spike! Game Over!" << std::endl;
            spikehit = true;
            spikeClock.restart();
            return GAME_STATE;
        }
    }

    return GAME_STATE;
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
