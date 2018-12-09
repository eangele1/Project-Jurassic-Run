#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"


class App: public GlutApp {
    AnimatedRect* explosion;
    AnimatedRect* fastExplosion;
    AnimatedRect* Bird;
    bool isGameOn;
    
    
public:
    App(int argc, char** argv);
    
    void draw();
    
    void idle();
    
    void keyDown(unsigned char key, float x, float y);
    
    void setGameOn(bool progress){
        isGameOn = progress;
    }
    
    bool getGameOn(){
        return isGameOn;
    }
    
    ~App();
    
};

#endif
