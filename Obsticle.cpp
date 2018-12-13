#include "Obsticle.h"

void Obsticle::birdAdvance(Obsticle* obsticle){
    
    if(obsticle->Bird->getX() <= -1.2){
        obsticle->Bird->setX(1);
    }
    
    obsticle->Bird->setX(obsticle->Bird->getX() - advanceRate);
}

void Obsticle::cactusAdvance(Obsticle* obsticle){
    
    if(obsticle->Cactus->getX() <= -1.2){
        obsticle->Cactus->setX(1);
    }
    
    obsticle->Cactus->setX(obsticle->Cactus->getX() - advanceRate);
}

void Obsticle::checkBirdHit(Dinosaur* Dino, Obsticle* obsticle, bool& isGameOn, bool& DinoJump, bool& isDead, bool& end, AnimatedRect* gameover, Score* score, std::string& hiScore, sf::Music* music, Score* runningScore, sf::Music* secretMusic){
    
    if(Dino->DinoRun->animating == false){
        //DO NOTHING!!!
    }
    else{
        if(obsticle->Bird->contains((Dino->DinoRun->getX() + Dino->DinoRun->getW()), (Dino->DinoRun->getY() - Dino->DinoRun->getH())) || obsticle->Bird->contains((Dino->DinoRun->getX() + Dino->DinoRun->getW()), (Dino->DinoRun->getY())) || obsticle->Bird->contains((Dino->DinoRun->getX()), (Dino->DinoRun->getY() - Dino->DinoRun->getH())) || obsticle->Bird->contains(Dino->DinoRun->getX(), Dino->DinoRun->getY())){
            isGameOn = false;
            DinoJump = false;
            isDead = true;
            Dino->DinoRun->pause();
            Dino->DinoCrouch->pause();
            Dino->DinoDead->setY(Dino->DinoRun->getY());
            
            runningScore->timer->stop();
            score->timer->stop();
            score->compareAndSet();
            hiScore = score->getHighScore();
            
            //stops the secrete music if it's playing
            secretMusic->stop();
            
            //stops the audio file
            music->stop();
            
            //if music file not found, will throw error in console.
            if (!music->openFromFile("audio/Dead.wav")){
                std::cout<<"Audio file not found!"<<std::endl;
            }
            
            music->setLoop(false);
            
            //plays the audio file
            music->play();
            
            if(end == false){
                gameover->playOnce();
                end = true;
            }
        }
    }
    
    if (Dino->DinoCrouch->animating == false) {
        //DO NOTHING!!!
    }
    else{
        if(obsticle->Bird->contains((Dino->DinoCrouch->getX() + Dino->DinoCrouch->getW()), (Dino->DinoCrouch->getY() - Dino->DinoCrouch->getH())) || obsticle->Bird->contains((Dino->DinoCrouch->getX() + Dino->DinoCrouch->getW()), (Dino->DinoCrouch->getY())) || obsticle->Bird->contains((Dino->DinoCrouch->getX()), (Dino->DinoCrouch->getY() - Dino->DinoCrouch->getH())) || obsticle->Bird->contains(Dino->DinoCrouch->getX(), Dino->DinoCrouch->getY())){
            isGameOn = false;
            DinoJump = false;
            isDead = true;
            Dino->DinoRun->pause();
            Dino->DinoCrouch->pause();
            Dino->DinoDead->setY(Dino->DinoRun->getY());
            
            runningScore->timer->stop();
            score->timer->stop();
            score->compareAndSet();
            hiScore = score->getHighScore();
            
            //stops the secrete music if it's playing
            secretMusic->stop();
            
            //stops the audio file
            music->stop();
            
            //if music file not found, will throw error in console.
            if (!music->openFromFile("audio/Dead.wav")){
                std::cout<<"Audio file not found!"<<std::endl;
            }
            
            music->setLoop(false);
            
            //plays the audio file
            music->play();
            
            if(end == false){
                gameover->playOnce();
                end = true;
            }
        }
    }
}

void Obsticle::checkCactusHit(Dinosaur* Dino, Obsticle* obsticle, bool& isGameOn, bool& DinoJump, bool& isDead, bool& end, AnimatedRect* gameover, Score* score, std::string& hiScore, sf::Music* music, Score* runningScore, sf::Music* secretMusic){
    
    if(Dino->DinoRun->animating == false){
        //DO NOTHING!!!
    }
    else{
        if(obsticle->Cactus->contains((Dino->DinoRun->getX() + Dino->DinoRun->getW()), (Dino->DinoRun->getY() - Dino->DinoRun->getH())) || obsticle->Cactus->contains((Dino->DinoRun->getX() + Dino->DinoRun->getW()), (Dino->DinoRun->getY())) || obsticle->Cactus->contains((Dino->DinoRun->getX()), (Dino->DinoRun->getY() - Dino->DinoRun->getH())) || obsticle->Cactus->contains(Dino->DinoRun->getX(), Dino->DinoRun->getY())){
            isGameOn = false;
            DinoJump = false;
            isDead = true;
            Dino->DinoRun->pause();
            Dino->DinoCrouch->pause();
            Dino->DinoDead->setY(Dino->DinoRun->getY());
            
            runningScore->timer->stop();
            score->timer->stop();
            score->compareAndSet();
            hiScore = score->getHighScore();
            
            //stops the secrete music if it's playing
            secretMusic->stop();
            
            //stops the audio file
            music->stop();
            
            //if music file not found, will throw error in console.
            if (!music->openFromFile("audio/Dead.wav")){
                std::cout<<"Audio file not found!"<<std::endl;
            }
            
            music->setLoop(false);
            
            //plays the audio file
            music->play();
            
            if(end == false){
                gameover->playOnce();
                end = true;
            }
        }
    }
    
    if (Dino->DinoCrouch->animating == false) {
        //DO NOTHING!!!
    }
    else{
        if(obsticle->Cactus->contains((Dino->DinoCrouch->getX() + Dino->DinoCrouch->getW()), (Dino->DinoCrouch->getY() - Dino->DinoCrouch->getH())) || obsticle->Cactus->contains((Dino->DinoCrouch->getX() + Dino->DinoCrouch->getW()), (Dino->DinoCrouch->getY())) || obsticle->Cactus->contains((Dino->DinoCrouch->getX()), (Dino->DinoCrouch->getY() - Dino->DinoCrouch->getH())) || obsticle->Cactus->contains(Dino->DinoCrouch->getX(), Dino->DinoCrouch->getY())){
            isGameOn = false;
            DinoJump = false;
            isDead = true;
            Dino->DinoRun->pause();
            Dino->DinoCrouch->pause();
            Dino->DinoDead->setY(Dino->DinoRun->getY());
            
            runningScore->timer->stop();
            score->timer->stop();
            score->compareAndSet();
            hiScore = score->getHighScore();
            
            //stops the secrete music if it's playing
            secretMusic->stop();
            
            //stops the audio file
            music->stop();
            
            //if music file not found, will throw error in console.
            if (!music->openFromFile("audio/Dead.wav")){
                std::cout<<"Audio file not found!"<<std::endl;
            }
            
            music->setLoop(false);
            
            //plays the audio file
            music->play();
            
            if(end == false){
                gameover->playOnce();
                end = true;
            }
        }
    }
}
