#pragma once
#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#define max_speed 1
#define min_speed 1
#define max_acceleration 1

#include "position.h"
#include "field.h"
#include "food.h"

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

extern position Direction[4];

using namespace std;

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
    vector<position>& getSnake(){return asnake;}
    inline direction getDirection(){return dir;}
    inline double getAccelation(){return acceleration;}

    inline void updateSpeed(){
        updateAcceleration();
        speed += acceleration;
        speed = max(min_speed,speed);
        speed = min(speed,max_speed);
    }
    bool move();
    bool eatAndMove();
    bool move(Field& f);
    bool autoMove();
private:
    vector<position> asnake;
    vector<direction> historyDir;
    double speed;
    double acceleration;
    direction dir,lastDir;
    //add for food & weapon system
    vector<Food> f;
    Food curUsingFood;

    //private member function
    inline void updateAcceleration(){
        if(dir == DNone)
            acceleration = 0;
        else if(dir != lastDir)
            acceleration = max(0,acceleration-1);
        else
            acceleration = min(max_acceleration,acceleration+1);
    }
};

#endif // SNAKE_H_INCLUDED
