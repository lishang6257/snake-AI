#pragma once
#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED


#include "basic.h"
#include <cmath>

#define max_field_x 22//包含樯
#define max_field_y 22
/*
以数组的左上角为原点,水平向右为y正方向,竖直向下为x正方向
*/


class position{
public:
    position(){x=y=0;};
    position(int x,int y):x(x),y(y){}
//    position(const position& p):x(p.x),y(p.y){};
    ~position(){};

    inline int X(){return x;}
    inline int Y(){return y;}
    inline void setX(int X){x = X;}
    inline void setY(int Y){y = Y;}

    inline position currect(){
        x = Max(0,x);
        x = Min(x,max_field_x-1);
        y = Max(0,y);
        y = Min(y,max_field_y-1);
        return position(x,y);
    }
    inline bool isValid(){
        if(x < 0 || x >= max_field_x || y < 0 || y >= max_field_y) return false;
        return true;
    }
    inline int distance(position& p){
        return fabs(p.X() - x) + fabs(p.Y() - y);
    }
    inline position operator + (const position& p) const {
        return position(x+p.x,y+p.y);
    }
    inline position operator - (const position& p) const {
        return position(x-p.x,y-p.y);
    }
    inline void operator +=(const position &p){
        x += p.x;y += p.y;
    }
    inline void operator -=(const position &p){
        x -= p.x;y -= p.y;
    }
    inline position operator * (const double& p) const {
        return position(x*p,y*p);
    }
    inline position operator / (const double& p) const {
        return position(x/p,y/p);
    }
    inline bool operator ==(const position &p){
        return x == p.x && y == p.y;
    }
    inline bool operator !=(const position &p){
        return !(x == p.x && y == p.y);
    }
    inline bool operator <(const position& p) const{
        if(p.x > x) return true;
        if(p.x == x && p.y > y) return true;
        return false;
    }
    inline bool operator >(const position& p) const{
        if(p.x < x) return true;
        if(p.x == x && p.y < y) return true;
        return false;
    }
    friend std::ostream & operator<<(std::ostream &out,const position& p){
        return (out << "(" << p.x << "," << p.y << ")");
    }

    inline position left(){int Y = y;return position(x,Max(0,--Y));}
    inline position right(){int Y = y;return position(x,Min(max_field_y - 1,++Y));}
    inline position up(){int X = x;return position( Max(0,--X),y );}
    inline position down(){int X = x;return position( Min(max_field_x-1,++X),y );}

private:
    int x,y;
};

#endif // POSITION_H_INCLUDED
