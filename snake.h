#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "position.h"
using namespace std;

class Snake{
public:
    Snake(const vector<position> &v);
    bool move(position direction);
    bool eatAndMove(position direction);
    bool autoMove();
private:
    vector<position> asnake;
};

Snake::Snake(const vector<position> &v)
{
//    asnake.assign(v.begin(), v.end());
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

bool Snake::autoMove()
{
    for(int i = 0;i < 4;i ++){
        if(move(Direction[i])) return true;
    }
    return false;
}


#endif // SNAKE_H_INCLUDED
