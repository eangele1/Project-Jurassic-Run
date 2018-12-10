#include "Environment.h"

void Background::advance(Background* background){
    
    //BG1
    if(background->Main[0]->getX() <= -3){
        background->Main[0]->setX(-1);
    }
    if(background->Repeat[0]->getX() <= -1.01){
        background->Repeat[0]->setX(0.99);
    }
    
    background->Main[0]->setX(background->Main[0]->getX() - advanceRate);
    background->Repeat[0]->setX(background->Repeat[0]->getX() - advanceRate);
    
    //BG2
    if(background->Main[1]->getX() <= -3){
        background->Main[1]->setX(-1);
    }
    if(background->Repeat[1]->getX() <= -1.01){
        background->Repeat[1]->setX(0.99);
    }
    
    background->Main[1]->setX(background->Main[1]->getX() - advanceRate);
    background->Repeat[1]->setX(background->Repeat[1]->getX() - advanceRate);
    
    //BG3
    if(background->Main[2]->getX() <= -3){
        background->Main[2]->setX(-1);
    }
    if(background->Repeat[2]->getX() <= -1.01){
        background->Repeat[2]->setX(0.99);
    }
    
    background->Main[2]->setX(background->Main[2]->getX() - advanceRate);
    background->Repeat[2]->setX(background->Repeat[2]->getX() - advanceRate);
    
    //BG4
    if(background->Main[3]->getX() <= -3){
        background->Main[3]->setX(-1);
    }
    if(background->Repeat[3]->getX() <= -1.01){
        background->Repeat[3]->setX(0.99);
    }
    
    background->Main[3]->setX(background->Main[3]->getX() - advanceRate);
    background->Repeat[3]->setX(background->Repeat[3]->getX() - advanceRate);
    
    //BG5
    if(background->Main[4]->getX() <= -3){
        background->Main[4]->setX(-1);
    }
    if(background->Repeat[4]->getX() <= -1.01){
        background->Repeat[4]->setX(0.99);
    }
    
    background->Main[4]->setX(background->Main[4]->getX() - advanceRate);
    background->Repeat[4]->setX(background->Repeat[4]->getX() - advanceRate);
}
