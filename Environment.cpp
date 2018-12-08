//
//  Environment.cpp
//  glutapp
//
//  Created by Samantha Chi on 12/4/18.
//  Copyright © 2018 Angelo Kyrilov. All rights reserved.
//

#include "Environment.h"
#include "TexRect.h"




void Environment::drawEnvironment(){
    TexRect *background = new TexRect("Desert.png",-1,1,2, 2);
    background->drawR(0);
//    TextRect *cacti = new TexRect(
}


void Environment::Background(bool isGameOn){
    while(isGameOn == true){
        //use milliseconds from timer to increment position
        //once x reaches a certain number, redraw
        
    }
}
