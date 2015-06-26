
#ifndef __GAMEfinalproj__zombie__
#define __GAMEfinalproj__zombie__
#include <iostream>
#include "player.h"
#include "living.h"

using namespace std;
//inheritance of health functions
class zombie : public living {
private:
    
    string color;
    int strength;
    int location;
    int points;
    
public:
    //constructors
    zombie (){//small
        health=10;
        color="green";
        strength=1;
        location=3;
        points =2;
    }
    zombie(string size="medium"){//medium
        health=14;
        color="blue";
        strength=2;
        location=4;
        points =4;
    }
    zombie(int large){//large
        health=20;
        color="red";
        strength=5;
        location=5;
        points =8;
    }
    zombie(int health, string color, int strength, int location, int points){//custom/boss zombie
        this->health=health;
        this->color=color;
        this->strength=strength;
        this->location=location;
        this->points=points;
    }
    
    //calling functions
    int getstrength();
    void setstrength(int strength);

    void gethit(string gun);
    void getdamage(int damage);

    
    string getcolor();
    void setcolor(string color);
    
    int getlocation();
    void setlocation(int location);
    
    int getpoints();
    void setpoints(int points);
    
};
#endif