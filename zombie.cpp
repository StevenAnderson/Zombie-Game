
#include "zombie.h"



int  zombie::getstrength(){
    return strength;
}
void  zombie::setstrength(int strength){
    this->strength=strength;
}

void  zombie::gethit(string gun){
    if (gun=="pistol")
        this->health-=4;
   else if (gun=="shotgun")
        this->health-=8;
   else if (gun=="uzi")
        this->health-=16;
   else if (gun=="50 cal")
        this->health-=20;
    else
        cout << "Error, no specified gun" <<endl;
}

string  zombie::getcolor(){
    return color;
    
}
void  zombie::setcolor(string color){
    this->color=color;
    
}
int  zombie::getlocation(){
    return location;
}
void  zombie::setlocation(int location){
    this->location-=location;
    
}

int  zombie::getpoints(){
    return points;
    
}
void  zombie::setpoints(int points){
    this->points=points;
}

void zombie::getdamage(int damage){
    this->sethealth(this->gethealth()-damage);
    
}

