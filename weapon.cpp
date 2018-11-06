#include "weapon.h"

Weapon::Weapon(vector<position>&pos,object wt,direction d,double s):weapon(pos),weaponType(wt),dir(d),speed(s){}

void Weapon::setWeapon(vector<position>& pos)
{
    weapon = pos;
}

void Weapon::move(Field& f)
{
    /*子弹更新规则
    1. 按照给定的向前平移
    2. 若遇到障碍物，判定武器的属性，是否穿过，消失，或者障碍物是否消失
    3. 若遇到墙体，直接消失
    4. 若遇到蛇体，判定子弹属性，是否造成伤害，或者debuff效果
    */
    position nhead = weapon[0] + Direction[dir];
    nhead.currect();

}
