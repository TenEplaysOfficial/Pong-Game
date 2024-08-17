#include "player.h"
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

player::player() : playerASpeed(400.f), playerBSpeed(400.f), playerA(Vector2f(15, 105)), playerB(Vector2f(15, 105)) {

    // Player A
    playerA.setFillColor(Color::Red);
    playerA.setOrigin(playerA.getSize().x / 2, playerA.getSize().y / 2);
    playerA.setPosition(30, 350);

    // Player B
    playerB.setFillColor(Color::Green);
    playerB.setOrigin(playerB.getSize().x / 2, playerB.getSize().y / 2);
    playerB.setPosition(1170, 350);
}

void player::playerinput(float deltaTime) {
    // Player A Movement
    deltaTime = clock.restart().asSeconds();
    if (Keyboard::isKeyPressed(Keyboard::W)) playerA.move(0, -playerASpeed * deltaTime);
    if (Keyboard::isKeyPressed(Keyboard::S)) playerA.move(0, playerASpeed * deltaTime);

    // Player B Movement
    if (Keyboard::isKeyPressed(Keyboard::Up)) playerB.move(0, -playerBSpeed * deltaTime);
    if (Keyboard::isKeyPressed(Keyboard::Down)) playerB.move(0, playerBSpeed * deltaTime);
}

void player::playerEdgeCollision(RenderWindow& window) {
    // Ensure players stay within the window bounds
    if (playerA.getPosition().y - playerA.getSize().y / 2 < 0) playerA.setPosition(playerA.getPosition().x, playerA.getSize().y / 2);
    if (playerA.getPosition().y + playerA.getSize().y / 2 > window.getSize().y) playerA.setPosition(playerA.getPosition().x, window.getSize().y - playerA.getSize().y / 2);

    if (playerB.getPosition().y - playerB.getSize().y / 2 < 0) playerB.setPosition(playerB.getPosition().x, playerB.getSize().y / 2);
    if (playerB.getPosition().y + playerB.getSize().y / 2 > window.getSize().y) playerB.setPosition(playerB.getPosition().x, window.getSize().y - playerB.getSize().y / 2);
}

void player::renderPlayer(RenderWindow& window) {
    window.draw(playerA);
    window.draw(playerB);
}

void player::reset() {
    playerA.setPosition(30, 350);
    playerB.setPosition(1170, 350);
}