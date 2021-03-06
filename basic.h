#pragma once
#ifndef BASIC_H_INCLUDED
#define BASIC_H_INCLUDED

#define Max(a,b) ((a) > (b) ? (a) : (b))
#define Min(a,b) ((a) < (b) ? (a) : (b))

#include <iostream>



using namespace std;

enum object{NONE,SNAKE,SNAKEHEAD,WALL,
        OBSTACLE_Start,OBSTACLE_Normal,OBSTACLE_End,
        FOOD_Start,Food_Normal,FOOD_Accelerator,FOOD_Weapon_Attack,FOOD_Invincible,FOOD_End,
        WEAPON_Start,WEAPON_Fire,WEAPON_End};
enum gameStatus{GSNONE,GSStart,GSPlayOn,GSPause,GSGameOver};
enum sankeStatus{SSNormal,SSInvincible,SSInvisible,SSWeapon_Attack};
enum direction{Up,Down,Left,Right,DNone};

#endif // BASIC_H_INCLUDED


/*
else if (board[i][j] == FOOD_NORMAL) cout << "★";
			else if (board[i][j] == FOOD_ACCELERATOR) cout << "Ω";
			else if (board[i][j] == FOOD_ATTACK) cout << "Σ";
			else if (board[i][j] == FOOD_INVINCIBILITY) cout << "◎";
			else if (board[i][j] == FIRE) cout << "×";
*/
