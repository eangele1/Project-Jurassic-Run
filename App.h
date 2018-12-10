#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"


class App: public GlutApp {
    
    AnimatedRect* Title;
    AnimatedRect* gameover;
    
public:
    App(int argc, char** argv);
    
    void draw();
    
    void idle();
    
    void keyDown(unsigned char key, float x, float y);
    
    void keyUp(unsigned char key, float x, float y);
    
    ~App();
    
};

#endif
