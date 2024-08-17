#pragma once

#include <SFML/Graphics.hpp>

#include "player.h"
#include "Media.h"

#include "scoreSystem.h"
#include "scoreSystem.h"

using namespace sf;
using namespace std;

class ball
{
public:
    ball();

    void startBall();

    void resetBall();

    void update();

    void renderBall(RenderWindow& window);
    void ballMovement();
    void ballCollision(RenderWindow& window, player& playerA, player& playerB, scoreSystem& score, Media& media);

   
private:
    CircleShape ballshape;
    bool isBallMoving;
    float deltaTime;
    float ballSpeed;
    float speedIncrement;
    float initialSpeed;
    Clock clock; // Main clock for game logic
    Vector2f ballVelocity;  // Ball velocity
    Clock delayClock; // Clock for delay
};
