#pragma once
#ifndef BASIC_H_INCLUDED
#define BASIC_H_INCLUDED

#define Max(a,b) ((a) > (b) ? (a) : (b))
#define Min(a,b) ((a) < (b) ? (a) : (b))

//#define normalDistribution(u,s,x) (exp(-(x-u)*(x-u)/(2*u*u))/(u*sqrt(2*3.141)))


#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>

#include "position.h"

using namespace std;
/*
技能解释
*****Buff/Debuf果实******
Food_Normal(普通果实)只增加体长
FOOD_Accelerate(加速果实)增幅加速效果或抵消减速效果
FOOD_Decelerate(减速果实)无法获得加速效果或抵消加速效果
FOOD_Invincible(无敌果实)无视障碍物，任何减速效果，子弹效果，但并不会在蛇碰撞产生效果
FOOD_Invisible(透明果实)产生透明效果


*****武器果实**********
WEAPON_Fire(火焰果实)
一次发射可发射多颗连续火焰子弹，以下是对一颗子弹解释
破坏力：可破坏一个障碍物、食物或者荆棘子弹，可对蛇身造成伤害；产生上述效果后直接消失
位移效果：正常情况可持续移动
存在时间：在未产生破坏时，移动一定“距离”后自动消失；产生破坏后自动消失
--------------------------
WEAPON_Bramble（荆棘果实）
一次发射可发射多颗连续荆棘子弹，以下是对一颗子弹解释
破坏力：无伤害，蛇遇到后无法加速；蛇头遇到静止固定时间
位移效果：移动固定距离后会停滞在某处直至消亡；无法穿透普通障碍物移动
存在时间：停滞后开始计算，存在固定系统时间
---------------------------


解释：
1. 伤害
普通伤害：对蛇身造成伤害，按照伤害处在蛇身的位置计算损失长度，并将损失长度按照一定方式分布在受伤点附近
七寸伤害，当受伤点刚好在七寸位置，蛇体直接死亡；若在求整后的七寸位置，概率截断；
爆头伤害：当场去世

2. 距离
距离取曼哈顿距离，计算方法如下
空白格（NONE）算一个，蛇身，荆棘算两格[考虑是否实现中]

3.透明效果（幽灵态）
无视任何障碍物，不会对食物，蛇体做出任何反应
在透明->正常形态时
若身体上的障碍物小于体长1/10产生碾压效果；否则普通障碍物按一次火焰伤害计算，荆棘障碍物发动减速效果，
蛇身交错则在固定系统时间内(半幽灵态)，按其他蛇按该点火焰伤害（自己无视伤害），时间流逝后（正常态），自动计算伤害[不计算七寸伤害]
处于幽灵态的蛇受到伤害不产生食物

4.(de)buff果实有系统时效限制

5.武器果实无时限限制，可装备多个,并自动切换，但发射果实需要消耗体长

6.碰撞说明：
保护头部，头部受损直接死亡
特别的，在蛇头与蛇头碰撞中，蛇体长的一方无损，短的一方死亡,相同长度双方死亡

7.所有果实都有增加体长功能


*/

enum object{NONE,SNAKE,SNAKEHEAD,WALL,
        OBSTACLE_Start,OBSTACLE_Normal,OBSTACLE_Bramble,OBSTACLE_End,
        FOOD_Start,Food_Normal,FOOD_Accelerate,FOOD_Decelerate,FOOD_Invincible,FOOD_Invisible,FOOD_Weapon_Fire,Food_Weapon_Bramble,FOOD_End,
        WEAPON_Start,WEAPON_Fire,WEAPON_Bramble,WEAPON_End};
enum gameStatus{GSNONE,GSStart,GSPlayOn,GSPause,GSGameOver};
enum snakeStatus{SSNormal,SSAccelarate,SSDecelerate,SSInvincible,SSInvisible,SSWeapon_Fire,SSWeapon_Bramble,SSSTILL,SSHalfInvisible};//添加注意对齐食物顺序
enum direction{Up,Down,Left,Right,DNone};

typedef pair<snakeStatus,double> SStatus;//snakeStatus,指状态；double指状态开始时间



#endif // BASIC_H_INCLUDED


/*
else if (board[i][j] == FOOD_NORMAL) cout << "★";
			else if (board[i][j] == FOOD_ACCELERATOR) cout << "Ω";
			else if (board[i][j] == FOOD_ATTACK) cout << "Σ";
			else if (board[i][j] == FOOD_INVINCIBILITY) cout << "◎";
			else if (board[i][j] == FIRE) cout << "×";
*/
