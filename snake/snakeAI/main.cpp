#include "mainwindow.h"
#include <QApplication>
#include <snakegame.h>
#include <field.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SnakeGame game(NULL);
    game.playOn();
    //game.show();

//    Field f();
//    f.show();

    return a.exec();
}
