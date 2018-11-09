#include "weapon.h"
#include <map>

map<object,int> Map_WeaponMoveDistance{
    {WEAPON_Fire,5},
    {WEAPON_Bramble,3}
};

map<object,double> Map_WeaponTime{
    {WEAPON_Fire,10},
    {WEAPON_Bramble,20}
};

void Weapon::attack(Field& f)
{
    /*子弹更新规则
    1. 按照给定的向前平移
    2. 若遇到障碍物，判定武器的属性，是否穿过，消失，或者障碍物是否消失
    3. 若遇到墙体，直接消失
    4. 若遇到蛇体，判定子弹属性，是否造成伤害，或者debuff效果
    */
    if(f[weapon] == WALL){
        //樯:直接消失
        whetherExist = false;
    }
    else if(f[weapon] < FOOD_End && f[weapon] > WEAPON_Start){
        //食物:双向消失
        whetherExist = false;
        f.deleteFood(weapon);
    }
    else if(f[weapon] == OBSTACLE_Bramble){

    }
    else if(f[weapon] == OBSTACLE_Normal){

    }
}

void Weapon::move(Field& f)
{

    position nhead = weapon + Direction[dir];
    nhead.currect();

}
