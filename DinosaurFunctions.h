<<<<<<< HEAD
#ifndef DinasaurFunctions_h
#define DinasaurFunctions_h
#include <iostream>
#include "DinausarFunctions.cpp"
#include <vector>
#include "App.cpp"
=======
#ifndef DinosaurFunctions_h
#define DinosaurFunctions_h
>>>>>>> 92ffdbbb6bfb1d17bff2c64877b08f21eae23411

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

#endif
