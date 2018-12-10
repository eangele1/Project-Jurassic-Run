#include "Dino.h"

void Dinosaur::crouch(Dinosaur* Dino){
    Dino->DinoRun->pause();
    Dino->DinoCrouch->playLoop();
    
}

void Dinosaur::crouchUp(Dinosaur* Dino){
    Dino->DinoCrouch->pause();
    Dino->DinoRun->playLoop();
}

void Dinosaur::jump(Dinosaur* Dino, int& flag, bool& DinoJump){
    
    if(flag == 0){
        if(Dino->DinoRun->getY() < 0.2){
            Dino->DinoRun->setY(Dino->DinoRun->getY() + 0.0015);
            Dino->DinoCrouch->setY(Dino->DinoCrouch->getY() + 0.0015);
        }
        else{
            flag = 1;
        }
    }
    if(flag == 1){
        if(Dino->DinoRun->getY() >= -0.5){
            Dino->DinoRun->setY(Dino->DinoRun->getY() - fallRate);
            Dino->DinoCrouch->setY(Dino->DinoCrouch->getY() - fallRate);
        }
        else{
            flag = 0;
            DinoJump = false;
        }
    }
}
