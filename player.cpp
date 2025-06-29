#include "player.hpp"

Player::Player()
    : isJumping(false), jumpSpeed(-600.0f),  
      currentFrame(0), frameTime(0.1f), timeSinceLastFrame(0.f),
      frameWidth(32), frameHeight(32)
{
    texture.loadFromFile("img/AnimationSheet_Character.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight));
    sprite.setPosition(100.f, 700.f);
    sprite.setOrigin(frameWidth / 2.f, 0);
    sprite.setScale(1.7f, 1.7f);
}

void Player::handleInput() {
    velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x = -150.f;
        sprite.setScale(-1.7f, 1.7f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x = 150.f;
        sprite.setScale(1.7f, 1.7f);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping) {
        velocity.y = jumpSpeed;
        isJumping = true;
    }
}

void Player::update(float deltaTime) {
    // Gravity
    velocity.y += 15.f;

    // Animation only when walking
    if (velocity.x != 0.f) {
        timeSinceLastFrame += deltaTime;
        if (timeSinceLastFrame >= frameTime) {
            currentFrame = (currentFrame + 1) % 2; 
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            timeSinceLastFrame = 0.f;
        }
    } else {
        sprite.setTextureRect(sf::IntRect(0, 0, frameWidth, frameHeight)); 
    }

    sprite.move(velocity * deltaTime);
}
void Player::checkObstacleCollision(const std::vector<RealmObstacle*>& obstacles) {
    for (auto obs : obstacles) {
        if (!obs->isBlocking()) continue;

        if (sprite.getGlobalBounds().intersects(obs->getBounds())) {
            if (velocity.x > 0) {
                // Coming from the left → push to the left side of obstacle
                sprite.setPosition(obs->getBounds().left - sprite.getGlobalBounds().width, sprite.getPosition().y);
            }
            if (velocity.x < 0) {
                // Coming from the right → push to the right side of obstacle (dumb solution cuz of scaling)
                sprite.setPosition(obs->getBounds().left + 40.0f + obs->getBounds().width, sprite.getPosition().y);
            }
            velocity.x = 0;
        }
    }
}


void Player::checkCollision(const std::vector<Platform*>& platforms) {
    for (const auto& plat : platforms) {
        if (sprite.getGlobalBounds().intersects(plat->getBounds()) && plat->isActive()) {
            if (velocity.y > 0) {
                sprite.setPosition(sprite.getPosition().x, plat->getPosition().y - sprite.getGlobalBounds().height);
                velocity.y = 0.f;
                isJumping = false;
            }
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}
