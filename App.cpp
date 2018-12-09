#include "App.h"
#include <string>
#include "cxxtimer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Score.h"
#include "Environment.h"

#include "DinosaurFunctions.h"
#include "TexRect.h"
#include "App.h"


Score* score = new Score();
Environment* background = new Environment();
Moves* FunctionsDino = new Moves();

std::string hi = "HI";
std::string curr = "CURR";
std::string hiScore;
std::string currScore;

long long scoreNum;

bool isGameOn = false;


App::App(int argc, char** argv): GlutApp(argc, argv){
    //explosion = new AnimatedRect("fireball.bmp", 6, 6, 100, -0.5, 0.5, 0.5, 0.5);
   // fastExplosion = new AnimatedRect("fireball.bmp", 6, 6, 10, 0.5, 0.5, 0.5, 0.5);
    //This is for explosion
    
    hiScore = score->getHighScore();
}

//used to write text in the window
void drawString (void * font, std::string *s, float x, float y){
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < s->length(); i++)
        glutBitmapCharacter (font, s->at(i));
}

//used to update screen for timer and graphics
void App::idle(){
    glutPostRedisplay();
    score->setCurrScore(isGameOn);
    currScore = score->getCurrScore();
    
    scoreNum = score->timer->count<std::chrono::microseconds>();
    
    scoreNum /= 100000;
}

void App::draw() {
    //explosion->draw(0.15);
    //fastExplosion->draw(0.15);
    
    
    //Part that are comented out
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    //gives the text the color white
    glColor3f(1, 1, 1);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &hi, .1, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &curr, .47, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &hiScore, .22, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &currScore, .72, .75);
    
    if(scoreNum > 40){
        TexRect* Cactus = new TexRect("cactus.png", -.7, -0.1, .2, .2 );
        Cactus->draw(0);
        //Randomizer
        
    }
    if(scoreNum > 500)
    {
        Bird = new AnimatedRect("Bird.png", 1, 2, 100, -.5, -.2, .5, .5);
        Bird->draw(.15);
    }
    
    
    background->Background();
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
    
    if (key == ' '){
        //fastExplosion->playOnce();
        //explosion->playOnce();
        
        FunctionsDino->DrawDino();
        
        FunctionsDino->jump();
        
        
        if(isGameOn == false)
        {
            
            //reset and start timer
            score->timer->reset();
            score->timer->start();
            background->timer->reset();
            background->timer->start();
        }
        
        //turn on game
        isGameOn = true;
    }
    
    if(key == 'q'){
        if(isGameOn == true){
            
            //stop timer and manipulate score accordingly
            background->timer->stop();
            score->timer->stop();
            score->compareAndSet();
            hiScore = score->getHighScore();
            
            //The Dinosaur start appearing
            //FunctionsDino->Playloop();
            
        }
        
        //turn off game
        isGameOn = false;
    }
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
    delete score;
    delete FunctionsDino;
    //delete explosion;
    //delete fastExplosion;
}
