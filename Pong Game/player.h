#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class player {
public:
    player();
    void playerinput(float deltaTime);
    void playerEdgeCollision(RenderWindow& window);
    void renderPlayer(RenderWindow& window);

    void reset();

    RectangleShape playerA;
    RectangleShape playerB;

private:
    Clock clock;
    float playerASpeed;
    float playerBSpeed;
};
