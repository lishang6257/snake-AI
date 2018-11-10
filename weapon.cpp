#include "weapon.h"
#include "snake.h"
#include <map>

map<object,int> Map_WeaponMoveDistance{
    {WEAPON_Fire,5},
    {WEAPON_Bramble,3}
};

map<object,double> Map_WeaponTime{
    {WEAPON_Fire,10},
    {WEAPON_Bramble,20}
};

void error()
{

}

void Weapon::move(Field& f)
{
    /*子弹更新规则
    1. 按照给定的向前平移
    2. 若遇到障碍物，判定武器的属性，是否穿过，消失，或者障碍物是否消失
    3. 若遇到墙体，直接消失
    4. 若遇到蛇体，判定子弹属性，是否造成伤害，或者debuff效果
    */


    //判定是否移动
    //速度为零，或者移动距离达到上限，禁止移动
    if(speed == 0 || dis++ < Map_WeaponMoveDistance.find(weaponType)->second) return ;
    //向“前”移动一格
    position nhead = nhead + Direction[dir];
    if(f[nhead] == WALL){
        switch(weaponType){
            case WEAPON_Fire    : f.deleteWeapon(weapon);break;//火焰子弹被边界墙清除
            case WEAPON_Bramble : speed = 0;break;
            default             : error();break;
        }
    }
    else if(f[nhead] == OBSTACLE_Bramble){
        switch(weaponType){
            case WEAPON_Fire    : f.setObject(nhead,NONE);f.deleteWeapon(weapon);break;//火焰子弹被边界墙清除
            case WEAPON_Bramble : speed *= Weapon_brambleDecelerateRate;weapon = nhead;break;
            default             : error();break;
        }
    }
    else if(f[nhead] == OBSTACLE_Normal){
        switch(weaponType){
            case WEAPON_Fire    : f.setObject(nhead,NONE);f.deleteWeapon(weapon);break;//火焰子弹被边界墙清除
            case WEAPON_Bramble : speed = 0;break;
            default             : error();break;
        }
    }
    else if(f[nhead] > FOOD_Start && f[nhead] < FOOD_End){
        //食物
        switch(weaponType){
            case WEAPON_Fire    : f.deleteFood(nhead);f.deleteWeapon(weapon);break;//火焰子弹被边界墙清除
            case WEAPON_Bramble : speed *= Weapon_brambleDecelerateRate;weapon = nhead;break;
            default             : error();break;
        }
    }
    else if(f[nhead] == SNAKEHEAD || f[nhead] == SNAKE){
        switch(weaponType){
            case WEAPON_Fire    : {
                int pos = f.getSnake(nhead);//实体蛇
                vector<Snake>& ss = f.getSnake();
                if(pos == -1){weapon = nhead;break;}
                else if(ss[pos].isInvincible()){
                    //无敌
                    f.deleteWeapon(weapon);break;
                }
                else{
                    //击中该蛇头
                    ss[pos].hurtAtPoint(f,nhead);break;
                }
            }
            case WEAPON_Bramble : {
                int pos = f.getSnake(nhead);//实体蛇
                vector<Snake>& ss = f.getSnake();
                if(pos == -1){weapon = nhead;break;}
                else if(ss[pos].isInvincible()){
                    //无敌
                    f.deleteWeapon(weapon);break;
                }
                else{
                    f.deleteWeapon(weapon);
                    if(f[nhead] == SNAKEHEAD) ss[pos].dealStill();
                    else if(f[nhead] == SNAKE) ss[pos].dealDecelerate();
                    break;
                }
            }
            default             : error();break;
        }
    }
    else if(f[nhead] == WEAPON_Fire || weaponType == WEAPON_Fire){
        f.deleteWeapon(nhead);
        f.deleteWeapon(weapon);
    }
    else if(f[nhead] == WEAPON_Bramble){//两者均为荆棘，融合静止
        f.deleteFood(nhead);//注意删除顺序
        speed = 0;
        weapon = nhead;
    }
    else {
        error();
    }



}
