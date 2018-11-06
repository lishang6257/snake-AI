#include "food.h"
#include "field.h"

Food::Food()
{
    BuffTime = 5;
    survivalTime = 10;
    foodType = object(rand()%(FOOD_End-FOOD_Start - 1) + FOOD_Start + 1);
}

