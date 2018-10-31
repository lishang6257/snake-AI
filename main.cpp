#include <iostream>
#include <vector>
#include "position.h"
#include "snake.h"
using namespace std;

enum object{NONE,SNAKE,SNAKEHEAD,WALL};
string enumToStr(const object& o)
{
    switch(o){
        case SNAKE     : return "Snake";
        case SNAKEHEAD : return "SnakeHead";
        case WALL      : return "WALL";
        default        : return "NONE";
    }
}

class field{
public:
    field();
    inline object operator [](position& p){//const 问题
        if(!p.isValid()) return WALL;
        else return Field[p.X()][p.Y()];
    }
    inline vector<snake>& getSnake(){
        return Snake;
    }
private:
    object Field[max_field_x][max_field_y];//这里面不包含樯的位置
    vector<snake> Snake;
};

field::field()
{
    for(int i = 0;i < max_field_x;i ++){
        for(int j = 0;j < max_field_y;j ++){
            Field[i][j] = NONE;
        }
    }
}
//class game{
//public:
//    game();
//    void show();
//
//private:
//    //friend class feild;
////    vector<snake> Snakes;
//
//    //test a snake wander
//    snake s;
//};

//game::game()
//{
//    //initial wall
//    for(int i = 0;i < max_field_x;i ++) {field[i][0] = field[i][max_field_y-1] = WALL;}
//    for(int j = 0;j < max_field_y;j ++) {field[0][j] = field[max_field_x - 1][j] = WALL;}
//
//    //test
//    vector<position> v = {position(1,2),position(1,3)};
//    snake s(v);
//}

//void game::show()
//{
//     //fresh
//}

int main()
{
    vector<position> v = {position(1,2),position(1,3)};
    snake s(v);
    field f;
    position p = position(1,1);
    cout << enumToStr(f[p]);
    return 0;
}
