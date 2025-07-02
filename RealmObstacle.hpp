#pragma once
#include "Realm.hpp"
#include <SFML/Graphics.hpp>

class RealmObstacle {
private:
    sf::RectangleShape shape;
    Realm activeRealm;
    bool isActive;

public:
    RealmObstacle(const sf::Vector2f& size, const sf::Vector2f& position, Realm realm)
        : activeRealm(realm), isActive(true)
    {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red); // or a semi-transparent color for debugging
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(1.f);
    }

    void setRealm(Realm current) {
        isActive = (current == activeRealm);
    }

    void draw(sf::RenderWindow& window) {
        if (isActive)
            window.draw(shape);
    }

    bool isBlocking() const {
        return isActive;
    }

    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();
    }
};
