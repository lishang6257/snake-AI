#ifndef SNAKEGAME_H
#define SNAKEGAME_H

class SnakeGmae{
public:
    SnakeGmae();


    void viewer();
    void controller();
    void controller2();


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

};

SnakeGmae::SnakeGmae()
{
    //model Parameter

    //viewer Parameter

    //controller Parameter

    //other parameter
    GS = lastGS = GSNONE;
    time = pauseTime = 0;
}

void SnakeGmae::timer()
{
    switch(GS){
        case GSStart   : startTime = clock();break;
        case GSPause   : if(lastGS == GSPlayOn) tmpTime = clock(); pauseTime += difftime(clock(),tmpTime);break;
        case GSPlayOn  : time = time + difftime(clock(),startTime) - pauseTime;break;
        default        : break;
    }
}

void SnakeGmae::viewer()
{
    //fresh
//    cls();
    field.fresh();
    field.painter();
}

void SnakeGmae::controller()
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

void SnakeGmae::controller2()
{
    if(field.getSnake().size() <= 1) return;
//    cout << "controller ''''''\n";
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

void SnakeGmae::playOn()
{
    thread t1(&game::controller, this);
    thread t2(&game::controller2, this);
    setGameStatus(GSPlayOn);

    while(1){
        viewer();

        t1.join();
//        t2.join();
    }
}

////int main()
////{
////    srand((unsigned int)time(NULL));
////    game g;
////    g.playOn();
////    return 0;
////}





#endif // SNAKEGAME_H
