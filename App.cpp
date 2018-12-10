#include <iostream>
#include "App.h"
#include "Dino.h"
#include "Environment.h"
#include "Obsticle.h"
#include <string>
#include "cxxtimer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Score.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

std::string hi = "HI";
std::string curr = "CURR";
std::string hiScore;
std::string currScore;

bool isGameOn = false;
bool isDead = false;
bool DinoJump = false;
bool isCrouched = false;

int flag = 0;

int objectSwitch = 0;

bool intro = false;
bool end = false;

int i = 0;

int controllerFlag = 1;
int controllerSoundHandler = 0;

long long scoreNum;

//Instantiate a new audio file
sf::Music* music = new sf::Music();

sf::SoundBuffer* buffer1 = new sf::SoundBuffer();
sf::Sound* sound1 = new sf::Sound();

sf::SoundBuffer* buffer2 = new sf::SoundBuffer();
sf::Sound* sound2 = new sf::Sound();

int playerPort = 0;

Score* score = new Score();
Score* runningScore = new Score();

Dinosaur* Dino = new Dinosaur();
Background* background = new Background();
Obsticle* obsticle = new Obsticle();

App::App(int argc, char** argv): GlutApp(argc, argv){
    
    //if music file not found, will throw error in console.
    if (!music->openFromFile("audio/Main Menu.wav")){
        std::cout<<"Audio file not found!"<<std::endl;
    }
    
    //makes audio loop (only loops from beginning to end, not at loop points)
    music->setLoop(true);
    
    //sets audio volume. Default is at 70; max is at 100.
    music->setVolume(70);
    
    //plays the audio file
    music->play();
    
    sound1->setVolume(50);
    
    for(int i = 0; i < 8; i++){
        sf::Joystick::update();
        if(sf::Joystick::isConnected(i)){
            std::cout << "Controller port " << i + 1 << " is connected." <<std::endl;
            
            std::string str = sf::Joystick::getIdentification(i).name;
            
            std::transform(str.begin(), str.end(),str.begin(), ::toupper);
            
            unsigned int buttonCount = sf::Joystick::getButtonCount(i);
            
            std::cout << "Controller Name: " << str << std::endl;
            std::cout << "# of Buttons: " << buttonCount << std::endl;
            
            std::cout << "Controller port " << i + 1 << " is the current player." << std::endl;
            
            playerPort = i;
        }
        else{
            std::cout << "Controller port " << i + 1 << " is not connected." <<std::endl;
        }
    }
    
    //make keyboard key hold, but not repeat
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    
    //Dino graphics
    Dino->DinoRun = new AnimatedRect("Textures/dinoRun.png", 1, 2, 100, -0.5, -0.5, 0.2, 0.2);
    Dino->DinoCrouch = new AnimatedRect("Textures/dinoCrouch.png", 1, 2, 100, -0.5, -0.55, 0.25, 0.15);
    Dino->DinoStand = new TexRect("Textures/dinoStand.png", -0.5, -0.5, 0.2, 0.2);
    Dino->DinoDead = new TexRect("Textures/dinoDead.png", -0.5, -0.5, 0.2, 0.2);
    
    //Background graphics
    background->Main.push_back(new TexRect("Textures/Desert.png", -1, 1, 2, 2));
    background->Repeat.push_back(new TexRect("Textures/Desert.png", 0.99, 1, 2, 2));
    
    background->Main.push_back(new TexRect("Textures/Greenfields.png", -1, 1, 2, 2));
    background->Repeat.push_back(new TexRect("Textures/Greenfields.png", 0.99, 1, 2, 2));
    
    background->Main.push_back(new TexRect("Textures/Forest.png", -1, 1, 2, 2));
    background->Repeat.push_back(new TexRect("Textures/Forest.png", 0.99, 1, 2, 2));
    
    background->Main.push_back(new TexRect("Textures/Volcano.png", -1, 1, 2, 2));
    background->Repeat.push_back(new TexRect("Textures/Volcano.png", 0.99, 1, 2, 2));
    
    background->Main.push_back(new TexRect("Textures/Stars.png", -1, 1, 2, 2));
    background->Repeat.push_back(new TexRect("Textures/Stars.png", 0.99, 1, 2, 2));
    
    //Obsticle graphics
    obsticle->Cactus = new TexRect("Textures/cactus.png", 1, -0.5, 0.2, 0.2);
    obsticle->Bird = new AnimatedRect("Textures/bird.png", 1, 2, 100, 1, -0.325, 0.2, 0.2);
    
    //Title and Game Over graphics
    Title = new AnimatedRect("Textures/title.png", 7, 5, 35, -0.55, 1, 1.25, 1);
    gameover = new AnimatedRect("Textures/gameover.png", 28, 5, 15, -0.65, 0.5, 1.25, 0.5);
    
    //get high score at the beginning
    hiScore = score->getHighScore();
    
    obsticle->advanceRate = 0.001;
    background->advanceRate = 0.001;
    
    if (!buffer1->loadFromFile("sound/100 Points.wav")){
        std::cout<<"Sound file not found!"<<std::endl;
    }
    sound1->setBuffer(*buffer1);
    
    if (!buffer2->loadFromFile("sound/Jump.wav")){
        std::cout<<"Sound file not found!"<<std::endl;
    }
    sound2->setBuffer(*buffer2);
}

//used to write text in the window
void drawString (void * font, std::string *s, float x, float y){
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < s->length(); i++)
        glutBitmapCharacter (font, s->at(i));
}

void App::idle(){
    
    sf::Joystick::update();
    
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    
    if(sf::Joystick::isButtonPressed(playerPort, 1) && controllerSoundHandler == 0){
        if(isGameOn == true){
            DinoJump = true;
            sound2->play();
            controllerSoundHandler = 1;
        }
    }
    else if(!sf::Joystick::isButtonPressed(playerPort, 1) && controllerSoundHandler == 1){
        controllerSoundHandler = 0;
    }
    
    if(y == 100){
        if(isGameOn == true && controllerFlag == 1){
            isCrouched = true;
            Dino->fallRate = 0.003;
            Dino->crouch(Dino);
            controllerFlag = 0;
        }
    }
    else{
        if(isGameOn == true && controllerFlag == 0){
            isCrouched = false;
            Dino->fallRate = 0.0015;
            Dino->crouchUp(Dino);
            controllerFlag = 1;
        }
    }
    
    if(sf::Joystick::isButtonPressed(playerPort, 9)){
        
        if(isGameOn == false){
            //stops the audio file
            music->stop();
            
            //if music file not found, will throw error in console.
            if (!music->openFromFile("audio/Run Theme.wav")){
                std::cout<<"Audio file not found!"<<std::endl;
            }
            
            //makes audio loop (only loops from beginning to end, not at loop points)
            music->setLoop(true);
            
            //plays the audio file
            music->play();
            
            i = 0;
            
            isCrouched = false;
            end = false;
            isDead = false;
            DinoJump = true;
            
            score->timer->reset();
            score->timer->start();
            
            runningScore->timer->reset();
            runningScore->timer->start();
            
            obsticle->Bird->setX(1);
            obsticle->Cactus->setX(1);
            
            obsticle->Bird->playLoop();
            Dino->DinoRun->playLoop();
        }
        
        isGameOn = true;
        
    }
    
    glutPostRedisplay();
    
    score->setCurrScore(isGameOn);
    currScore = score->getCurrScore();
    
    scoreNum = runningScore->timer->count<std::chrono::microseconds>();
    
    scoreNum /= 100000;
    
    if(intro == false){
        Title->playOnce();
        intro = true;
    }
    
    if(isGameOn == true){
        
        background->advance(background);
        
        if(scoreNum % 100 == 0 && scoreNum != 0){
            sound1->play();
        }
        
        if(scoreNum % 200 == 0 && scoreNum != 0 && scoreNum % 1000 != 0 && i < 1){
            i = 1;
        }
        else if(scoreNum % 400 == 0 && scoreNum != 0 && scoreNum % 1000 != 0 && i < 2){
            i = 2;
        }
        else if(scoreNum % 600 == 0 && scoreNum != 0 && scoreNum % 1000 != 0 && i < 3){
            i = 3;
        }
        else if(scoreNum % 800 == 0 && scoreNum != 0 && scoreNum % 1000 != 0 && i < 4){
            i = 4;
        }
        else if(scoreNum % 1000 == 0 && scoreNum != 0 && i < 5 && i != 0){
            i = 0;
        }
        
        if(scoreNum == 1000){
            runningScore->timer->stop();
            runningScore->timer->reset();
            runningScore->timer->start();
        }
        
        if(scoreNum > 30){
            if(objectSwitch == 0){
                obsticle->cactusAdvance(obsticle);
                if(obsticle->Cactus->getX() <= -1.2){
                    objectSwitch = 1;
                }
            }
            else{
                obsticle->birdAdvance(obsticle);
                if(obsticle->Bird->getX() <= -1.2){
                    objectSwitch = 0;
                }
            }
            
        }
        
        obsticle->checkBirdHit(Dino, obsticle, isGameOn, DinoJump, isDead, end, gameover, score, hiScore, music, runningScore);
        obsticle->checkCactusHit(Dino, obsticle, isGameOn, DinoJump, isDead, end, gameover, score, hiScore, music, runningScore);
        
    }

    if(DinoJump){
        Dino->jump(Dino, flag, DinoJump);
    }
    
}

void App::draw() {
    
    //gives the text the color white
    glColor3f(1, 1, 1);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &hi, .1, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &curr, .47, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &hiScore, .22, .75);
    
    drawString(GLUT_BITMAP_TIMES_ROMAN_24, &currScore, .72, .75);
    
    if(i == 0){
        background->Main[0]->draw(0);
        background->Repeat[0]->draw(0);
    }
    else if(i == 1){
        background->Main[1]->draw(0);
        background->Repeat[1]->draw(0);
    }
    else if(i == 2){
        background->Main[2]->draw(0);
        background->Repeat[2]->draw(0);
    }
    else if(i == 3){
        background->Main[3]->draw(0);
        background->Repeat[3]->draw(0);
    }
    else{
        background->Main[4]->draw(0);
        background->Repeat[4]->draw(0);
    }
    
    obsticle->Cactus->draw(0.15);
    obsticle->Bird->draw(0.15);
    
    if(isGameOn == false){
        
        if(isDead){
            Dino->DinoDead->draw(0.15);
            gameover->draw(0.15);
        }
        else{
            Dino->DinoStand->draw(0.15);
            Title->draw(0.15);
        }
    }
    
    if(isCrouched == true){
        Dino->DinoCrouch->draw(0.15);
    }
    else{
        Dino->DinoRun->draw(0.15);
    }
    
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    
    if(key == '0'){
        //sets audio volume. Default is at 70; max is at 100.
        music->setVolume(0);
    }
    if(key == '9'){
        //sets audio volume. Default is at 70; max is at 100.
        music->setVolume(70);
    }
    
    if (key == 'b') {
        if(isGameOn == true){
            isCrouched = true;
            Dino->fallRate = 0.003;
            Dino->crouch(Dino);
        }
    }
    
    if (key == ' '){
        
        if(isGameOn == true){
            DinoJump = true;
            sound2->play();
        }
        
        if(isGameOn == false){
            
            //stops the audio file
            music->stop();
            
            //if music file not found, will throw error in console.
            if (!music->openFromFile("audio/Run Theme.wav")){
                std::cout<<"Audio file not found!"<<std::endl;
            }
            
            //makes audio loop (only loops from beginning to end, not at loop points)
            music->setLoop(true);
            
            //plays the audio file
            music->play();
            
            i = 0;
            
            isCrouched = false;
            end = false;
            isDead = false;
            DinoJump = true;
            
            score->timer->reset();
            score->timer->start();
            
            runningScore->timer->reset();
            runningScore->timer->start();
            
            obsticle->Bird->setX(1);
            obsticle->Cactus->setX(1);
            
            obsticle->Bird->playLoop();
            Dino->DinoRun->playLoop();
        }
        
        isGameOn = true;
    }
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
    delete Dino;
    delete background;
    delete obsticle;
    delete Title;
    delete gameover;
    delete score;
    delete music;
    delete buffer1;
    delete sound1;
    delete buffer2;
    delete sound2;
}

void App::keyUp(unsigned char key, float x, float y){
    if (key == 'b') {
        
        if(isGameOn == true){
            isCrouched = false;
            Dino->fallRate = 0.0015;
            Dino->crouchUp(Dino);
        }
    }
}
