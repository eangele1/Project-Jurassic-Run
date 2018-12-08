//
//  Environment.cpp
//  glutapp
//
//  Created by Samantha Chi on 12/4/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#include "Environment.h"
#include "Score.h"
#include "cxxtimer.h"
#include "TexRect.h"
#include <chrono>


void Environment::drawEnvironment(){
    TexRect *background = new TexRect("Desert.png",-1,1,2, 2);
    background->drawR(0);
//    TextRect *cacti = new TexRect(
}

bool Environment::GameUpdate(){
    bool running = false;
    
    if(timer->start() == true)
        running = true;
    
    if(timer->stop() == true)
        running = false;
    
    return running;
    
        // use isGameOn from App.cpp
}


void Environment::Background(){
    float decrement = 0.0;
    
    while(GameUpdate() == true){
        
        //decrement -= timer->count<std::chrono::microseconds>()/ 10;
        decrement += 0.1;
        setmovex(decrement);
        
        TexRect *background = new TexRect("Desert.png",1+getMoveX(),1,2, 2);
        background->drawR(0);
        //use milliseconds from timer to increment position
        //once x reaches a certain number, redraw

    }
    
}
