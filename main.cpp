#pragma once

#include <iostream>
#include <vector>
#include <ctime>

#include "basic.h"

#include "position.h"
#include "snake.h"
#include "field.h"

//add for controller
#include <conio.h>
//add for paint
#include <windows.h>
using namespace std;

extern position Direction[4] = {position(-1,0),position(1,0),position(0,-1),position(0,1)};

string enumToStr(const object& o)
{
    switch(o){
        case SNAKE     : return "Snake";
        case SNAKEHEAD : return "SnakeHead";
        case WALL      : return "WALL";
        default        : return "NONE";
    }
}
string enumToStr(const gameStatus& gs)
{
    switch(gs){
        case GSStart         : return "GSStart";
        case GSPlayOn       : return "GSPlayOn";
        case GSPause        : return "GSPause";
        case GSGameOver     : return "GSGameOver";
        default             : return "GSNONE";
    }
}

//解决刷新闪屏问题 ： refer :http://bbs.csdn.net/topics/391949781?page=1#post-402928936
bool cls() //编程方式实现清除屏幕
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0 , 0 };    /* here's where we'll home the cursor */
	COORD coordScreen1 = { max_field_x, 0 };    /* here's where we'll home the cursor */
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
	DWORD dwConSize;                 /* number of character cells in the current buffer */

	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info); //隐藏控制台光标

																		 /* get the number of character cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* get the current text attribute */
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return false;

	/* now set the buffer's attributes accordingly */
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen1, &cCharsWritten))
		return false;

	/* put the cursor at (0, 0) */
	if (!SetConsoleCursorPosition(hConsole, coordScreen))
		return false;
}

class game{
public:
    game();
    void viewer();
    void controller();
    inline void timer();

    inline void setGameStatus(gameStatus gs){lastGS = GS;GS = gs;}

    inline double getTime(){return time;}
    inline gameStatus getGameStatus(){return GS;}

    void playOn();
private:
    //model
    Field field;
    //timer
    time_t startTime,tmpTime;
    double time,pauseTime;//ms¼¶
    //other
    gameStatus GS,lastGS;


    //test a snake wander
};

game::game()
{
    //model Parameter

    //viewer Parameter

    //controller Parameter

    //other parameter
    GS = lastGS = GSNONE;
    time = pauseTime = 0;
}

void game::timer()
{
    switch(GS){
        case GSStart   : startTime = clock();break;
        case GSPause   : if(lastGS == GSPlayOn) tmpTime = clock(); pauseTime += difftime(clock(),tmpTime);break;
        case GSPlayOn  : time = time + difftime(clock(),startTime) - pauseTime;break;
        default        : break;
    }
}

void game::viewer()
{
    //fresh
    cls();
    field.fresh();
    field.painter();
}

void game::controller()
{
    if(field.getSnake().size() <= 0) return;
    if (_kbhit()) {
        char KBIn = _getch();
        if(GS == GSPlayOn){
            switch (KBIn) {
                case 'w':case 'W': field.getSnake()[0].setDirection(Up);break;
                case 's':case 'S': field.getSnake()[0].setDirection(Down);break;
                case 'a':case 'A': field.getSnake()[0].setDirection(Left);break;
                case 'd':case 'D': field.getSnake()[0].setDirection(Right);break;
                case 't':case 'T': {
                    field.getSnake()[0].hurtAtPoint(field,3);
                    cout << "snakw length :" << field.getSnake()[0].getSnake().size() << endl;
                    break;
                }
                case 'p':case 'P': setGameStatus(GSPause); break;
			    default: break;
            }
        }
        else if(GS == GSPause){
            switch (KBIn) {
                case 'p':case 'P': setGameStatus(GSPlayOn); break;
			    default: break;
            }
        }
        if(!field.getSnake()[0].isAlive()) field.deleteSnake(field.getSnake()[0].getID());
        cout << "snake num : " << field.getSnake().size() << endl;
        if(field.getSnake().size() <= 0) return;
        if(!field.getSnake()[0].Move(field,0)) cout << "game over";
        else cout << "continue .....";
    }
//    if(!field.getSnake()[0].move(field)) cout << "game over";
//    else cout << "continue .....";
//    timer();
}

void game::playOn()
{
    setGameStatus(GSPlayOn);
    while(1){
        viewer();

//        field.getSnake()[0].autoMove();
        controller();
    }
}

int main()
{
    cout << (position(0,0) < position(0,1)) << "dfa\n";
//    srand((unsigned int)time(NULL));
//    game g;
//    g.playOn();
    return 0;
}

//void login::help() {
//	cout << "Ì°³ÔÉß×÷Õ½\n";
//	cout << "\n\noperator :\n";
//	cout << "w : up                 |  s : down\n";
//	cout << "a : left               |  d : right\n";
//	cout << "j : fire               |  p : pause\n";
//	cout << "\nimage :\n";
//	cout << "wall               : ¡ö  | obstacle    : ¡õ\n";
//	cout << "snakeHead          : ¡Ñ  | snakeBody   : ¡ð\n";
//	cout << "fire               : ¡Á  | food_normal : ¡ï\n";
//	cout << "food_accelerator   : ¦¸  | food_attack : ¦²\n";
//	cout << "food_invincibility : ¡ò  |\n";
//	cout << "\nauthor : Peter Guan\n";
//	cout << "email : 1991969298@qq.com\n";
//	cout << "\npress any Key to start!\n";
//	_getch();
//}


