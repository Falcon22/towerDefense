#ifndef TOWERDEFENSE_GAME_H
#define TOWERDEFENSE_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "StateManager.h"
#include "GameContext.h"
#include "ResourceManager/ResourcesHolder.h"
#include "ResourceManager/ResourcesIdentifier.h"


class Game {
public:
    Game();

    void run();

private:
    void input();
    void update(sf::Time frameTime);
    void draw();

    void registerStates();
    void loadAllResources();

    TextureHolder textureHolder;
    FontHolder fontHolder;
    sf::Font font;
    sf::Sprite cursor;
    sf::RenderWindow window;
    States::Context context;
    StateManager stateManager;
};


#endif //TOWERDEFENSE_GAME_H