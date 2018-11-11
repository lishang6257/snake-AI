#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED
#include "basic.h"

class Obstacle{
public:
    Obstacle(){
        obstacleType = object(rand()%(OBSTACLE_End - OBSTACLE_Start - 1) + OBSTACLE_Start);
    }
    Obstacle(position pos){
        obstacle = pos;
        obstacleType = object(rand()%(OBSTACLE_End - OBSTACLE_Start - 1) + OBSTACLE_Start);
    };

    inline void setPosition(position p){
        obstacle = p;
    }
    inline void setType(object ot){obstacleType = ot;}

    inline position& getPosition(){return obstacle;}
    inline object getType(){return obstacleType;}

private:
    position obstacle;
    object obstacleType;

};

#endif // OBSTACLE_H_INCLUDED
