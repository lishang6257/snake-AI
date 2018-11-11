#pragma once
#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
//default
#include "basic.h"

#include <cstdlib>

#define max_food_num 3

using namespace std;

extern position Direction[4];


class Snake;
class Food;
class Obstacle;
class Weapon;

class Field{
public:
    Field();
    ~Field();

    inline object operator [](position& p){//const 问题
        if(!p.isValid()) return WALL;
        else return field[p.X()][p.Y()];
    }
    inline vector<Snake>& getSnake(){
        return snakes;
    }
    int getSnake(position shead,bool flag = true);
    bool deleteSnake(int id);


    inline vector<Food>& getFood(){
        return foods;
    }
    void addFood(position p,object ft = FOOD_Start);
    bool createOneFood();
    bool createNFoodAtPosition(position p,int n);
    bool deleteFood(position p);


    inline vector<Obstacle>& getObstacle(){
        return obstacles;
    }
    void addObstacle(position p,object ot = OBSTACLE_Start);
    bool deleteObstacle(position p);


    inline void setObject(position &p,object o){
        field[p.X()][p.Y()] = o;
    }
    void clearObject(vector<position>&p);

    void addWeapon(Weapon w);
    bool deleteWeapon(position p);

    void painter();
    void fresh();
private:
    object field[max_field_x][max_field_y];//这里面不包含樯的位置
    vector<Snake> snakes;
    vector<Food> foods;
    vector<Obstacle> obstacles;//从小到大排好序的
    vector<Weapon> weapons;
};

#endif // FIELD_H_INCLUDED
