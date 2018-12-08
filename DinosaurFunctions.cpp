#include "DinosaurFunctions.h"
#include "TexRect.h"
#include "AnimatedRect.h"

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
void Moves:: DrawDino()
{
  AnimatedRect* Dino = new AnimatedRect("dino.png", 5, 5, 100, -0.7, -0.1, 0.2, 0.2);
    Dino->draw(.15); 
}
void Moves:: DrawBird()
{
  AnimatedRect*  Bird = new AnimatedRect("bird.png", 5, 5, 100, -.7, -.1, .2, .2);
    Bird->draw(.15);
}
