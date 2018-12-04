#ifndef DinasaurFunctions_h
#define DinasaurFunctions_h
#include <iostream>
#include "DinausarFunctions.cpp"
#include <vector>

class Moves
{
private:
    float x = 0.0; //x Coordinate
    float y = 0.0; //y Coordinate
    
public:
    bool Left;
    bool Right;
    bool Crouch;
    bool Jump;
    //Constructor
    Moves()
    {
        this->x= x;
        this->y= y;
    }
    //Constructor for moving left and right
    Moves(float X)
    {
        this->x= x;
        Left = false;
        Crouch = false;
    }
    //Contructor for moving up and down
    Moves(float x, float y)
    {
        this->x = x;
        this->y = y;
        Right = false;
        Jump = false;
    }
    float getX()const
    {
        return this->x;
    }
    float getY()const
    {
        return this->y;
    }
    void setX(float x)
    {
        this->x =x;
    }
    void setY(float y)
    {
        this->y = y;
    }
    
    void Dinoleft()
    {
        float x = Moves->getX();
        x= x - .05;
        
    }
    void Dinoright()
    {
        float x = Moves->getX();
        x = x + .05;
    }
    void crouch()
    {
        float y= Moves->getY();
        y = -.05;
        
    }
    void jump()
    {
        float y = Moves->getY();
        float x = Moves->getX();
        y = y + 1.0;
        y = x + .05;
        
    }
};

vector <Moves*> functions;

#endif
