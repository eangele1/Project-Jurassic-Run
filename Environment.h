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
#include "cxxtimer.h"


class Environment{
private:
    float MoveX = 3;
public:
    
    cxxtimer::Timer* timer = new cxxtimer::Timer();
    
    Environment(){}

    void setmovex(float X){
        MoveX = X;
    }
    float getMoveX(){
        return MoveX;
    }
    
    void drawEnvironment();
    
    bool GameUpdate();
    
    void Background();
    
    ~Environment(){
        
    }
};




#endif /* Environment_h */
