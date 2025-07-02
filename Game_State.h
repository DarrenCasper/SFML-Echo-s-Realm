#pragma once

#include "State.h"
#include "player.hpp"
#include "platform.hpp"
#include "DisappearPlatform.hpp"
#include "Realm.hpp"
#include "RealmPlatform.hpp"
#include "Object.hpp"
#include "Cloud.hpp"
#include "RealmObstacle.hpp"

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>
#include <vector>

class Game_State : public State {
public:
    Game_State();
    ~Game_State() override;

    void handle_event(sf::Event event) override; 
    void update() override;
    void render(sf::RenderWindow& window) override; 
    int get_next_state() override; 

private:
    void updateView(sf::RenderWindow& window, sf::View& view);

    Player player;
    Realm currentRealm;
    bool rKeyPrev;


    std::vector<Platform*> platforms;
    std::vector<RealmObstacle*> obstacles;
    std::list<std::unique_ptr<Object>> decorations;
    std::list<std::unique_ptr<Object>> goal;
    std::list<std::unique_ptr<Object>> spikes;

    sf::Texture backgroundTexture1, backgroundTexture2, backgroundTexture3, backgroundTexture4;
    sf::Sprite backgroundSprite1, backgroundSprite2, backgroundSprite3, backgroundSprite4;

    sf::Clock clock;
    sf::View view;

    bool goalReached = false;
    sf::Clock goalClock;
    float goalDelay = 0.1f; 

    bool spikehit = false;
    sf::Clock spikeClock;
    float spikeDelay = 0.1f;


    float gravity;
};