
#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED
#include <vector>
#include "position.h"
#include "basic.h"
#include <cstdlib>
using namespace std;

class Field;

class Food{
public:
    Food();
//    Food(Field& field);
    inline position& getPosition(){return p;}
    inline void setPosition(position pos){p = pos;}
    inline object getFoodType(){return foodType;}
    inline double getBuffTime(){return BuffTime;}
    inline double getSurvivalTime(){return survivalTime;}
private:
    position p;
    object foodType;
    double BuffTime,survivalTime;
};



#endif // FOOD_H_INCLUDED
