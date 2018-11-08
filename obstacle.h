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

    inline void setObstacle(position p){
        obstacle = p;
    }
    inline void setObstacleType(object ot){obstacleType = ot;}

    inline position& getObstacle(){return obstacle;}
    inline object getOstacleType(){return obstacleType;}

private:
    position obstacle;
    object obstacleType;

};

#endif // OBSTACLE_H_INCLUDED
