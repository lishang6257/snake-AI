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

class Field{
public:
    Field();
    inline object operator [](position& p){//const 问题
        if(!p.isValid()) return WALL;
        else return field[p.X()][p.Y()];
    }

    inline vector<Snake>& getSnake(){
        return Snake;
    }
private:
    object field[max_field_x][max_field_y];//这里面不包含樯的位置
    vector<Snake> Snake;
};

Field::Field()
{
    for(int i = 0;i < max_field_x;i ++){
        for(int j = 0;j < max_field_y;j ++){
            field[i][j] = NONE;
        }
    }
}

class game{
public:
    game();
    void viewer();
    void timer();
private:
    Field field;
    //test a snake wander
};

game::game()
{
    //test
    vector<position> v = {position(1,2),position(1,3)};
    Snake s(v);
}

//void login::help() {
//	cout << "贪吃蛇作战\n";
//	cout << "\n\noperator :\n";
//	cout << "w : up                 |  s : down\n";
//	cout << "a : left               |  d : right\n";
//	cout << "j : fire               |  p : pause\n";
//	cout << "\nimage :\n";
//	cout << "wall               : ■  | obstacle    : □\n";
//	cout << "snakeHead          : ⊙  | snakeBody   : ○\n";
//	cout << "fire               : ×  | food_normal : ★\n";
//	cout << "food_accelerator   : Ω  | food_attack : Σ\n";
//	cout << "food_invincibility : ◎  |\n";
//	cout << "\nauthor : Peter Guan\n";
//	cout << "email : 1991969298@qq.com\n";
//	cout << "\npress any Key to start!\n";
//	_getch();
//}

void game::viewer()
{
    //fresh
    //paint wall
    for(int i = 0;i < max_field_x;i ++){
        for(int j = 0;j < max_field_y;j ++){
            position p = position(i,j);
            switch(field[p]){
                case WALL       :  cout << "■";break;
                case SNAKEHEAD  :  cout << "⊙";break;
                case SNAKE      :  cout << "○";break;
                default         :  cout << "  ";break;
            }
        }
        cout << endl;
    }
}

int main()
{
    vector<position> v = {position(1,2),position(1,3)};
    Snake s(v);
    Field f;
    game g;
    g.viewer();
    position p = position(1,1);
    cout << enumToStr(f[p]);
    return 0;
}
