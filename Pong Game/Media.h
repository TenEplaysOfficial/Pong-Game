#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Media {
public:
    Media();

    void playMusic1();
    void stopMusic1();
    
    void playScoreEffect();

private:
    SoundBuffer scoreEffect;
    Sound Effect_score;

    Music Music1;
};
