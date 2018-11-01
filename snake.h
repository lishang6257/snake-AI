#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED
#include "position.h"

#include "field.h"

using namespace std;

class Snake{
public:
    Snake(const vector<position> &v);
    Snake();//useless
    ~Snake();

    vector<position>& getSnake(){return asnake;}
    bool move(position direction);
    bool eatAndMove(position direction);
    bool move(Field& f,position direction);
    bool autoMove();
private:
    vector<position> asnake;
};

#endif // SNAKE_H_INCLUDED
