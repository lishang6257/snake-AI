#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "basic.h"
#include "field.h"
#include<mutex>

class SnakeGame : QWidget {
public:
    SnakeGame(QWidget *parent);
    ~SnakeGame();

    void viewer();


    void controller();
    void controller2();


    void game_init_ui();


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
    double time,pauseTime;//游戏时间
    //other
    gameStatus GS,lastGS;
    mutex fieldFlag;

};


#endif // SNAKEGAME_H
