
#ifndef __GAMEfinalproj__player__
#define __GAMEfinalproj__player__
#include <iostream>
using namespace std;
class player{
private:
    int health;
    string gun;
    string powerup;
    
public:
    player(){//base player stats
        health=10;
        gun="pistol";
        powerup="";
    }
    int gethealth();
    void sethealth(int health);
    
    void gethit(int damage);
    void gethealed(int health);
    
    string getgun();
    void setgun(string newgun);
    
    string getpowerup();
    void setpowerup(string powerup);
    
    
    
    
    
};
#endif