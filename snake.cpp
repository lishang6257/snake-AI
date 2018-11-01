#pragma once
#include "snake.h"

Snake::Snake(const vector<position> &v)
{
    speed = 1;
    acceleration = 0;
    dir = lastDir = DNone;
    asnake.assign(v.begin(), v.end());

}

Snake::Snake()
{
    speed = 1;
    acceleration = 0;
    dir = lastDir = DNone;
    asnake.insert(asnake.begin(),position(3,3));
    asnake.insert(asnake.begin(),position(4,3));
    asnake.insert(asnake.begin(),position(5,3));
}

Snake::~Snake()
{
    asnake.clear();
    foods.clear();
}

//这里还没有考虑速度对蛇身影响
bool Snake::move()
{
    position nhead = asnake[0] + Direction[dir]*speed;
    nhead.currect();
    if(nhead != asnake[0]){
        asnake.erase(asnake.begin() + asnake.size() - 1);
        asnake.insert(asnake.begin(),nhead);
        return true;
    }
    return false;
}

bool Snake::eatAndMove()
{
    position nhead = asnake[0] + Direction[dir]*speed;
    nhead.currect();
    if(nhead != asnake[0]){
        asnake.insert(asnake.begin(),nhead);
        return true;
    }
    return false;
}

bool Snake::move(Field& f)
{
    position nhead = asnake[0] + Direction[dir]*speed;
    nhead.currect();
    if(f[nhead] > FOOD_Start && f[nhead] < FOOD_End) return eatAndMove();
    else return move();
}

bool Snake::autoMove()
{
    for(int i = 0;i < 4;i ++){
        setDirection(direction(i));
        if(move()) return true;
    }
    return false;
}
