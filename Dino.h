#ifndef Dino_h
#define Dino_h

#include <iostream>
#include "AnimatedRect.h"

class Dinosaur{
    
    public:
    
    AnimatedRect* DinoRun;
    AnimatedRect* DinoCrouch;
    TexRect* DinoStand;
    TexRect* DinoDead;
    
    float fallRate = 0.0015;
    
    Dinosaur(){}
    
    void jump(Dinosaur* Dino, int& flag, bool& DinoJump);
    void crouch(Dinosaur* Dino);
    void crouchUp(Dinosaur* Dino);
    
    ~Dinosaur(){
        delete DinoRun;
        delete DinoCrouch;
        delete DinoDead;
        delete DinoStand;
    }
};

#endif
