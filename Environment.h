#ifndef Environment_h
#define Environment_h

#include <iostream>
#include <vector>
#include "AnimatedRect.h"

class Background{
    
public:
    
    float advanceRate;
    
    std::vector<TexRect*> Main;
    std::vector<TexRect*> Repeat;
    
    Background(){}
    
    void advance(Background* background);
    
    ~Background(){}
    
};

#endif
