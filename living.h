
#ifndef __GAMEfinalproj__living__
#define __GAMEfinalproj__living__
#include <iostream>
using namespace std;
//common traits for player and zombie classes
class living{
protected:
    int health;
    
public:
    int gethealth();
    void sethealth(int sethealth);
    
};


#endif