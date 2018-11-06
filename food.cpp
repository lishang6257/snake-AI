#include "food.h"
#include "field.h"

Food::Food()
{
    p = position(0,0);
    foodType = FOOD_Start;
}

Food::Food(Field& f)
{
    BuffTime = 5;
    survivalTime = 10;
    foodType = object(rand()%(FOOD_End-FOOD_Start - 1) + FOOD_Start + 1);
    int i,j;
    while(1){
        i = rand()%max_field_x;
        j = rand()%max_field_y;
        position pos = position(i,j);
        if(f[pos] == NONE) break;
    }
    p = position(i,j);
}
