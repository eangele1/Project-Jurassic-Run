#include "PowerUp.h"

void PowerUp::powerUpAdvance(PowerUp* powerUp){
    if(powerUp->item->getX() <= -1.2){
        powerUp->item->setX(1);
    }
    powerUp->item->setX(powerUp->item->getX() - advanceRate);
}

bool PowerUp::checkPowerUpGet(Dinosaur* Dino, PowerUp* powerUp){
    if(Dino->DinoRun->animating == false){
        return false;
    }
    else{
        if(powerUp->item->contains((Dino->DinoRun->getX() + Dino->DinoRun->getW()), (Dino->DinoRun->getY() - Dino->DinoRun->getH())) || powerUp->item->contains((Dino->DinoRun->getX() + Dino->DinoRun->getW()), (Dino->DinoRun->getY())) || powerUp->item->contains((Dino->DinoRun->getX()), (Dino->DinoRun->getY() - Dino->DinoRun->getH())) || powerUp->item->contains(Dino->DinoRun->getX(), Dino->DinoRun->getY())){
            
            powerUp->item->setX(1);
            
            timer->start();
            
            return true;
            
        }
        
        return false;
    }
}

bool PowerUp::checkLaserHit(PowerUp* powerUp, Obsticle* obsticle, std::vector<TexRect*>::iterator laserIterator, int& objectSwitch){
    if(obsticle->Bird->contains(((*laserIterator)->getX() + (*laserIterator)->getW()), ((*laserIterator)->getY() - (*laserIterator)->getH())) || obsticle->Bird->contains(((*laserIterator)->getX() + (*laserIterator)->getW()), ((*laserIterator)->getY())) || obsticle->Bird->contains(((*laserIterator)->getX()), ((*laserIterator)->getY() - (*laserIterator)->getH())) || obsticle->Bird->contains((*laserIterator)->getX(), (*laserIterator)->getY())){
        
        obsticle->Bird->setX(1.5);
        
        srand(static_cast<unsigned int>(time(0)));
        objectSwitch = rand() % 2;
        
        return true;
        
    }
    
    if(obsticle->Cactus->contains(((*laserIterator)->getX() + (*laserIterator)->getW()), ((*laserIterator)->getY() - (*laserIterator)->getH())) || obsticle->Cactus->contains(((*laserIterator)->getX() + (*laserIterator)->getW()), ((*laserIterator)->getY())) || obsticle->Cactus->contains(((*laserIterator)->getX()), ((*laserIterator)->getY() - (*laserIterator)->getH())) || obsticle->Cactus->contains((*laserIterator)->getX(), (*laserIterator)->getY())){
        
        obsticle->Cactus->setX(1.5);
        
        srand(static_cast<unsigned int>(time(0)));
        objectSwitch = rand() % 2;
        
        return true;
        
    }
    
    return false;
}
