#ifndef Obsticle_h
#define Obsticle_h

#include <iostream>
#include <string>
#include "AnimatedRect.h"
#include "Dino.h"
#include "Score.h"
#include <SFML/Audio.hpp>

class Obsticle{
  
public:
    
    TexRect* Cactus;
    AnimatedRect* Bird;
    
    float advanceRate;
    
    Obsticle(){}
    
    void birdAdvance(Obsticle* obsticle);
    void cactusAdvance(Obsticle* obsticle);
    void checkBirdHit(Dinosaur* Dino, Obsticle* obsticle, bool& isGameOn, bool& DinoJump, bool& isDead, bool& end, AnimatedRect* gameover, Score* score, std::string& hiScore, sf::Music* music);
    void checkCactusHit(Dinosaur* Dino, Obsticle* obsticle, bool& isGameOn, bool& DinoJump, bool& isDead, bool& end, AnimatedRect* gameover, Score* score, std::string& hiScore, sf::Music* music);
    
    ~Obsticle(){
        delete Cactus;
        delete Bird;
    }
};

#endif
