#ifndef PowerUp_h
#define PowerUp_h

#include <iostream>
#include <vector>
#include <cstdlib>
#include "AnimatedRect.h"
#include "Dino.h"
#include "cxxtimer.h"
#include "Obsticle.h"

class PowerUp{
  
public:
    
    TexRect* item;
    
    std::vector<TexRect*>* lasers;
    std::vector<std::vector<TexRect*>::iterator>* deleteLasers;
    
    cxxtimer::Timer* timer = new cxxtimer::Timer();
    
    float advanceRate;
    
    PowerUp(){}
    
    void powerUpAdvance(PowerUp* powerUp);
    bool checkPowerUpGet(Dinosaur* Dino, PowerUp* powerUp);
    bool checkLaserHit(PowerUp* powerUp, Obsticle* obsticle, std::vector<TexRect*>::iterator laserIterator, int& objectSwitch);
    
    ~PowerUp(){
        delete item;
        delete lasers;
        delete deleteLasers;
        delete timer;
    }
};

#endif
