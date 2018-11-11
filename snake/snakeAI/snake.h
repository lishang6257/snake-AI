#pragma once
#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#define max_speed 1
#define min_speed 1
#define max_acceleration 1
#define max_gameTimeDistance 30
#define max_weaponSpeedRate 1.5

#define max_weaponFireThrowDistance 1
#define max_weaponBrameThrowDistance 3

#define hurt_rate_cutPoint 0.5//截断伤害
#define hurt_rate_noramlPoint 0.5//普通伤害
//#define hurt_rate_head 0.25//爆头伤害
#define hurt_rate_heart 0.25//七寸伤害

#define change_rate 0.5 //震荡概率


#include "position.h"
#include "field.h"
#include "food.h"
#include "weapon.h"
#include <map>

extern position Direction[4];


/*
这里很棘手的一个问题是蛇的速度的定义放在哪儿
用按压键的时长作为修改依据
方案一：在蛇结构体中，带来位置更新的问题（不是整格点数；一格一格更新）
方案二：在线程控制中，更改刷新间隔

在多次权衡中选择方案二
*/



class Snake{
public:
    Snake(const vector<position> &v);
    Snake();//useless
    ~Snake();

    inline void setDirection(direction d){
        lastDir = dir;dir = d;
        //更新速度
        updateSpeed();
    }
    inline int getID(){return id;}
    vector<position>& getSnake(){return asnake;}
    inline direction getDirection(){return dir;}
    inline double getAccelation(){return acceleration;}

    inline void updateSpeed(){
//        updateAcceleration();
//        speed += acceleration;
        speed = Max(min_speed,speed);
        speed = Min(speed,max_speed);
    }
    bool isAlive(){return whetherAlive;}
    bool Move(Field& f,double time);
    bool autoMove(Field& f,double time);

    bool hurtAtPoint(Field& f,position p,bool flag = true);
    bool hurtAtPoint(Field& f,int pos,bool flag = true);

    //处理Buff效果
    void dealOtherBuffStatus(snakeStatus ss);
    void dealDecelerate();
    void dealAccelerate();
    void dealInvincible();
    void dealInvisible();
    void dealStill();
    bool addWeapon(object w);

    bool canAccelerate();
    bool isInvisible();
    bool isHalfInvinsible();
    bool isInvincible();
    bool isStill();

    void switchWeapon();
    bool launchWeapon(Field& f);


private:
    int id;
    vector<position> asnake;
    vector<direction> historyDir;

    double gameTime;
    double speed;
    double acceleration;
    direction dir,lastDir;
    //add for food & weapon system
    vector<SStatus> SBuffStatus;//有时效
    vector<snakeStatus> SWeaponStatus;//无时效
    snakeStatus currentUsingWeapon;
    bool whetherAlive;
//    vector<Food> food;
//    Food curUsingFood;

    bool updateGameTime(double time);
    void updateSBuffStatus();
    //移动相关
    bool move(Field& f,bool flag = true);
    bool eatAndMove(Field& f);
    //处理关键词--伤害
    bool cutAtPoint(Field& f,int i,bool flag = true);
    bool cutAtPoint(Field& f,position p,bool flag = true);
    bool hurtAtNormalPoint(Field &f,int i,bool flag = true);
    bool hurtAtNormalPoint(Field &f,position p,bool flag = true);


    //private member function
//    inline void updateAcceleration(){
//        if(dir == DNone)
//            acceleration = 0;
//        else if(dir != lastDir)
//            acceleration = max(0,acceleration-1);
//        else
//            acceleration = min(max_acceleration,acceleration+1);
//    }
};

#endif // SNAKE_H_INCLUDED
