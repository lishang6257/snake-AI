#include "snake.h"

Snake::Snake(const vector<position> &v)
{
    speed = 1;
    acceleration = 0;
    dir = lastDir = DNone;
    asnake = v;
}

Snake::Snake()
{
    speed = 1;
    acceleration = 0;
    dir = lastDir = DNone;
    asnake.insert(asnake.begin(),position(3,3));
    asnake.insert(asnake.begin(),position(4,3));
    asnake.insert(asnake.begin(),position(5,3));
    asnake.insert(asnake.begin(),position(6,3));
    asnake.insert(asnake.begin(),position(7,3));
    asnake.insert(asnake.begin(),position(8,3));
}

Snake::~Snake()
{
    asnake.clear();
    food.clear();
}

//这里还没有考虑速度对其他蛇身影响
bool Snake::move()
{
    position nhead = asnake[0] + Direction[dir];
    nhead.currect();
    for(int i = 0;i < asnake.size() - 1;i ++)
        if(asnake[i] == nhead) return false;
    if(nhead != asnake[0]){
        asnake.erase(asnake.begin() + asnake.size() - 1);
        asnake.insert(asnake.begin(),nhead);
        return true;
    }
    return false;
}

bool Snake::eatAndMove()
{
    position nhead = asnake[0] + Direction[dir];
    nhead.currect();
    if(nhead != asnake[0]){
        asnake.insert(asnake.begin(),nhead);
        cout << "eat.............\n";
        return true;
    }
    return false;
}

bool Snake::move(Field& f)
{
    /*蛇的移动规则
    1.按方向进行平移
    2.遇到食物，增长，获得食物加成
    3.遇到障碍物，判定蛇的加成
    4.遇到蛇体，判定位置关系，进行生成碰撞结果
    5.遇到墙体，死亡
    */
    position nhead = asnake[0] + Direction[dir]*speed;
    nhead.currect();
    //check snake collosion

//    Snake& snakes = f.getSnake();
//    for()
    if(f[nhead] == WALL || f[nhead] > OBSTACLE_Start && f[nhead] < OBSTACLE_End) return false;
    if(f[nhead] == WALL || f[nhead] > OBSTACLE_Start && f[nhead] < OBSTACLE_End) return false;
    if(f[nhead] > FOOD_Start && f[nhead] < FOOD_End) {
        vector<Food>& foods = f.getFood();
        for(int i = 0;i < foods.size();i ++){
            if(foods[i].getPosition() == nhead) {
//                cout << "delete food......\n";
                foods.erase(foods.begin() + i);break;
            }
        }
        return eatAndMove();
    }
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
