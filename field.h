#pragma once
#ifndef FIELD_H_INCLUDED
#define FIELD_H_INCLUDED
//default
#include <vector>
#include "position.h"
#include "basic.h"

#include <cstdlib>

#define max_food_num 3

using namespace std;

extern position Direction[4];


class Snake;
class Food;

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

    bool createOneFood();
    void painter();
    void fresh();
private:
    object field[max_field_x][max_field_y];//这里面不包含樯的位置
    vector<Snake> snakes;
    vector<Food> foods;
};

#endif // FIELD_H_INCLUDED
