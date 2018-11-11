#include "field.h"
#include "snake.h"
#include "food.h"

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
    snakes.push_back(Snake());

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

bool Field::createOneFood()
{
    int i,j,it=0;
    while(it ++ < 10){
        i = rand()%max_field_x;
        j = rand()%max_field_y;
        if(field[i][j] == NONE){
            Food f;
            f.setPosition(position(i,j));
            foods.push_back(f);
            return true;
        }
    }
    return false;
}


void Field::fresh()
{
    for(int i = 1;i < max_field_x - 1;i ++){
        for(int j = 1;j < max_field_y - 1;j ++){
            field[i][j] = NONE;
        }
    }
    //更新 snake
    for(auto s : snakes){
        for(auto sp : s.getSnake()) field[sp.X()][sp.Y()] = SNAKE;
        field[s.getSnake()[0].X()][s.getSnake()[0].Y()] = SNAKEHEAD;
    }
    //更新 食物
    while(foods.size() < max_food_num){
        createOneFood();
    }
    for(auto f : foods){
        field[f.getPosition().X()][f.getPosition().Y()] = f.getFoodType();
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
                case Food_Normal       :  cout << "◎";break;
                case FOOD_Accelerator  :  cout << "Ω";break;
                case FOOD_Weapon_Attack:  cout << "Σ";break;
                case FOOD_Invincible   :  cout << "★";break;
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
