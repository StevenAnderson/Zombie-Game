
#include "player.h"
//taking damage
void player::gethit(int damage){
    this->health-=damage;
    
}
//for health powerup
void player::gethealed(int health){
    this->health+=health;
}
// get gun
string player::getgun(){
    return gun;
    
}
//for picking up a new gun
void player::setgun(string newgun){
    this->gun=newgun;
    
}
//for using a powerup
string player::getpowerup(){
   if (powerup=="")
       cout<< "None";
    return powerup;
}
//picking up a powerup
void player::setpowerup(string powerup){
    this->powerup=powerup;
}