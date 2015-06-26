
#ifndef __GAMEfinalproj__player__
#define __GAMEfinalproj__player__
#include <iostream>
#include "living.h"

using namespace std;
// inheritance of health functions
class player : public living {
private:
    string gun;
    string powerup;
    
public:
    player(){//base player stats
        health=10;
        gun="pistol";
        powerup="";
    }

    //function calls
    void gethit(int damage);
    void gethealed(int health);
    
    string getgun();
    void setgun(string newgun);
    
    string getpowerup();
    void setpowerup(string powerup);
    
    
    
    
    
};
#endif