#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include <vector>
using namespace std;

class Ending_State: public State
{
public:
    Ending_State ();

    virtual void handle_event (sf::Event event) override;
    virtual void update () override;
    virtual void render (sf::RenderWindow & window) override;
    virtual int get_next_state() override;


private:


    
    sf::Text endingTitle;
    vector<sf::Text> textMenus;
    sf::Font font{};

    sf::Texture textTitleBtn;
    sf::Text textMenutBtn;
    sf::Sprite textTitleRender;


    bool play;

    int activeMenu;


  
};
