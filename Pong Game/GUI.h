#pragma once

#include <SFML/Graphics.hpp>

// Forward declaration of GameState
enum GameState;

#include "player.h"
#include "ball.h"
#include "scoreSystem.h"

using namespace sf;

enum GameState {
    MainMenu,
    Playing,
    Paused
};

class GUI {
public:

    GUI();

    void MainMenu();

    void renderMainMenu(RenderWindow& window);
    void renderPauseMenu(RenderWindow& window);

    void GUIinputHandle(RenderWindow& window, Event event, GameState& gameState);

    float getDeltaTime(); // Get delta time

    void updateGameElements(RenderWindow& window, float deltaTime ,player& playerA, player& playerB); // Update game elements

private:

    // Game Title
    Text GameName;
    Font GameNameFont;

    // Play Button
    Texture BDefault_Play;
    Texture BHover_Play;
    Sprite playButton;

    Clock clock; // Clock for delta time
    player playerA;
    player playerB;
    ball ball;
    scoreSystem score;
    Media media;
};
