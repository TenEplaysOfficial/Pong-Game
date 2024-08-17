#include "scoreSystem.h"
#include <iostream> // For std::cerr

using namespace sf;
using namespace std;

scoreSystem::scoreSystem() : scoreboardp1(0), scoreboardp2(0) {
    if (!arial.loadFromFile("Assets/Fonts/Arial.ttf")) {
        cerr << "Failed to load font!" << endl;
    }

    // Text and scores for P1 and P2
    scorep1.setFont(arial);
    scorep2.setFont(arial);

    scorep1.setPosition(20, 10);
    scorep2.setPosition(1150, 10);

    scorep1.setCharacterSize(24);
    scorep2.setCharacterSize(24);

    scorep1.setFillColor(Color::White);
    scorep2.setFillColor(Color::White);

    // Set initial scores
    updateScoreText();
}

void scoreSystem::renderScore(RenderWindow& window) {
    window.draw(scorep1);
    window.draw(scorep2);
}

void scoreSystem::increaseScoreP1() {
    ++scoreboardp1;
    updateScoreText();
}

void scoreSystem::increaseScoreP2() {
    ++scoreboardp2;
    updateScoreText();
}

void scoreSystem::setScoreP1() {
    scoreboardp1 = this->score;
    updateScoreText();
}

void scoreSystem::setScoreP2() {
    scoreboardp2 = this->score;
    updateScoreText();
}

void scoreSystem::resetScores() {
    scoreboardp1 = 0;
    scoreboardp2 = 0;
    updateScoreText();
}

void scoreSystem::updateScoreText() {
    scorep1.setString(to_string(scoreboardp1));
    scorep2.setString(to_string(scoreboardp2));
}
