#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include "field.h"

using namespace std;

class Weapon{
public:
    Weapon(){
        dir = DNone;
        weaponType = WEAPON_Start;
        speed = 0;
    }
    Weapon(vector<position>& w,object weaponType,direction d,double s = 0);

    inline vector<position>& getWeapon(){return weapon;}
    inline object getWeaponType(){return weaponType;}

    void setWeapon(vector<position>& pos);
    inline void setWeaponType(object wt){weaponType = wt;}
    inline void setDirection(direction d){dir = d;}
    inline void setSpeed(double s){speed = s;}

    void move(Field& f);
private:
    vector<position> weapon;
    object weaponType;
    direction dir;
    double speed;
};

#endif // WEAPON_H_INCLUDED
