#include "DinosaurFunctions.h"
#include "TexRect.h"

float Moves::getX()const{
    return this->x;
}

float Moves::getY()const{
    return this->y;
}

void Moves::setX(float x){
    this->x = x;
}

void Moves::setY(float y){
    this->y = y;
}

void Moves::crouch(){
    float y = getY();
    y = -.05;
    
}
void Moves::jump(){
    float y = getY();
    float x = getX();
    y = y + 1.0;
    y = x + .05;
}
