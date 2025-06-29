#pragma once


#include <SFML/Graphics.hpp>
#include "State.h"

class Splash_State : public State
{
public:
    Splash_State();

    virtual void handle_event(sf::Event event) override;
    virtual void update() override;
    virtual void render(sf::RenderWindow& window) override;
    virtual int get_next_state() override;

private:
    sf::Texture logoTexture;
    sf::Sprite logoSprite;
    sf::Clock clock;
    bool skip, textResized, outra;
    float trans;
    sf::Time tShow;
};