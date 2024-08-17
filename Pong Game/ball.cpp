#include "ball.h"
#include <SFML/Graphics.hpp>
#include <string>  // For std::to_string()
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <cmath>   // For std::abs

using namespace sf;
using namespace std;

ball::ball() : ballshape(20), ballVelocity(0.f, 0.f), ballSpeed(400.f), deltaTime(0.0f), speedIncrement(50.f), initialSpeed(400.f), isBallMoving(false) {
    // Ball initialization
    ballshape.setFillColor(Color::White);
    ballshape.setOrigin(ballshape.getRadius(), ballshape.getRadius());
    ballshape.setPosition(600, 350);
    srand(static_cast<unsigned>(time(nullptr))); // Initialize random seed
}

void ball::startBall() {
    // Start the ball with a random direction
    ballVelocity.x = (rand() % 2 == 0) ? ballSpeed : -ballSpeed;
    ballVelocity.y = (rand() % 2 == 0) ? ballSpeed : -ballSpeed;
    isBallMoving = true; // Set the flag to indicate the ball is moving
}

void ball::ballMovement() {
    // Update deltaTime and move the ball
    deltaTime = clock.restart().asSeconds();
    if (isBallMoving) {
        ballshape.move(ballVelocity * deltaTime);
    }
}

void ball::ballCollision(RenderWindow& window, player& playerA, player& playerB, scoreSystem& score, Media& media) {
    // Ball Collision with top and bottom walls
    if (ballshape.getPosition().y - ballshape.getRadius() < 0 || ballshape.getPosition().y + ballshape.getRadius() > window.getSize().y) {
        ballVelocity.y = -ballVelocity.y;
    }

    // Ball Collision with players
    if (ballshape.getGlobalBounds().intersects(playerA.playerA.getGlobalBounds())) {
        float offset = (ballshape.getPosition().y - playerA.playerA.getPosition().y) / playerA.playerA.getSize().y;
        ballVelocity.x = std::abs(ballVelocity.x) + speedIncrement; // Increase speed
        ballVelocity.y += offset * ballSpeed * 0.3f; // Adjust angle based on impact point
    }
    if (ballshape.getGlobalBounds().intersects(playerB.playerB.getGlobalBounds())) {
        float offset = (ballshape.getPosition().y - playerB.playerB.getPosition().y) / playerB.playerB.getSize().y;
        ballVelocity.x = -std::abs(ballVelocity.x) - speedIncrement; // Increase speed
        ballVelocity.y += offset * ballSpeed * 0.3f; // Adjust angle based on impact point
    }

    // Ball out of bounds (scoring)
    if (ballshape.getPosition().x - ballshape.getRadius() < 0) {
        media.playScoreEffect(); // Play sound effect
        score.increaseScoreP2();
        resetBall();
        delayClock.restart(); // Restart the delay clock
    }
    if (ballshape.getPosition().x + ballshape.getRadius() > window.getSize().x) {
        media.playScoreEffect(); // Play sound effect
        score.increaseScoreP1();
        resetBall();
        delayClock.restart(); // Restart the delay clock
    }
}

void ball::resetBall() {
    // Reset ball position and stop the ball
    ballshape.setPosition(600, 350);
    ballVelocity = sf::Vector2f(0.f, 0.f); // Stop the ball
    isBallMoving = false; // Ball is not moving
}

void ball::update() {
    // Check if the ball should start moving after delay
    if (!isBallMoving && delayClock.getElapsedTime().asSeconds() > 3.0f) {
        startBall(); // Start the ball after 3 seconds
    }
}

void ball::renderBall(RenderWindow& window) {
    window.draw(ballshape);
}
