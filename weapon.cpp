#include "weapon.h"

Weapon::Weapon(vector<position>&pos,object wt,double s)
{
    weapon.assign(pos.begin(),pos.end());
    weaponType = wt;
    speed = s;
}

void Weapon::setWeapon(vector<position>& pos)
{
    weapon.assign(pos.begin(),pos.end());
}
