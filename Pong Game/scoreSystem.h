#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class scoreSystem {
public:
    scoreSystem();
    int score;
    void renderScore(RenderWindow& window);
    void increaseScoreP1();
    void increaseScoreP2();
    void setScoreP1();
    void setScoreP2();
    void resetScores();  // Method to reset scores

private:
    int scoreboardp1;
    int scoreboardp2;

    Font arial;
    Text scorep1;
    Text scorep2;

    void updateScoreText();
};