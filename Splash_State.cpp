#include "Splash_State.h"

#include <iostream>
#include <string>
#include <stdexcept>


Splash_State::Splash_State()
    : skip(false) , trans(0.0) , textResized(false), tShow(sf::seconds(2)), outra(false)
{
    if(!logoTexture.loadFromFile("img/Logo.png"))
        throw std::invalid_argument("Unable to load logo texture");
    logoSprite.setTexture(logoTexture);
    clock.restart();
}

void Splash_State::handle_event(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
        {
            skip = true;
        }
    }
}

void Splash_State::update()
{

}

void Splash_State::render (sf::RenderWindow& window)
{

    auto bounds = logoSprite.getGlobalBounds();
    auto size = window.getSize();
    auto scaleFactor = sf::Vector2f(1.0f, 1.0f);

    logoSprite.setPosition((size.x - bounds.width) / 2 , (size.y - bounds.height) / 2);


    if(!textResized)
    {
        scaleFactor.x = size.x / bounds.width;
        scaleFactor.y = size.y / bounds.height;
        if(scaleFactor.x > scaleFactor.y)
            scaleFactor.x = scaleFactor.y;
        if(scaleFactor.y > scaleFactor.x)
            scaleFactor.y = scaleFactor.x;
        logoSprite.setScale(scaleFactor);
        textResized = true;
    }

    if (!outra){
        trans = clock.getElapsedTime().asMilliseconds() / (float)tShow.asMilliseconds();
        if(trans > 2.0f){
            clock.restart();
            outra = true;
        }
        if(trans > 1.0f){
            trans = 1.0f;
        }
    }
    else{
        trans = 1.0f - (clock.getElapsedTime().asMilliseconds() / (float)tShow.asMilliseconds());
        if(trans < 0.0f){
            skip = true;
            trans = 0.0f;
        }
    }
    logoSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(trans * 255)));
    window.clear(sf::Color::Black);
    window.draw(logoSprite);
    window.display();
}

int Splash_State::get_next_state()
{
    if(skip){
        skip = false; // Reset skip for next time
        return MENU_STATE; // Change to the menu state
    }
    else{
        return SPLASH_STATE;
    }
}

