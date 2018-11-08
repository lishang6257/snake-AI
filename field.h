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
    inline vector<Food>& getFood(){
        return foods;
    }
    bool addFood(position p,object ft);
    bool deleteFood(position);
//    bool addFoo

    inline vector<Obstacle>& getObstacle(){
        return obstacles;
    }
    bool addObstacle(position p,object ot);
    bool deleteObstacle(position p);
    inline void setObject(position &p,object o){
        field[p.X()][p.Y()] = o;
    }
    bool deleteSnake(int id);

//    void

    bool createOneFood();
    bool createNFoodAtPosition(position p,int n);
    void painter();
    void fresh();
private:
    object field[max_field_x][max_field_y];//这里面不包含樯的位置
    vector<Snake> snakes;
    vector<Food> foods;
    vector<Obstacle> obstacles;//从小到大排好序的
};

#endif // FIELD_H_INCLUDED
