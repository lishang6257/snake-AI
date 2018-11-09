#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "basic.h"

#include <cstdlib>
using namespace std;

class Field;

class Food{
public:
    Food();
    Food(position p);
//    Food(Field& field);

    inline void setPosition(position pos){p = pos;}
    inline void setType(object o){foodType = o;}

    inline position& getPosition(){return p;}
    inline object getType(){return foodType;}

    inline double getBuffTime(){return BuffTime;}
    inline double getSurvivalTime(){return survivalTime;}
    inline snakeStatus ToSnakeStaus(){
        return snakeStatus(foodType - FOOD_Start - 1);
    }
private:
    position p;
    object foodType;
    double BuffTime,survivalTime;
};



#endif // FOOD_H_INCLUDED
