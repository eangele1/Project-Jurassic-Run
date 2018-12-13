#include "PowerUp.h"

void PowerUp::powerUpAdvance(PowerUp* powerUp){
    if(powerUp->item->getX() <= -1.2){
        powerUp->item->setX(1);
    }
    
    powerUp->item->setX(powerUp->item->getX() - advanceRate);
}
void PowerUp::laserAdvance(Dinosaur* Dino, PowerUp* powerUp){
    powerUp->laser->setX(Dino->DinoRun->getX() + 0.0015);
}
void PowerUp::checkPowerUpGet(Dinosaur* Dino, PowerUp* powerUp){
    
}
void PowerUp::checkLaserHit(PowerUp* powerUp, Obsticle* obsticle){
    
}
