#ifndef PowerUp_h
#define PowerUp_h

#include <iostream>
#include "AnimatedRect.h"
#include "Dino.h"
#include "cxxtimer.h"
#include "Obsticle.h"

class PowerUp{
  
public:
    
    TexRect* item;
    TexRect* laser;
    
    cxxtimer::Timer* timer = new cxxtimer::Timer();
    
    float advanceRate;
    
    PowerUp(){}
    
    void powerUpAdvance(PowerUp* powerUp);
    void laserAdvance(Dinosaur* Dino, PowerUp* powerUp);
    void checkPowerUpGet(Dinosaur* Dino, PowerUp* powerUp);
    void checkLaserHit(PowerUp* powerUp, Obsticle* obsticle);
    
    ~PowerUp(){}
};

#endif
