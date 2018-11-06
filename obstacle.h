#ifndef OBSTACLE_H_INCLUDED
#define OBSTACLE_H_INCLUDED

class Obstacle{
public:
    Obstacle(){
        obstacleType = rand()%(OBSTACLE_End - OBSTACLE_Start - 1) + OBSTACLE_Start;
    }
    Obstacle(vector<position>& pos){
        obstacle = pos;
        obstacleType = rand()%(OBSTACLE_End - OBSTACLE_Start - 1) + OBSTACLE_Start;
    };

    inline void setObstacle(vector<position>& p){
        obstacle = p;
    }
    inline void setObstacleType(object ot){obstacleType = ot;}

    inline vector<position>& getObstacle(){return obstacle;}
    inline object getOstacleType(){return obstacleType;}

private:
    position obstacle;
    object obstacleType;

};

#endif // OBSTACLE_H_INCLUDED
