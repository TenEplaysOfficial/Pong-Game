    // SFML Lib
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <windows.h>

    // C++ Lib
    #include <cstdlib> // For rand() and srand()
    #include <ctime>   // For time()
    #include <string>  // For std::to_string()
    #include <iostream> // For std::cerr
    #include <cmath>  // For std::abs

    // Header Files
    #include "GUI.h"
    #include "player.h"
    #include "scoreSystem.h"
    #include "ball.h"
    #include "Media.h"

    // Name Space
    using namespace sf;
    using namespace std;

    // Define game states


    void setWindowStyle(RenderWindow& window) {
        HWND hwnd = window.getSystemHandle(); // Get the native handle

        // Get the current window style
        LONG style = GetWindowLong(hwnd, GWL_STYLE);

        // Remove the maximize button by clearing the WS_MAXIMIZEBOX flag
        style &= ~WS_MAXIMIZEBOX;

        // Set the new style
        SetWindowLong(hwnd, GWL_STYLE, style);

        // Redraw the window with the new style
        SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    }

    int main() {
        RenderWindow window(VideoMode(1200, 700), "Pong Game");
        window.setFramerateLimit(60);

        // Load icon from file
        Image windowIcon;
        windowIcon.loadFromFile("Assets/Icon/PONG GAME LOGO.png");
        // Set the window icon
        window.setIcon(windowIcon.getSize().x, windowIcon.getSize().y, windowIcon.getPixelsPtr());

        // Initialize random seed
        srand(static_cast<unsigned>(time(nullptr)));

        // Initialize GUI
        GUI gui;
        gui.MainMenu();
        player playerA;
        player playerB;
        Media media;

        setWindowStyle(window); // Apply the window style change

        // Set initial game state
        GameState gameState = MainMenu;

        // Game loop
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();

                // Handle input based on game state
                if (gameState == MainMenu) {
                    gui.GUIinputHandle(window, event, gameState);
                }
                else if (gameState == Playing) {
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                        gameState = Paused; // Pause the game
                    }
                }
                else if (gameState == Paused) {
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                        gameState = Playing; // Resume the game
                    }
                    if (event.type == Event::KeyPressed && event.key.code == Keyboard::Backspace) {
                        window.close();
                    }
                }
            }

            window.clear(Color(50, 55, 65, 255));

            // Render based on game state
            if (gameState == MainMenu) {
                gui.renderMainMenu(window);
            }
            else if (gameState == Playing) {
                // Update and render game elements
                float deltaTime = gui.getDeltaTime();
                gui.updateGameElements(window, deltaTime, playerA, playerB);
            }
            else if (gameState == Paused) {
                gui.renderPauseMenu(window);
            }

            window.display();

        }

        return 0;
    }