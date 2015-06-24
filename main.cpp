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
   // const int gunsize=4;
    int points=0;
    srand(time(NULL));//random numbers
    //string guns[gunsize]={"pistol", "shotgun", "uzi", "50 cal"};
    //string powerups[gunsize]={"heal", "TNT", "nuke", "insta-kill"};//Not needed??

    cout << "Zombie Slayer 1.5" << endl;//title
    
    string name; // player name
    int level=1; // level
    player p1=player();//creation of a basic player
    
    //intro
    cout << "Please enter your name:";
    getline (cin, name);
/// walkthrough for space
    
    cout << endl;
    cout << name << ", it is with great regret that I have to inform you the world has turned completely to zombies! Your survival is now completely in your own hands. Good Luck." << endl;
    //tutorial
    cout << endl;
    tutorial();
    cout << endl;
    
    //level while-loop // dependant on health //
    while ( p1.gethealth()>0){//level dependant text??
        cout << "LEVEL " << level << endl;
        cout << "Health: " << p1.gethealth()<< "    " << "Gun: " << p1.getgun()<< "    "  << "Powerups: " << p1.getpowerup()<< "    " << "Total Points: " << points << endl;
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
            if (gun==1||gun==2|| gun ==3|| gun==4)
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
        
        while (totzombies!=0){//loops until zombies are dead... or you are.
            fighting(droppedpowerup,  availablepowerup, p1, zombs , totzombies, droppedgun, availablegun, points);////fighting function!
            if ( p1.gethealth()<=0)/// for if the player dies, still exits loop.
                totzombies=0;
        }
        if ( p1.gethealth()>0){
            cout << "Zombie wave Level " << level << " Completed!" << endl;
                            }
        cout << endl;
        
       
        level++;
  }
    cout << "It appears you died..." << endl;
    cout << "Final Score: " << points << endl;
    cout << endl;

    fstream iofile ("/Users/Steven/Desktop/highscore.txt", ios::in|ios::out);
    if (!iofile)
    {   //if no file exists
        iofile.open("/Users/Steven/Desktop/highscore.txt", ios::out);
        cout<< "You are the first to play this game! New High Score!" << endl;
        //inputs score
        iofile << "1st " << name << " " << points << endl;
    }
    else {
        string first;
        vector<string> scores;
        //places every line in a vector
        while( getline (iofile, first)){
            scores.push_back(first);
        }//places first high score if none exist
        
        if (scores[0] == ""){
            cout<< "You are the first to play this game! New High Score!" << endl;
            
            iofile << "1st " << name << " " << points << endl;
            
        }
            
       else //loops for top 5 scores
       {for (int k=0; k<5; k++)
           if (scores[k]==""){
               string defaultplace;
               
               if (k==1)
                   defaultplace="2nd";
               if (k==2)
                   defaultplace="3rd";
               if (k==3)
                   defaultplace="4th";
               if (k==4)
                   defaultplace="5th";
                   
               cout << "Your score is " << defaultplace<< " place by default!" << endl;
               scores[k]=defaultplace+ " " +name+to_string(points);
           }
           else
        {
            string score="";
            string place="";
            first = scores[k];
            int i=0;
            // stores place (1st, 2nd, 3rd..) into string
            for (; first[i]!=' '; i++){ //place
                place+=first[i];
            }
            i++;//skippping blank space
            
            for (int j=0; first[i]!=' '; j++){// skipping name
                i++;}
            
            i++;//skippping blank space
            
            for (int j=0;first[i]!='\0' ; j++){//places score into string for comparison
                score+=first[i];
                i++;}

            if (score<to_string(points)){
                cout << "Congrats! You now have the " << place << " highest score!" << endl;
                string temp=scores[k];
                scores[k]=" "+ name +" "+ to_string(points);
                //switching the vector cells with the ones below um.
                for (int i=5; i>k ; i--) {
                    scores[i]=scores[i-1];
                }
                if (scores.size()==1)
                    scores.push_back(temp);
                else
                scores[k+1]=temp;
                
                k=5;//exits once it is greater than the current score
            }
    
            
        }
       }
        cout << "High Scores:" << endl;
        string outputplace;
        for (int i=0;i<5;i++)
        {
        
            if (i==1)
                outputplace="2nd";
            if (i==2)
                outputplace="3rd";
            if (i==3)
                outputplace="4th";
            if (i==4)
                outputplace="5th";
            if ( i==0){
                 outputplace="1st";
        iofile <<outputplace<< scores[i]<< endl;
            cout << outputplace<< scores[i] << endl;}
        else
            {//to cut off the previous rankings
                int l=3;
                string line=scores[i];
                iofile <<outputplace;
                cout<< outputplace<< " ";
                while(line[l]!=' '){
                    for (; l<100; l++)
                        {
                    iofile << line[l];
                            cout << line[l];
                        }
                }
                iofile<< endl;
                cout << endl;
                
            }
        }
    }
    
    //stacking powerups
    //more random dropping times (totzombie rand number/not=to last zomb)
    //iofile.flush();
    iofile.close();
    
    return 0;
}
void fighting(string& droppedpowerup, string&  availablepowerup, player& p1, vector<zombie>& zombs, int& totzombies, string& droppedgun,string&  availablegun, int& points){
    string command;
    int startingtot=totzombies;
    
    //cout << "Shoot them before you get eaten!" << endl;
    cout << "Command: ";
    cin >> command;
        if (command=="shoot")
        {zombs[totzombies-1].gethit(p1.getgun());//shoots farthest one
            cout << "Zombie hit!" << endl;
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
                cout << p1.getgun()<<" picked up!" << endl;
            }
            else
                cout << "No dropped gun" << endl;
            }
       else if (command=="nuke"){////nuke powerup
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
//////////from shoot command
    if (totzombies!=0){
    cout << "zombies shuffle closer towards you" << endl;
        if (zombs[totzombies-1].getlocation()>2)
        cout << "The closest zombie is " << zombs[totzombies-1].getlocation()-1 << " steps from you!"<< endl;
        else if  (zombs[totzombies-1].getlocation()==2)
            cout << "The closest zombie is " << zombs[totzombies-1].getlocation()-1 << " step from you!"<< endl;
            else
            cout << "The zombies are upon you!!"<< endl;
    }
    for (int i=0; i<startingtot; i++) {
        zombs[i].setlocation(1);
        if (zombs[i].getlocation()<=0 && zombs[i].gethealth()>0){
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
        cout << endl;
        cout<< "You have time to do one action before the zombies move closer to you!" << endl;
        cout<< "These actions are: 'shoot' 'pickupgun' 'pickuppowerup' 'usepowerup' and 'nuke'" << endl;
     //   cout << "Most of those are self explanatory. When you shoot and kill a zombie, theres a chance it will drop a power up or a gun, its here when you can pick these items up." << endl;
        cout << "While running for your live away from zombies, you discovered the launch-football for the worlds nukes" << endl;
        cout<< "When you are certain your doom is iminent, you can type 'nuke' and the world, all the zombies and you will be blown up." << endl;
        //cout<< "The command 'shoot' is obvious. You will always be shooting at the zombie closest to you" << endl;
            cout << endl;
        //picking up guns- different damage
       // cout << "WEAPONS:" << endl;
       // cout << "There are 4 different types of weapons: a pistol, a shotgun, an uzi, and a 50 cal." << endl;
       // cout << "These weapons do increasing damage each, with the shotgun hurting surrounding zombies and the 50 cal going through several at a time!" << endl;
       // cout << endl;
        //picking up powerups-different types
       // cout << "POWERUPS:" << endl;
       // cout<< "There are 3 types of powerups that will be dropped by zombies" << endl;
       // cout << "The first is HEALTH, this gives you 10 health points." << endl;
       // cout << "The second is TNT, this blows up and does blast damage on all the zombies near it." << endl;
       // cout << "The last is INSTA-KILL, this makes all zombies die after one shot." << endl;
       // cout << endl;
        //health and taking damage
       // cout << "The zombies can only start doing damage when they can reach you!" << endl;
         //   cout << endl;
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
    
}