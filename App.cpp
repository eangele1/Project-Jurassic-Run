#include "App.h"
#include <string>
#include "cxxtimer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Score.h"

Score* score = new Score();

std::string hi = "HI";
std::string curr = "CURR";
std::string hiScore;
std::string currScore;

bool isGameOn = false;

App::App(int argc, char** argv): GlutApp(argc, argv){
    //explosion = new AnimatedRect("fireball.bmp", 6, 6, 100, -0.5, 0.5, 0.5, 0.5);
    //fastExplosion = new AnimatedRect("fireball.bmp", 6, 6, 10, 0.5, 0.5, 0.5, 0.5);
    hiScore = score->getHighScore();
}

//used to write text in the window
void drawString (void * font, std::string *s, float x, float y){
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < s->length(); i++)
        glutBitmapCharacter (font, s->at(i));
}

void App::idle(){
    score->setCurrScore(isGameOn);
    currScore = score->getCurrScore();
}

void App::draw() {
    //explosion->draw(0.15);
    //fastExplosion->draw(0.15);
    
    // Set background color to black
    glClearColor(1.0, 1.0, 1.0, 1.0);
    
    //gives the text the color white
    glColor3f(0, 0, 0);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &hi, .1, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &curr, .47, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &hiScore, .22, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &currScore, .72, .75);
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
    
    if (key == ' '){
        //fastExplosion->playOnce();
        //explosion->playOnce();
        
        if(isGameOn == false){
            score->timer->reset();
            score->timer->start();
        }
        
        isGameOn = true;
    }
    
    if(key == 'q'){
        if(isGameOn == true){
            score->timer->stop();
            score->compareAndSet();
            hiScore = score->getHighScore();
        }
        
        isGameOn = false;
    }
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
    //delete explosion;
    //delete fastExplosion;
}
