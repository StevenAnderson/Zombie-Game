 #include "player.h"
#include "zombie.h"
#include "living.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
void tutorial();
void usepowerup(string powerup, player& p1, vector<zombie>& zombs, int totzombies);
void fighting(string& droppedpowerup,string&  availablepowerup, player& p1, vector<zombie>& zombs, int& totzombies, string& droppedgun, string&  availablegun, int& points);

using namespace std;
int main (){
    int points=0;
    srand(time(NULL));//random numbers

    cout << "Zombie Slayer!" << endl;//title
    
    string name; // player name
    int level=1; // level
    player p1=player();//creation of a basic player
    
    //intro
    cout << "Please enter a codename:";
    cin >> name;
    cout << endl;
    cout << name << ", it is with great regret that I have to inform you the world has turned completely to zombies! Your survival is now completely in your own hands. Good Luck." << endl;
    //tutorial
    cout << endl;
    tutorial();
    cout << endl;
    
    //level while-loop // dependant on health //
    while ( p1.gethealth()>0){
        cout << "LEVEL " << level << endl;
        cout << "Health: " << p1.gethealth()<< "    " << "Gun: " << p1.getgun()<< "    "  << "Powerups: " << p1.getpowerup()<< "    " << "Total Points: " << points << endl;
        //variables for level
        string droppedgun="";
        string droppedpowerup;
        vector<zombie> zombs;
        
        //level random numbers
       int addzombies=rand()% level;
        int totzombies=addzombies+level;//zombies in level
        
        //determining dropped gun if-statements
        int gun=rand()% 10;//guns
        if (p1.getgun()=="pistol")
        {
       if (gun==1||gun==2|| gun ==3||gun==4||gun==5)
           droppedgun="shotgun";
        }
        else if (p1.getgun()=="shotgun"){
            if (gun==1||gun==2|| gun ==3)
                droppedgun="uzi";}
        else if (p1.getgun()=="uzi"){
            if (gun==1||gun==2)
                droppedgun="50 cal";}
        
    //determining dropped power up
        
        int powerup=rand()% 10;
        if (powerup==1||powerup==2||powerup ==3)
            droppedpowerup="health";
        else if (powerup==4||powerup==5)
            droppedpowerup="TNT";
        else if (powerup==6)
            droppedpowerup="insta-kill";
        //dropped items go into these variables
        string  availablepowerup;
        string  availablegun;
        
        cout << totzombies << " zombies suddenly appear heading towards you!" << endl;
        
        for (int i=0;i<totzombies;i++){//for-loop creating the number of zombie objects
            //health increases randomly, color is set, hit strenght is random, position makes it so no zombies are the same distance, points are static at the moment
            int hitstrength=rand()% level+1;//difficulty - for strength of hits - (strength of hits decides points)
            int healthdif=rand()% level+1;//difficulty - for health
            healthdif+=level;
            zombie z(4+healthdif,"green", hitstrength, 3+totzombies-i, hitstrength);
            zombs.push_back(z);
           }
        
        
        //combat portion of loop
            //has recursion built in, as long as theres zombies and p1 has health it'll loop
            fighting(droppedpowerup,  availablepowerup, p1, zombs , totzombies, droppedgun, availablegun, points);////fighting function!
      
        if ( p1.gethealth()>0){
            cout << "Zombie wave Level " << level << " Completed!" << endl;
                            }
        cout << endl;
        
       
        level++;
  }
    //once player health is <=0.
    cout << "It appears you died..." << endl;
    cout << "Final Score: " << points << endl;
    cout << endl;
    //connecting to highscore file
    fstream iofile ("highscore.txt", ios::in|ios::out);
    if (!iofile)
    {   //if no file exists
        iofile.open("highscore.txt", ios::out);
        cout<< "You are the first to play this game! New High Score!" << endl;
        //inputs score
        iofile.seekg( 0, ios::beg );
        iofile << "1st " << name << " " << points << endl;
        
    }
    else {
        string line;
        string score;
        int scores[5];
        string names[5];
        string place[5]={"1st ", "2nd ", "3rd ", "4th ", "5th "};
        
        //places every line in a vector
        int loop=0;
        while( getline (iofile, line)){
            
            
            int i=0;
            ///going over the place
            for (; line[i]!=' '; i++){} //place
            
            i++;//skippping blank space
            
            for (int j=0; line[i]!=' '; j++){// skipping name
                names[loop]+=line[i];
                i++;}
            
            i++;//skippping blank space
            
            for (int j=0;line[i]!='\0' ; j++){//places score into string for comparison
                scores[loop]*=10;
                scores[loop]+=line[i]-'0';
                i++;
            }
            
            loop++;
        }
        
        for (int i=0; i<5; i++) {
            if (points>scores[i])
            {   //swaps the scores up the arrray for new high score
                scores[i+1]=scores[i];
                scores[i]=points;
                string tempname=names[i];
                names[i+1]=names[i];
                names[i]=name;
                cout << "Congrats! You got the " << place[i] << " high score!" << endl;
                i=5;
            }
            
        }
        cout<< "High Scores:" << endl;
        iofile.clear();
        iofile.seekg( 0, ios::beg );
        //places new scores in file, outputs the new list as well
        for (int i=0; i<5; i++){
            iofile <<place[i]<< names[i]<< " " << scores[i]<< endl;
            cout<<place[i]<< names[i]<< " " << scores[i]<< endl;
        }
        
        
        
    }
    iofile.close();
    return 0;
}
//functions!!

//fighting function
void fighting(string& droppedpowerup, string&  availablepowerup, player& p1, vector<zombie>& zombs, int& totzombies, string& droppedgun,string&  availablegun, int& points){
    string command;
    int startingtot=totzombies;
        //prompts input from user
    cout << "Command: ";
    cin >> command;
        if (command=="shoot")
        {zombs[totzombies-1].gethit(p1.getgun());//shoots farthest one
            cout << "Zombie hit!" << endl;
            //damage for special guns (shotgun/50 cal)
            if (p1.getgun()=="shotgun")
            {
                if (totzombies>1){
                zombs[totzombies-2].getdamage(3);
                    if (totzombies>2)
                        zombs[totzombies-3].getdamage(2);
                        if (totzombies>3)
                            zombs[totzombies-4].getdamage(1);
                        }
                
            }
            if (p1.getgun()=="50 cal"){
                if(totzombies>1)
                    zombs[totzombies-2].getdamage(7);
                if (totzombies==11){
                    cout<< "Critical Headshot" << endl;
                    zombs[totzombies-1].getdamage(100);
                    for (int i=2; i<12; i++)
                    {
                    zombs[totzombies-i].getdamage(14-i);

                    }
                }

            }
            
            
        }
    //use powerup command
      else if (command=="usepowerup")
            {
                //if the player has a powerup
                if (p1.getpowerup()!=""){
            usepowerup( p1.getpowerup(), p1, zombs,  totzombies);
                    
                }
            else
                cout << "No powerup to use." << endl;
            }
    //pick up powerup command
       else if (command=="pickuppowerup")
            {//if theres one to pick up
            if ( availablepowerup!="")
            {
            p1.setpowerup(availablepowerup);
                cout << "Powerup picked up!" << endl;
            }
            else
                cout << "No dropped powerup." << endl;
            }
    //pick up gun command
       else if (command=="pickupgun")
            {
                //if a gun is available
            if ( availablegun!="")
            {
            p1.setgun(availablegun);
                cout << p1.getgun()<<" picked up!" << endl;
            }
            else
                cout << "No dropped gun" << endl;
            }
    
       else if (command=="nuke"){////nuke powerup
           cout << "There's no going back, are you sure?";
           string ans;
           cin >> ans;
           //different responses
           if (ans=="yes"||ans == "Yes" || ans == "Y" ||ans == "y")
           {    //all zombies die
               for (int i=0; i<totzombies;i++){
                   zombs[i].sethealth(0);
               }//player dies
               p1.sethealth(0);
               cout << "Yippe-ki-ya..*BOOM*" << endl;
           }
           else//if response in not yes.
               cout << "Looks like you chose to keep fighting! Good Luck" << endl;
           
       }
    //if swear words, player dies
       else if (command=="shit" ||command=="damn" ||command=="bitch" ||command=="fuck"){
           cout<< "Cussing Kills!"  << endl;
           cout << "A zombie comes out of nowhere and bites your head off!" << endl;
           p1.sethealth(0);
           
       }
    
    else
        cout << "Zombies see your poor command skills and laugh!" << endl;
    
    ///after command, zombies move or attack,
    ////////////
    for (int i=0; i<startingtot;i++)
    {
        //checking to see if any zombies were killed
    if (zombs[totzombies-1].gethealth()<=0)
    {//when a zombie dies
        cout << "Zombie " << totzombies << " killed!" << endl;
        points+=zombs[totzombies-1].getpoints();
        totzombies--;
        //if an item is dropped
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
    // if there are still zombies and the player is alive
    //zombies move closer
    if (totzombies!=0&& p1.gethealth()>0){
    cout << "zombies shuffle closer towards you" << endl;
        if (zombs[totzombies-1].getlocation()>2)
        cout << "The closest zombie is " << zombs[totzombies-1].getlocation()-1 << " steps from you!"<< endl;
        else if  (zombs[totzombies-1].getlocation()==2)
            cout << "The closest zombie is " << zombs[totzombies-1].getlocation()-1 << " step from you!"<< endl;
            else
            cout << "The zombies are upon you!!"<< endl;
    }
    //moving the zombies closer to the player
    for (int i=0; i<startingtot; i++) {
        zombs[i].setlocation(1);
        if (zombs[i].getlocation()<=0 && zombs[i].gethealth()>0){
            cout << "Zombie " << i+1 << " attacks and does " << zombs[i].getstrength() << " points of damage!!" << endl;
            p1.gethit(zombs[i].getstrength());
        }
    }
    //recursion
    while (totzombies!=0 && p1.gethealth()>0){//loops until zombies are dead... or you are.
        fighting(droppedpowerup,  availablepowerup, p1, zombs , totzombies, droppedgun, availablegun, points);////fighting function!
    
    }
}
//had a long tutorial, decided shorter is better
void tutorial(){
    cout << "If you wish to have a short tutorial please enter 'yes' or 'no' : ";
    string yesno;
    cin >> yesno;
    if (yesno=="yes"){
        
        //shooting zombies-different types
        cout << endl;
        cout<< "You have time to do one action before the zombies move closer to you!" << endl;
        cout<< "These actions are: 'shoot' 'pickupgun' 'pickuppowerup' 'usepowerup' and 'nuke'" << endl;
     //nuke
        cout << "While running for your live away from zombies, you discovered the launch-football for the worlds nukes" << endl;
        cout<< "When you are certain your doom is iminent, you can type 'nuke' and the world, all the zombies and you will be blown up." << endl;
            cout << endl;
           }
    else
        cout<< "Tutorial skipped."<< endl;
}
// using powerups function
void usepowerup(string powerup, player& p1, vector<zombie>& zombs, int totzombies){
    if (powerup=="health"){///Heal powerup
        cout<< "Healed!" << endl;
        p1.gethealed(10);//adds 10 points of health
        p1.setpowerup("");//deletes powerup, otherwise infinite
    }
    
    else if (powerup=="insta-kill"){//instakill powerup
        cout<< "insta-kill activated" << endl;
        p1.setpowerup("");
        //instakill sets all zombies health to 1
        for (int i=0; i<totzombies;i++){
            zombs[i].sethealth(1);
        }
    }
    else if (powerup=="TNT")//////tnt powerup
    {
        cout<< "*Huge Explosion!*" << endl;
        p1.setpowerup("");

        for (int i=0; i<totzombies;i++){
            zombs[i].getdamage(5);//does 5 damage to every zombie
                                        }
    }
    
}