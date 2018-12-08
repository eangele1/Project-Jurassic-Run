#include <iostream>
#include <vector>
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
    void DrawDino();
    void DrawBird();
    
    //Destructor
    ~Moves(){}
};

#endif
