#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#define Weapon_brambleDecelerateRate 0.6

#include "basic.h"
#include "field.h"

using namespace std;

class Weapon{
public:
    Weapon():dir(DNone),weaponType(WEAPON_Start),speed(0),gameTime(0){dis = 0;whetherExist = true;}
    Weapon(position p,object wt,direction d,double s,double time):dir(d),weapon(p),weaponType(wt),speed(s),gameTime(time){dis = 0;whetherExist = true;}

    inline position& getPosition(){return weapon;}
    inline object getType(){return weaponType;}

    inline void setPosition(position pos){weapon = pos;}
    inline void setType(object wt){weaponType = wt;}

    inline void setDirection(direction d){dir = d;}
    inline void setSpeed(double s){speed = s;}

    void attack(Field& f);
    void move(Field& f);
private:
    direction dir;
    position weapon;
    object weaponType;
    double speed;//移动速度
    double gameTime;//子弹发射时间
    int dis;
    bool whetherExist;
};

#endif // WEAPON_H_INCLUDED
