#include "GUI.h"
#include <iostream>

using namespace sf;
using namespace std;

GUI::GUI() {
    // Load fonts and textures
    if (!GameNameFont.loadFromFile("Assets/Fonts/JosefinSans-Bold.ttf")) {
        cout << "Failed to load font Game Name!" << endl;
    }
    if (!BDefault_Play.loadFromFile("Assets/GUI/Buttons/Default.png")) {
        cout << "Failed to load BDefault_Play!" << endl;
    }
    if (!BHover_Play.loadFromFile("Assets/GUI/Buttons/Hover.png")) {
        cout << "Failed to load BHover_Play!" << endl;
    }

    MainMenu();  // Initialize the GUI components
}

void GUI::MainMenu() {
    GameName.setFont(GameNameFont);
    GameName.setString("Pong Game");
    GameName.setCharacterSize(50);
    GameName.setFillColor(Color::White);
    GameName.setPosition(600 - GameName.getLocalBounds().width / 2, 200 - GameName.getLocalBounds().height / 2);

    playButton.setTexture(BDefault_Play);
    playButton.setPosition(600 - playButton.getLocalBounds().width / 2, 380 - playButton.getLocalBounds().height / 2);

    media.playMusic1();

}

void GUI::GUIinputHandle(RenderWindow& window, Event event, GameState& gameState) {
    static bool buttonHovered = false; // Track button hover state

    // Handle events
    if (event.type == Event::Closed) {
        window.close();
    }

    // Handle play button hover
    Vector2i mousePos = Mouse::getPosition(window);
    bool isHovered = playButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos));

    if (isHovered && !buttonHovered) {
        playButton.setTexture(BHover_Play);
        buttonHovered = true;
    }
    else if (!isHovered && buttonHovered) {
        playButton.setTexture(BDefault_Play);
        buttonHovered = false;
    }

    // Handle button click
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        if (playButton.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
            gameState = Playing; // Proceed to game start
            window.setMouseCursorVisible(false);
            clock.restart(); // Restart the clock for delta time calculation
            media.stopMusic1();
        }
    }
}

void GUI::renderMainMenu(RenderWindow& window) {
    window.draw(GameName);
    window.draw(playButton);
}

void GUI::renderPauseMenu(RenderWindow& window) {
    // Create a semi-transparent overlay
    RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150)); // Black with 150 alpha for transparency

    // Create pause text
    Text pauseText("Paused - Press 'Esc' to Resume or Press 'Backspace' to Quit Game", GameNameFont, 25);
    pauseText.setFillColor(Color::White);
    pauseText.setPosition(window.getSize().x / 2 - pauseText.getGlobalBounds().width / 2, window.getSize().y / 2 - pauseText.getGlobalBounds().height / 2);

    // Draw overlay and text
    window.draw(overlay);
    window.draw(pauseText);
}

float GUI::getDeltaTime() {
    return clock.restart().asSeconds();
}

void GUI::updateGameElements(RenderWindow& window, float deltaTime, player& playerA, player& playerB) {
    // Player input
    playerA.playerinput(deltaTime); // Player A input
    playerB.playerinput(deltaTime); // Player B input

    // Ball movement
    ball.ballMovement();
    ball.update();

    // Collision detection
    ball.ballCollision(window, playerA, playerB, score, media);

    playerA.playerEdgeCollision(window);
    playerB.playerEdgeCollision(window);

    // Render elements
    playerA.renderPlayer(window);
    playerB.renderPlayer(window);
    ball.renderBall(window);
    score.renderScore(window);
}