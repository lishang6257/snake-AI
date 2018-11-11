#include "snakegame.h"

#include<ctime>
#include<windows.h>
#include<conio.h>
#include<thread>

#include "snake.h"

position Direction[4] = {position(-1,0),position(1,0),position(0,-1),position(0,1)};

SnakeGame::SnakeGame(QWidget *parent)
    : QWidget(parent)
{
    //model Parameter

    //viewer Parameter

    //controller Parameter

    //other parameter
    GS = lastGS = GSNONE;
    time = pauseTime = 0;


    //here is for test different gamemode
    game_init_ui();
}

SnakeGame::~SnakeGame()
{

}

void SnakeGame::game_init_ui()
{
    //窗体属性
    this->setFixedSize(400,800);
    this->setVisible(true);
    //菜单
}

void SnakeGame::timer()
{
    switch(GS){
        case GSStart   : startTime = clock();break;
        case GSPause   : if(lastGS == GSPlayOn) tmpTime = clock(); pauseTime += difftime(clock(),tmpTime);break;
        case GSPlayOn  : time = time + difftime(clock(),startTime) - pauseTime;break;
        default        : break;
    }
}

void SnakeGame::viewer()
{
    //fresh
//    cls();
//    field.fresh();
//    field.painter();
}

void SnakeGame::controller()
{
    if(field.getSnake().size() <= 0) return;
    if (_kbhit()) {
        char KBIn = _getch();
        if(GS == GSPlayOn){
            lock_guard<mutex> lockGuard(fieldFlag);
            switch (KBIn) {
                case 'w':case 'W': field.getSnake()[0].setDirection(Up);break;
                case 's':case 'S': field.getSnake()[0].setDirection(Down);break;
                case 'a':case 'A': field.getSnake()[0].setDirection(Left);break;
                case 'd':case 'D': field.getSnake()[0].setDirection(Right);break;
                case 'f':case 'F': {
                    field.getSnake()[0].launchWeapon(field);
//                    field.getSnake()[0].hurtAtPoint(field,3);
//                    cout << "snakw length :" << field.getSnake()[0].getSnake().size() << endl;
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
//        cout << "snake num : " << field.getSnake().size() << endl;
        if(field.getSnake().size() <= 0) return;
        if(!field.getSnake()[0].Move(field,0)) cout << "game over";
        else cout << "continue .....";
    }
//    if(!field.getSnake()[0].move(field)) cout << "game over";
//    else cout << "continue .....";
//    timer();
}

void SnakeGame::controller2()
{
    if(field.getSnake().size() <= 1) return;
    if (_kbhit()) {
        char KBIn = _getch();
        if(GS == GSPlayOn){
            lock_guard<mutex> lockGuard(fieldFlag);
            switch (KBIn) {
                case 'i':case 'I': field.getSnake()[1].setDirection(Up);break;
                case 'k':case 'K': field.getSnake()[1].setDirection(Down);break;
                case 'j':case 'J': field.getSnake()[1].setDirection(Left);break;
                case 'l':case 'L': field.getSnake()[1].setDirection(Right);break;
                case 'u':case 'U': {
                    field.getSnake()[1].launchWeapon(field);
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
        if(!field.getSnake()[1].isAlive()) field.deleteSnake(field.getSnake()[0].getID());
//        cout << "snake num : " << field.getSnake().size() << endl;
        if(field.getSnake().size() <= 1) return;
        if(!field.getSnake()[1].Move(field,0)) cout << "game over";
        else cout << "continue .....";
    }
//    if(!field.getSnake()[0].move(field)) cout << "game over";
//    else cout << "continue .....";
//    timer();
}

void SnakeGame::playOn()
{
//    thread t1(&SnakeGame::controller, this);
//    thread t2(&SnakeGame::controller2, this);
    setGameStatus(GSPlayOn);

//    while(1){
//        viewer();

//        controller();

////        t1.join();
////        t2.join();
//    }
}

