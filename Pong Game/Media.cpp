#include "Media.h"
#include <iostream>

using namespace std;

Media::Media() {
    if (!scoreEffect.loadFromFile("Assets/Music/pickupCoin.wav")) {
        cout << "Error loading sound file scoreEffect" <<endl;
    }
    else {
        Effect_score.setBuffer(scoreEffect);
    }
    if (!Music1.openFromFile("Assets/Music/MainMusic.mp3")) {
        cout << "Error loading Music file Music1" << endl;
    }
    
}

void Media::playMusic1()
{
    Music1.play();
}

void Media::stopMusic1()
{
    Music1.stop();
}

void Media::playScoreEffect() {
    Effect_score.play();
}
