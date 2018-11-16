#include "Score.h"
#include "cxxtimer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

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

std::string Score::getHighScore(){
    return hiScore;
}

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

std::string Score::getCurrScore(){
    return currScore;
}

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
