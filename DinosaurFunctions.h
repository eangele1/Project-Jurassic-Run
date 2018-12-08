#ifndef DinasaurFunctions_h
#define DinasaurFunctions_h
#include <iostream>
//#include "DinausarFunctions.cpp"
#include <vector>
//#include "App.cpp"
#ifndef DinosaurFunctions_h
#define DinosaurFunctions_h

class Moves{
private:
    float x = 0.0; //x Coordinate
    float y = 0.0; //y Coordinate
    
public:
    bool Crouch;
    bool Jump;

    //Constructor
    Moves(){}

    //Contructor for moving up and down
    Moves(float x, float y){
        this->x = x;
        this->y = y;
        Jump = false;
    }

    float getX()const;
    float getY()const;
    void setX(float x);
    void setY(float y);

    void crouch();
    void jump();
    
    //Destructor
    ~Moves(){}
};

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


#endif
