#include "Score.h"
#include "cxxtimer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

//sets high score from data in hiscore.txt
void Score::setHighScore(){
    std::ofstream file;
    file.open ("hiscore.txt");
    file << currScore;
    file.close();
    
    std::ifstream inFile;
    inFile.open("hiscore.txt");
    inFile >> hiScore;
    inFile.close();
}

//returns high score in a string
std::string Score::getHighScore(){
    return hiScore;
}

//sets current score using counting timer
void Score::setCurrScore(bool isGameOn){
    if(isGameOn == true){
        long long second = timer->count<std::chrono::microseconds>();
        
        if(second == 99999){
            timer->stop();
        }
        else{
            second /= 100000;
        }
        
        currScore = std::to_string(second);
    }
}

//returns current score in a string
std::string Score::getCurrScore(){
    return currScore;
}

//manipulates high score according to current score. if current score is greater than high score, set current score to high score, otherwise do nothing
void Score::compareAndSet(){
    std::stringstream geek(currScore);
    int currScore = 0;
    geek >> currScore;
    
    std::stringstream seek(hiScore);
    int prevHiScore = 0;
    seek >> prevHiScore;
    
    if(currScore > prevHiScore){
        setHighScore();
    }
}
