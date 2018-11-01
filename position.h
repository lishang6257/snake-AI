#ifndef POSITION_H_INCLUDED
#define POSITION_H_INCLUDED
/*
以数组的左上角为原点,水平向右为y正方向,竖直向下为x正方向
*/
#include <iostream>
#define max_field_x 22//包含樯
#define max_field_y 22

class position{
public:
    position(){x=y=0;};
    position(int x,int y):x(x),y(y){}
    position(const position& p):x(p.x),y(p.y){};
    ~position(){};

    inline int X(){return x;}
    inline int Y(){return y;}
    inline void setX(int X){x = X;}
    inline void setY(int Y){y = Y;}

    inline position currect(){
        if(x<0) x = 0;
        if(x>=max_field_x) x = max_field_x-1;
        if(y<0) y = 0;
        if(y>=max_field_y) y = max_field_y-1;
        return position(x,y);
    }
    inline bool isValid(){
        if(x < 0 || x >= max_field_x || y < 0 || y >= max_field_y) return false;
        return true;
    }

    inline position operator + (const position& p) const {
        return position(x+p.x,y+p.y).currect();
    }
    inline position operator - (const position& p) const {
        return position(x-p.x,y-p.y).currect();
    }
    inline void operator +=(const position &p){
        x += p.x;y += p.y;
        currect();
    }
    inline void operator -=(const position &p){
        x -= p.x;y -= p.y;
        currect();
    }
    inline bool operator ==(const position &p){
        return x == p.x && y == p.y;
    }
    inline bool operator !=(const position &p){
        return !(x == p.x && y == p.y);
    }
    friend std::ostream & operator<<(std::ostream &out,const position& p){
        return (out << "(" << p.x << "," << p.y << ")");
    }

    inline position left(){y = --y > 0 ? y : 0;return position(x,y);};
    inline position right(){y = ++y < (max_field_y - 1) ? y : (max_field_y - 1);return position(x,y);}
    inline position up(){x = --x > 0 ? x : 0;return position(x,y);}
    inline position down(){x = ++x < (max_field_x - 1) ? x : (max_field_x - 1);return position(x,y);}

private:
    int x,y;
};

#endif // POSITION_H_INCLUDED
