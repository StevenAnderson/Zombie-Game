
#include "zombie.h"


//how much damage a zombie does
int  zombie::getstrength(){
    return strength;
}
//setting the strength
void  zombie::setstrength(int strength){
    this->strength=strength;
}
//what damage each gun does
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
//color for each zombie (not used)
string  zombie::getcolor(){
    return color;
    
}
//color for each zombie (not used)
void  zombie::setcolor(string color){
    this->color=color;
    
}//gets location in relation to player
int  zombie::getlocation(){
    return location;
}//sets location in relation to player
void  zombie::setlocation(int location){
    this->location-=location;
    
}
//gets points a zombie is worth
int  zombie::getpoints(){
    return points;
    
}//sets points a zombie is worth
void  zombie::setpoints(int points){
    this->points=points;
}
//taking damage function
void zombie::getdamage(int damage){
    this->sethealth(this->gethealth()-damage);
    
}

