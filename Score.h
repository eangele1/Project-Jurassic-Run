#ifndef Score_h
#define Score_h

#include <string>
#include "cxxtimer.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

class Score{
  
private:
    std::string currScore;
    std::string hiScore;
    
public:
    
    cxxtimer::Timer* timer = new cxxtimer::Timer();
    
    Score(){
        std::ifstream inFile;
        inFile.open("hiscore.txt");
        inFile >> hiScore;
        inFile.close();
    }
    
    std::string getHighScore();
    void setHighScore();
    std::string getCurrScore();
    void setCurrScore(bool isGameOn);
    
    void compareAndSet();
    
    ~Score(){}
    
};

#endif
