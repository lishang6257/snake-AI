#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED
#include "position.h"
#include <vector>

using namespace std;

class Weapon{
public:
    Weapon(){
        weaponType = WEAPON_Start;
        speed = 0;
    }
    Weapon(vector<position>& w,object weaponType,double s = 0);

    inline vector<position>& getWeapon(){return weapon;}
    inline object getWeaponType(){return weaponType;}

    void setWeapon(vector<position>& pos);
    inline void setSpeed(double s){speed = s;};
private:
    vector<position> weapon;
    object weaponType;
    double speed;
};

#endif // WEAPON_H_INCLUDED
