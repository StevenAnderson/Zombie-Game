#include "player.h"
#include "zombie.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
void tutorial();
void usepowerup(string powerup, player& p1, vector<zombie>& zombs, int totzombies);
void fighting(string& droppedpowerup,string&  availablepowerup, player& p1, vector<zombie>& zombs, int& totzombies, string& droppedgun, string&  availablegun, int& points);

using namespace std;
int main (){
    const int gunsize=4;
    int points=0;
    srand(time(NULL));//random numbers
    string guns[gunsize]={"pistol", "shotgun", "uzi", "50 cal"};
    string powerups[gunsize]={"heal", "TNT", "nuke", "insta-kill"};//Not needed??

    cout << "Zombie Slayer 1.5" << endl;//title
    
    string name; // player name
    int level=1; // level
    player p1=player();//creation of a basic player
    
    //intro
    cout << "Please enter your name:";
    cin >> name;
    cout << endl;
    cout << name << ", it is with great regret that I have to inform you the world has turned completely to zombies! Your survival is now completely in your own hands. Good Luck." << endl;
    //tutorial
    cout << endl;
    tutorial();
    cout << endl;
    
    //level while-loop // dependant on health //
    while (p1.gethealth()>0){
        cout << "LEVEL " << level << endl;
        cout << "Health: " << p1.gethealth()<< "    " << "Gun: " << p1.getgun()<< "    "  << "Powerups: " << p1.getpowerup()<< "    " << "Total Points: " << points << endl;
        string droppedgun="";
        string droppedpowerup;
         vector<zombie> zombs;
        //level random numbers
       int addzombies=rand()% level;
        int totzombies=addzombies+level;//zombies in level
        int healthdif=rand()% level+1;//difficulty - for health
        
        //determining dropped gun if-statements
        int gun=rand()% 10;//guns
        if (p1.getgun()=="pistol")
        {
       if (gun==1||gun==2|| gun ==3||gun==4||gun==5)
           droppedgun="shotgun";
            else cout << "no gun picked" << endl;
        }
        else if (p1.getgun()=="shotgun"){
            if (gun==1||gun==2|| gun ==3|| gun==4)
                droppedgun="uzi";}
        else if (p1.getgun()=="uzi"){
            if (gun==1||gun==2)
                droppedgun="50 cal";}
        
    //determining dropped power up
        
        int powerup=rand()% 10;
        if (powerup==1||powerup==2)
            droppedpowerup="health";
        else if (powerup==4||powerup==5)
            droppedpowerup="TNT";
        else if (powerup==6)
            droppedpowerup="insta-kill";
        else if (powerup==8)
            droppedpowerup="nuke";
        
        string  availablepowerup;
        string  availablegun;
        cout << totzombies << " zombies suddenly appear heading towards you!" << endl;
        for (int i=totzombies;i>0;i--){//for-loop creating the number of zombie objects
            //health increases randomly, color is set, hit strenght is random, position makes it so no zombies are the same distance, points are static at the moment
            int hitstrength=rand()% level+1;//difficulty - for strength of hits - (strength of hits decides points)
            zombie z(5+healthdif,"green", hitstrength, 2+totzombies, hitstrength);
           
            zombs.push_back(z);
            
        }
        //combat portion of loop
        
        while (totzombies!=0){//loops until zombies are dead... or you are.
            fighting(droppedpowerup,  availablepowerup, p1, zombs , totzombies, droppedgun, availablegun, points);////fighting function!
            if (p1.gethealth()<=0)/// for if the player dies, still exits loop.
                totzombies=0;
        }
        if (p1.gethealth()>0){
            cout << "Zombie wave Level " << level << " Completed!" << endl;
                            }
        cout << endl;
        
       
        level++;
  }
    cout << "It appears you died..." << endl;
    cout << "Final Score: " << points << endl;
    
    
    //read in all the high scores into a vector
    //sort those vectors into order
    //clear file and read in new order
    //display if high score or not
    
    
    return 0;
}
void fighting(string& droppedpowerup, string&  availablepowerup, player& p1, vector<zombie>& zombs, int& totzombies, string& droppedgun,string&  availablegun, int& points){
    string command;
    int startingtot=totzombies;
    
    cout << "Shoot them before you get eaten!" << endl;
    cout << "Command: ";
    cin >> command;
        if (command=="shoot")//topzombie on vector is closest
        {zombs[totzombies-1].gethit(p1.getgun());//[totzombies-1]???????
            cout << "Zombie hit!" << endl;
                   }
      else if (command=="usepowerup")
            {
           
                if (p1.getpowerup()!=""){
            usepowerup( p1.getpowerup(), p1, zombs,  totzombies);
                    
                }
            else
                cout << "No powerup to use." << endl;
            }
       else if (command=="pickuppowerup")
            {
            if ( availablepowerup!="")
            {
            p1.setpowerup(availablepowerup);
                cout << "Powerup picked up!" << endl;
            }
            else
                cout << "No dropped powerup." << endl;
            }
       else if (command=="pickupgun")
            {
            if ( availablegun!="")
            {
            p1.setgun(availablegun);
                cout << "Gun picked up!" << endl;
                cout<< p1.getgun()<< " is registered." << endl;
            }
            else
                cout << "No dropped gun" << endl;
            }
    else
        cout << "Not valid command: " << command << endl;
    ///after command, zombies move or attack,
    ////////////
    for (int i=0; i<startingtot;i++)
    {
    if (zombs[totzombies-1].gethealth()<=0)
    {
        cout << "Zombie " << totzombies << " killed!" << endl;
        points+=zombs[totzombies-1].getpoints();
        totzombies--;
    
        if (droppedgun!="" && totzombies!=0)//to only drop the gun up once
        {   cout << "A weapon is dropped: " << droppedgun << " !" << endl;
            availablegun=droppedgun;
            droppedgun="";
        }
        if (droppedpowerup!="" && totzombies!=0)//to only drop the power up once
        {   cout << "A powerup is dropped: " << droppedpowerup << " !" << endl;
            availablepowerup=droppedpowerup;
            droppedpowerup="";
        }
    }
    }
//////////copied from shoot command
    if (totzombies!=0)
    cout << "zombies shuffle closer towards you" << endl;
    for (int i=0; i<startingtot; i++) {
        zombs[i].setlocation(1);
        if (zombs[i].getlocation()<=0 && zombs[i].gethealth()>=0){
            cout << "Zombie " << i+1 << " attacks and does " << zombs[i].getstrength() << " points of damage!!" << endl;
            p1.gethit(zombs[i].getstrength());
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}
void tutorial(){
    cout << "If you wish to have a short tutorial please enter 'yes' or 'no' : ";
    string yesno;
    cin >> yesno;
    if (yesno=="yes"){
        
        //shooting zombies-different types
        cout<< "You will always be shooting at the zombie closest to you" << endl;
        //picking up guns- different damage
        cout << "WEAPONS:" << endl;
        cout << "There are 4 different types of weapons: a pistol, a shotgun, an uzi, and a 50 cal." << endl;
        cout << "These weapons do increasing damage each, with the shotgun hurting surrounding zombies and the 50 cal going through several at a time!" << endl;
        cout << endl;
        //picking up powerups-different types
        cout << "POWERUPS:" << endl;
        cout<< "There are 4 types of powerups that will be dropped by zombies" << endl;
        cout << "The first is HEALTH, this gives you 4 health points." << endl;
        cout << "The second is TNT, this blows up and does blast damage on all the zombies near it." << endl;
        cout << "The third is NUKE, this blows up the entire world (You with it), but gives you points for all the remaining zombies!" << endl;
        cout << "The last is INSTA-KILL, this makes all zombies die after one shot." << endl;
        cout << endl;
        

        //health and taking damage
        
    }
    else if (yesno=="no")
        cout<< "Tutorial skipped."<< endl;
}

void usepowerup(string powerup, player& p1, vector<zombie>& zombs, int totzombies){
    if (powerup=="health"){///Heal powerup
        cout<< "Healed!" << endl;
        p1.gethealed(10);
        p1.setpowerup("");
    }
    
    else if (powerup=="insta-kill"){//instakill powerup
        cout<< "insta-kill activated" << endl;
        p1.setpowerup("");

        for (int i=0; i<totzombies;i++){
            zombs[i].sethealth(1);
        }
    }
    else if (powerup=="TNT")//////tnt powerup
    {
        cout<< "*Huge Explosion!*" << endl;
        p1.setpowerup("");

        for (int i=0; i<totzombies;i++){
            zombs[i].getdamage(5);
                                        }
    }
    else if (powerup=="nuke"){////nuke powerup
        cout << "There's no going back, are you sure?";
        string ans;
        cin >> ans;
        if (ans=="yes"||ans == "Yes" || ans == "Y" ||ans == "y")
        {
            for (int i=0; i<totzombies;i++){
                zombs[i].sethealth(0);
            }
            p1.sethealth(0);
            cout << "Yippe-ki-ya..*BOOM*" << endl;
        }
        else
            cout << "Looks like you chose to keep fighting! Good Luck" << endl;
        
    }
        
    
    
}