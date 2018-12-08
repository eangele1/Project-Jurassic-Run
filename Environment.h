//
//  Environment.hpp
//  glutapp
//
//  Created by Samantha Chi on 12/4/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#ifndef Environment_h
#define Environment_h
#include "Timer.h"
#include "App.h"
#include "Rect.h"
#include <stdio.h>
#include "TexRect.h"

class Environment{
private:
    float MoveX;
public:
    Environment(){
        
    }
    
    void update(){          //return new position later
        MoveX = 0;
    }
    void setmovex(float X){
        MoveX = X;
    }
    float getMoveX(){
        return MoveX;
    }
    void drawEnvironment();
    
    void Background(bool isGameOn);
    
    ~Environment(){
        
    }
};




#endif /* Environment_h */
