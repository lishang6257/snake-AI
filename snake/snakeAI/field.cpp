#include "field.h"
#include "snake.h"
#include "food.h"
#include "obstacle.h"
#include "weapon.h"

template <typename T>
int BSearch(vector<T>&p,position value)
{
    /*返回值说明：
    若存在相同的值,返回该值位置
    若不存在，返回附近的位置
    - vector中的元素天生互异,元素已按从小到大排序
    */
    int l = 0,h = p.size() - 1,mid = (l+h)/2;
    while(l < h){
        if(value < p[mid].getPosition()) { h = mid - 1; mid = (l+h)/2; }
        else if(value > p[mid].getPosition()){l = mid + 1;mid = (l+h)/2;}
        else return mid;
    }
    return mid;
}


Field::Field()
{
    for(int i = 1;i < max_field_x - 1;i ++){
        for(int j = 1;j < max_field_y - 1;j ++){
            field[i][j] = NONE;
        }
    }
    //add the wall
    for(int i = 0;i < max_field_x;i ++){
        field[i][0] = WALL;
        field[i][max_field_y - 1] = WALL;
    }
    for(int j = 1;j < max_field_y - 1;j ++){
        field[0][j] = WALL;
        field[max_field_x-1][j] = WALL;
    }

    //init snake
    vector<position> v1{position(3,2),position(4,2),position(5,2),position(6,2),position(7,2),position(8,2),position(9,2),position(10,2)};
    vector<position> v2{position(3,5),position(4,5),position(5,5),position(6,5),position(7,5),position(8,5),position(9,5),position(10,5)};
    snakes.push_back(Snake(v1));
    snakes.push_back(Snake(v2));

    //init food
    while(foods.size() < max_food_num){
        createOneFood();
    }
}

Field::~Field()
{
    snakes.clear();
    foods.clear();
}

int Field::getSnake(position head,bool flag)//flag 表示是否为实体蛇
{
    int i;
    for(i = 0;i < snakes.size();i ++){
        if(flag && snakes[i].isAlive() && !snakes[i].isInvisible()){//实体蛇
            if(snakes[i].getSnake()[0] == head) return i;
        }
        if(!flag && snakes[i].isAlive() &&  snakes[i].isInvisible()){//幽灵蛇
            if(snakes[i].getSnake()[0] == head) return i;
        }
    }
    return -1;
}

bool Field::createOneFood()
{
    int i,j,it=0;
    while(it ++ < 10){
        i = rand()%max_field_x;
        j = rand()%max_field_y;
        if(field[i][j] == NONE){
            addFood(position(i,j));
            return true;
        }
    }
    return false;
}

bool Field::createNFoodAtPosition(position p,int n)
{
    int scale = sqrt(n)/2 + 1;
    position Start = p - position(scale,scale);
    position End = p + position(scale,scale);
    Start.currect();End.currect();
    vector<position>nonePos;
    for(int i = Start.X();i <= End.X();i ++){
        for(int j = Start.Y();j <= End.Y();j ++){
            if(field[i][j] == NONE){
                nonePos.push_back(position(i,j));
            }
        }
    }
    int oLen = 0;
    while(n -- > 0 || nonePos.empty()){
        int pi = rand()%nonePos.size();
        addFood(nonePos[pi]);
        nonePos.erase(nonePos.begin() + pi);
        oLen ++;
    }
    return oLen;
}

//csdn 注明,空元素
void Field::addFood(position p,object ft)
{
    //二分查找并插入
    p.currect();
    Food f(p);
    if(ft != FOOD_Start) f.setType(ft);

    if(foods.empty()){
        foods.insert(foods.begin(),f); return;
    }
    int pos = BSearch<Food>(foods,p);
    if(p > foods[pos].getPosition()){
        foods.insert(foods.begin()+pos+1,f);
    }
    else if(p < foods[pos].getPosition()){
        //只有两种可能[首元素,非首元素]
        if(!pos)    foods.insert(foods.begin(),f);
        else foods.insert(foods.begin() + pos,f);
    }
    else{
        foods[pos] = f;
    }
    //修改field值
    field[p.X()][p.Y()] = ft;
}

bool Field::deleteFood(position p)
{
    int pos = BSearch<Food>(foods,p);
    if(p == foods[pos].getPosition()){
        field[p.X()][p.Y()] = NONE;
        foods.erase(foods.begin() + pos);return true;
    }
    return false;
}

void Field::addObstacle(position p,object ot)
{
    //本来要合并的食物和障碍物的，后来认为不合适，所以就分开了
    //二分查找并插入
    p.currect();
    Obstacle f(p);
    if(ot != OBSTACLE_Start) f.setType(ot);
    if(obstacles.empty()){
        field[p.X()][p.Y()] = NONE;
        obstacles.insert(obstacles.begin(),f); return;
    }
    int pos = BSearch<Obstacle>(obstacles,p);
    if(p > obstacles[pos].getPosition()){
        obstacles.insert(obstacles.begin()+pos+1,f);
    }
    else if(p < obstacles[pos].getPosition()){
        //只有两种可能[首元素,非首元素]
        if(!pos)    obstacles.insert(obstacles.begin(),f);
        else obstacles.insert(obstacles.begin() + pos,f);
    }
    else{
        obstacles[pos] = f;
    }
    field[p.X()][p.Y()] = ot;
}

bool Field::deleteObstacle(position p)
{
    int pos = BSearch<Obstacle>(obstacles,p);
    if(p == obstacles[pos].getPosition()){
        obstacles.erase(obstacles.begin() + pos);return true;
    }
    return false;
}

bool Field::deleteSnake(int id)
{
    //这里不更改field值[考虑中]:防止幽灵蛇与实体蛇在消失产生冲突，不修改
    //蛇已经死亡
    for(int i = 0;i < snakes.size();i ++){
        if(snakes[i].getID() == id && !snakes[i].isAlive()){
            snakes.erase(snakes.begin()+i);
            return true;
        }
    }
    return false;
}

//武器处理方式还没想好，暂且这样
void Field::addWeapon(Weapon w)
{
    weapons.push_back(w);
    setObject(w.getPosition(),w.getType());
}

bool Field::deleteWeapon(position p)
{
    bool f = false;
    for(int i = 0;i < weapons.size();i++){
        if(weapons[i].getPosition() == p) {
            f = true;
            weapons.erase(weapons.begin() + i);
        }
    }
    return f;
}

void Field::clearObject(vector<position>& p)
{
    for(int i = 0;i < p.size();i ++){
        field[p[i].X()][p[i].Y()] = NONE;
    }
}

void Field::fresh()
{
    for(int i = 1;i < max_field_x - 1;i ++){
        for(int j = 1;j < max_field_y - 1;j ++){
            field[i][j] = NONE;
        }
    }
    //更新 snake
    for(int i = 0;i < snakes.size();i++){
//        if(!snakes[i].isAlive()) snakes.erase(snakes.begin()+i);
        if(!snakes[i].isAlive() || snakes[i].isInvisible()) continue;
        for(auto sp : snakes[i].getSnake()) field[sp.X()][sp.Y()] = SNAKE;
        field[snakes[i].getSnake()[0].X()][snakes[i].getSnake()[0].Y()] = SNAKEHEAD;
    }
    //更新 食物
    while(foods.size() < max_food_num){
        createOneFood();
    }
    for(auto f : foods){
        field[f.getPosition().X()][f.getPosition().Y()] = f.getType();
    }

    //更新武器
//    for(int i = 0;i < weapons.size();i ++){
//        field[weapons[i].X()][weapons[i].Y()] = weapons[i].getType();
//    }
    for(auto w : weapons){
        field[w.getPosition().X()][w.getPosition().Y()] = w.getType();
    }
}


void Field::painter()
{
    //paint wall
    for(int i = 0;i < max_field_x;i ++){
        for(int j = 0;j < max_field_y;j ++){
            switch(field[i][j]){
                case WALL       :  cout << "■";break;
                case SNAKEHEAD  :  cout << "⊙";break;
                case SNAKE      :  cout << "○";break;
                case Food_Normal         :  cout << "◎";break;
                case FOOD_Accelerate     :  cout << "Ω";break;
                case FOOD_Decelerate     :  cout << "Ω";break;
                case FOOD_Invincible     :  cout << "★";break;
                case FOOD_Invisible      :  cout << "Ω";break;
                case FOOD_Weapon_Fire    :  cout << "fa";break;
                case Food_Weapon_Bramble :  cout << "fb";break;
                case WEAPON_Fire         :  cout << "wf";break;
                case WEAPON_Bramble      :  cout << "wb";break;


                default                :  cout << "  ";break;
            }
        }
        cout << endl;
    }
}

/*
for (int i = 0; i < Board_x + 2; i++) {
		for (int j = 0; j < Board_y + 2; j++) {
			if (board[i][j] == WALL) cout << "■";
			else if (board[i][j] == SNAKEHEAD) cout << "⊙";
			else if (board[i][j] == SNAKE) cout << "○";
			else if (board[i][j] == FOOD_NORMAL) cout << "★";
			else if (board[i][j] == FOOD_ACCELERATOR) cout << "Ω";
			else if (board[i][j] == FOOD_ATTACK) cout << "Σ";
			else if (board[i][j] == FOOD_INVINCIBILITY) cout << "◎";
			else if (board[i][j] == FIRE) cout << "×";
			else if (board[i][j] == OBSTACLE) cout << "□";
			else cout << "  ";
		}
		cout << "\n";
	}
	*/
