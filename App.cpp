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

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    mx = 0.0;
    my = 0.0;
    
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

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    //gives the text the color white
    glColor3f(1, 1, 1);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &hi, .1, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &curr, .47, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &hiScore, .22, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &currScore, .72, .75);
    
    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::mouseDown(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::mouseDrag(float x, float y){
    // Update app state
    mx = x;
    my = y;
    
    // Redraw the scene
    redraw();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }
    
    if(key == 32){
        
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
