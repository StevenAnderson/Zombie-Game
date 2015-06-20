
#include "player.h"
int player::gethealth(){
    return health;
}
void player::sethealth(int health){
    this->health=health;
}

void player::gethit(int damage){
    this->health-=damage;
    
}
void player::gethealed(int health){
    this->health+=health;
}

string player::getgun(){
    return gun;
    
}
void player::setgun(string newgun){
    this->gun=newgun;
    
}

string player::getpowerup(){
   if (powerup=="")
       cout<< "None";
    return powerup;
}
void player::setpowerup(string powerup){
    this->powerup=powerup;
}