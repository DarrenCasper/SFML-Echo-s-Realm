#pragma once
#include <SFML/Graphics.hpp>

class Object {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;

public:
    Object(const std::string &imagePath, const sf::Vector2f &startPos);
    virtual void update(float deltaTime); 
    virtual void draw(sf::RenderWindow &window);
    virtual ~Object() {}
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds();}
    void setScale(float x, float y) { sprite.setScale(x, y); }
};
