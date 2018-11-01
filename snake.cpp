#include "snake.h"

Snake::Snake(const vector<position> &v)
{
    asnake.assign(v.begin(), v.end());
}

Snake::Snake()
{
    asnake.insert(asnake.begin(),position(3,3));
    asnake.insert(asnake.begin(),position(4,3));
}

Snake::~Snake()
{
    asnake.clear();
}

bool Snake::move(position dir)
{
    position nhead = asnake[0] + dir;
    nhead.currect();
    if(nhead != asnake[0]){
        asnake.erase(asnake.begin() + asnake.size() - 1);
        asnake.insert(asnake.begin(),nhead);
        return true;
    }
    return false;
}

bool Snake::eatAndMove(position dir)
{
    position nhead = asnake[0] + dir;
    nhead.currect();
    if(nhead != asnake[0]){
        asnake.insert(asnake.begin(),nhead);
        return true;
    }
    return false;
}

//bool Snake::move(Field& f,position direction)
//{
//    position nhead = asnake[0] + dir;
//    nhead.currect();
//    if(f[nhead] == FOOD) return eatAndMove(direction);
//    else return move(direction);
//}

bool Snake::autoMove()
{
    for(int i = 0;i < 4;i ++){
        if(move(Direction[i])) return true;
    }
    return false;
}
