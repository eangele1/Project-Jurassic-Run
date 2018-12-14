#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdlib>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "App.h"
#include "Dino.h"
#include "Environment.h"
#include "Obsticle.h"
#include "cxxtimer.h"
#include "Score.h"
#include "PowerUp.h"

std::string hi = "HI";
std::string curr = "CURR";
std::string powerUpText = "FIRE AWAY!!!";
std::string powerUpTimer;
std::string hiScore;
std::string currScore;

bool isGameOn = false;
bool isDead = false;
bool DinoJump = false;
bool isCrouched = false;

bool powerUpAppear = false;
bool showPowerUpText = false;

int flag = 0;

int objectSwitch = 0;

bool intro = false;
bool end = false;

int i = 0;

int controllerFlag = 1;
int controllerSoundHandler = 0;
int controllerSoundHandler2 = 0;

long long scoreNum;
long long powerUpInitialTime = 5;

//Instantiate a new audio file
sf::Music* music = new sf::Music();

//Instantiate a new audio file
sf::Music* secretMusic = new sf::Music();

//Instantiate SFX
sf::SoundBuffer* buffer1 = new sf::SoundBuffer();
sf::Sound* sound1 = new sf::Sound();
sf::SoundBuffer* buffer2 = new sf::SoundBuffer();
sf::Sound* sound2 = new sf::Sound();
sf::SoundBuffer* buffer3 = new sf::SoundBuffer();
sf::Sound* itemGet = new sf::Sound();
sf::SoundBuffer* buffer4 = new sf::SoundBuffer();
sf::Sound* shoot = new sf::Sound();

//initialize player port of default controller connected
int playerPort = 0;

//Instantiate score keeping
Score* score = new Score();
Score* runningScore = new Score();

//Instantiate main game objects
Dinosaur* Dino = new Dinosaur();
Background* background = new Background();
Obsticle* obsticle = new Obsticle();
PowerUp* powerUp = new PowerUp();

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
    
    //Power up graphics
    powerUp->item = new TexRect("Textures/powerUp.png", 1, -0.2, 0.2, 0.2);
    
    powerUp->lasers = new std::vector<TexRect*>;
    powerUp->deleteLasers = new std::vector<std::vector<TexRect*>::iterator>;
    
    //Title and Game Over graphics
    Title = new AnimatedRect("Textures/title.png", 7, 5, 35, -0.6, 1, 1.25, 1);
    gameover = new AnimatedRect("Textures/gameover.png", 28, 5, 15, -0.65, 0.5, 1.25, 0.5);
    
    //get high score at the beginning
    hiScore = score->getHighScore();
    
    //initial frame advance rates
    obsticle->advanceRate = 0.001;
    background->advanceRate = 0.001;
    powerUp->advanceRate = 0.001;
    
    //loading sounds into memory
    if (!buffer1->loadFromFile("sound/100 Points.wav")){
        std::cout<<"Sound file not found!"<<std::endl;
    }
    sound1->setBuffer(*buffer1);
    
    if (!buffer2->loadFromFile("sound/Jump.wav")){
        std::cout<<"Sound file not found!"<<std::endl;
    }
    sound2->setBuffer(*buffer2);
    
    if (!buffer3->loadFromFile("sound/powerUpGet.wav")){
        std::cout<<"Sound file not found!"<<std::endl;
    }
    itemGet->setBuffer(*buffer3);
    
    if (!buffer4->loadFromFile("sound/fire.wav")){
        std::cout<<"Sound file not found!"<<std::endl;
    }
    shoot->setBuffer(*buffer4);
}

//used to write text in the window
void drawString (void * font, std::string *s, float x, float y){
    unsigned int i;
    glRasterPos2f(x, y);
    for (i = 0; i < s->length(); i++)
        glutBitmapCharacter (font, s->at(i));
}

void App::idle(){
    
    //updates gamepad connectivity all the time
    sf::Joystick::update();
    
    //gets position of joystick axis.
    float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    
    //A Button
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
    
    //B Button
    if(sf::Joystick::isButtonPressed(playerPort, 0) && controllerSoundHandler2 == 0){
        if(showPowerUpText){
            TexRect* laser = new TexRect("Textures/laser.png", Dino->DinoStand->getX() + 0.15, Dino->DinoRun->getY(), 0.2, 0.1);
            powerUp->lasers->push_back(laser);
            shoot->play();
            controllerSoundHandler2 = 1;
        }
    }
    else if(!sf::Joystick::isButtonPressed(playerPort, 0) && controllerSoundHandler2 == 1){
        controllerSoundHandler2 = 0;
    }
    
    //"Joysticks" or rather up and down buttons
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
            
            obsticle->advanceRate = 0.001;
            background->advanceRate = 0.001;
            powerUp->advanceRate = 0.001;
            
            score->timer->reset();
            score->timer->start();
            
            runningScore->timer->reset();
            runningScore->timer->start();
            
            obsticle->Bird->setX(1);
            obsticle->Cactus->setX(1);
            powerUp->item->setX(1);
            
            obsticle->Bird->playLoop();
            Dino->DinoRun->playLoop();
        }
        
        isGameOn = true;
        
    }
    
    //IMPORTANT FUNCTION!!! -> displays frames all the time in the game
    glutPostRedisplay();
    
    score->setCurrScore(isGameOn);
    currScore = score->getCurrScore();
    
    scoreNum = runningScore->timer->count<std::chrono::microseconds>();
    
    powerUpTimer = std::to_string(powerUpInitialTime - powerUp->timer->count<std::chrono::seconds>());
    
    scoreNum /= 100000;
    
    srand(static_cast<unsigned int>(time(0)));
    int randomNum = rand() % 2;
    
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
            obsticle->advanceRate += 0.0002;
            background->advanceRate += 0.0002;
            powerUp->advanceRate += 0.0002;
        }
        else if(scoreNum % 400 == 0 && scoreNum != 0 && scoreNum % 1000 != 0 && i < 2){
            i = 2;
            obsticle->advanceRate += 0.0002;
            background->advanceRate += 0.0002;
            powerUp->advanceRate += 0.0002;
        }
        else if(scoreNum % 600 == 0 && scoreNum != 0 && scoreNum % 1000 != 0 && i < 3){
            i = 3;
            obsticle->advanceRate += 0.0002;
            background->advanceRate += 0.0002;
            powerUp->advanceRate += 0.0002;
        }
        else if(scoreNum % 800 == 0 && scoreNum != 0 && scoreNum % 1000 != 0 && i < 4){
            i = 4;
            obsticle->advanceRate += 0.0002;
            background->advanceRate += 0.0002;
            powerUp->advanceRate += 0.0002;
        }
        else if(scoreNum % 1000 == 0 && scoreNum != 0 && i < 5 && i != 0){
            i = 0;
            obsticle->advanceRate += 0.0002;
            background->advanceRate += 0.0002;
            powerUp->advanceRate += 0.0002;
        }
        
        if(powerUp->timer->count<std::chrono::seconds>() == 5){
            powerUp->timer->stop();
            powerUp->timer->reset();
            showPowerUpText = false;
        }
        
        if((score->timer->count<std::chrono::microseconds>()/100000) > 30){
            
            if(scoreNum % 150 == 0 && scoreNum != 0){
                powerUpAppear = true;
            }
            
            if (powerUpAppear == true && obsticle->Cactus->getX() <= -1.2 && obsticle->Bird->getX() <= -1.2) {
                
                objectSwitch = 2;
                
                powerUp->powerUpAdvance(powerUp);
                
                if(powerUp->item->getX() <= -1.2){
                    objectSwitch = 0;
                    powerUpAppear = false;
                }
                
                if(powerUp->checkPowerUpGet(Dino, powerUp)){
                    objectSwitch = 0;
                    powerUpAppear = false;
                    showPowerUpText = true;
                    itemGet->play();
                }
            }
            
            if(objectSwitch == 0){
                obsticle->cactusAdvance(obsticle);
                if(obsticle->Cactus->getX() <= -1.2){
                    objectSwitch = randomNum;
                }
            }
            else if (objectSwitch == 1){
                obsticle->birdAdvance(obsticle);
                if(obsticle->Bird->getX() <= -1.2){
                    objectSwitch = randomNum;
                }
            }
            
        }
        
        if(scoreNum == 1000){
            runningScore->timer->stop();
            runningScore->timer->reset();
            runningScore->timer->start();
        }
        
        if((score->timer->count<std::chrono::microseconds>()/100000) == 2000){
            //stops the audio file
            music->stop();
            
            //if music file not found, will throw error in console.
            if (!secretMusic->openFromFile("audio/Run90s.wav")){
                std::cout<<"Audio file not found!"<<std::endl;
            }
            
            //makes audio loop (only loops from beginning to end, not at loop points)
            secretMusic->setLoop(true);
            
            secretMusic->setVolume(70);
            
            //plays the audio file
            secretMusic->play();
        }
        
        obsticle->checkBirdHit(Dino, obsticle, isGameOn, DinoJump, isDead, end, gameover, score, hiScore, music, runningScore, secretMusic, showPowerUpText);
        obsticle->checkCactusHit(Dino, obsticle, isGameOn, DinoJump, isDead, end, gameover, score, hiScore, music, runningScore, secretMusic, showPowerUpText);
        
    }
    
    for(std::vector<TexRect*>::iterator laserIterator = powerUp->lasers->begin(); laserIterator != powerUp->lasers->end(); laserIterator++){
        
        if(powerUp->checkLaserHit(powerUp, obsticle, laserIterator, objectSwitch) || (*laserIterator)->getX() >= 1){
            powerUp->lasers->erase(laserIterator);
            break;
        }
        else{
            (*laserIterator)->setX((*laserIterator)->getX() + 0.005);
        }
    }
    
    if(DinoJump){
        Dino->jump(Dino, flag, DinoJump);
    }
    
}

void App::draw() {
    
    //gives the text the color white
    glColor3f(1, 1, 1);
    
    if(showPowerUpText && isGameOn){
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, &powerUpText, -0.2, .25);
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, &powerUpTimer, 0, .1);
    }
    
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
    powerUp->item->draw(0.15);
    
    for(std::vector<TexRect*>::iterator laserIterator = powerUp->lasers->begin(); laserIterator != powerUp->lasers->end(); laserIterator++){
        (*laserIterator)->draw(0.15);
    }
    
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
    
    if(key == 'm'){
        if(showPowerUpText){
            TexRect* laser = new TexRect("Textures/laser.png", Dino->DinoStand->getX() + 0.15, Dino->DinoRun->getY(), 0.2, 0.1);
            powerUp->lasers->push_back(laser);
            shoot->play();
        }
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
            
            obsticle->advanceRate = 0.001;
            background->advanceRate = 0.001;
            powerUp->advanceRate = 0.001;
            
            score->timer->reset();
            score->timer->start();
            
            runningScore->timer->reset();
            runningScore->timer->start();
            
            obsticle->Bird->setX(1);
            obsticle->Cactus->setX(1);
            powerUp->item->setX(1);
            
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
    delete runningScore;
    delete music;
    delete buffer1;
    delete sound1;
    delete buffer2;
    delete sound2;
    delete buffer3;
    delete itemGet;
    delete buffer4;
    delete shoot;
    delete secretMusic;
    delete powerUp;
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
