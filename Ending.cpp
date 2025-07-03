#include "Ending.h"
#include "constants.h"

#include <iostream>
#include <string>
#include <stdexcept>

using namespace sf;

/*
 * Create the welcome message using the font given in
 * 'resources/fonts/font.ttf'.
 *
 * The first argument of the sf::Text constructor is what string
 * it should draw, the second argument is what font should be used
 * to draw the text and the final argument specifies the font-size
 * (in pixels) of the text.
 */
Ending_State:: Ending_State ()
        :play { false } , activeMenu { 0 }
{
    std::string file = "Font/PixelifySans-Regular.ttf"; 
    if ( !font.loadFromFile (file) )
        throw std::invalid_argument ("Unable to load font");

    // Game Over
    endingTitle.setString("YOU WIN!!!");
    endingTitle.setFont(font);
    endingTitle.setScale(2.0f,2.0f);

    // Menu Entry
    textMenus.push_back(sf::Text("Exit", font, 32));

    // texture load
    textTitleBtn.loadFromFile("ButtonsText/ButtonText_Large_GreyOutline_Round.png");
    textTitleRender.setTexture(textTitleBtn);
    auto scaleX = endingTitle.getGlobalBounds().width * 1.25f / textTitleRender.getGlobalBounds().width;
    auto scaleY = scaleX;
    textTitleRender.setScale(scaleX, scaleY);
}

/*
 * check for the 'enter' key.
 *
 * If it has been pressed we want to change to a new state.
 */
void Ending_State :: handle_event (Event event)
{
    if ( event.type == Event::KeyPressed )
    {
        if( event.key.code == Keyboard::Key::Down){
            activeMenu++;
        }
        if( event.key.code == Keyboard::Key::Up){
            activeMenu--;
        }
        if(activeMenu < 0) activeMenu = textMenus.size() - 1;
        activeMenu = (activeMenu % textMenus.size());
        if(event.key.code == Keyboard::Key::Enter){
            play = true;
        }
    }
}


void Ending_State :: update ()
{

}

void Ending_State :: render (sf::RenderWindow & window)
{
    auto size { window.getSize() };
    auto startY { size.y / 3.0f};
    auto addY { textMenus[0].getGlobalBounds().height};

    // Render Title
    textTitleRender.setPosition((size.x - textTitleRender.getGlobalBounds().width) / 2.0f, startY - (endingTitle.getGlobalBounds().height * 2.5f));
    window.draw(textTitleRender);
    endingTitle.setPosition((size.x - endingTitle.getGlobalBounds().width) / 2.0f, startY - (endingTitle.getGlobalBounds().height * 2.0f));
    window.draw(endingTitle);

    // Render Menu
    auto index {0};
    startY += addY * 4.0f; // Adjust starting Y position for menu items
    addY *= 5.0f; // Adjust spacing between menu items
    for(auto obj : textMenus){
        if(index == activeMenu){
            obj.setStyle(sf::Text::Bold);
            obj.setScale(1.25f, 1.25f);
            obj.setFillColor(sf::Color::Blue);
        }

        sf::FloatRect bounds = obj.getGlobalBounds();
        obj.setPosition((size.x - bounds.width) / 2.0f, startY);
        window.draw(obj);
        startY += addY;
        index++;
    }
}

/*
 * If return has been pressed we change to the GAME_STATE, otherwise
 * we stay in MENU_STATE
 */
int Ending_State :: get_next_state()
{
    if (play)
    {
        play = false;

        if( activeMenu == textMenus.size() - 1 )
        {
            std::exit(0);
        }
        else{
            return ENDING_STATE; // In case of an error, stay in the menu
        }
    }
    else
    {
        return ENDING_STATE;
    }
}

