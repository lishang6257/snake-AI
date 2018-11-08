#include "snake.h"

double normalDistribution(double u,double s,double x)
{
    return exp(-(x-u)*(x-u)/(2*s*s))/(s*sqrt(2*3.141));
}

map<snakeStatus,double> Map_SStatusTime{
    {SSAccelarate,20},
    {SSDecelerate,20},
    {SSInvincible,10},
    {SSInvisible,10},
    {SSHalfInvisible,5}
};

snakeStatus objectToSnakeStatus(object w)
{
    switch(w){
        case FOOD_Weapon_Attack : return SSWeapon_Fire;
        case Food_Weapon_Bramble: return SSWeapon_Bramble;
        case FOOD_Accelerate    : return SSAccelarate;
        case FOOD_Decelerate    : return SSDecelerate;
        case FOOD_Invincible    : return SSInvincible;
        case FOOD_Invisible     : return SSInvisible;
        case WEAPON_Fire        : return SSWeapon_Fire;
        case WEAPON_Bramble     : return SSWeapon_Bramble;
        default : return SSNormal;
    }
}

Snake::Snake(const vector<position> &v)
{
    whetherAlive = true;
    speed = 1;
    acceleration = 0;
    dir = lastDir = DNone;
    asnake = v;
}

Snake::Snake()
{
    whetherAlive = true;
    speed = 1;
    acceleration = 0;
    dir = lastDir = Down;
    asnake.insert(asnake.begin(),position(3,3));
    asnake.insert(asnake.begin(),position(4,3));
    asnake.insert(asnake.begin(),position(5,3));
    asnake.insert(asnake.begin(),position(6,3));
    asnake.insert(asnake.begin(),position(7,3));
    asnake.insert(asnake.begin(),position(8,3));
    asnake.insert(asnake.begin(),position(9,3));
    asnake.insert(asnake.begin(),position(10,3));
    asnake.insert(asnake.begin(),position(11,3));
    asnake.insert(asnake.begin(),position(12,3));
    asnake.insert(asnake.begin(),position(13,3));
}

Snake::~Snake()
{
    asnake.clear();
    historyDir.clear();
}

void Snake::updateSBuffStatus(double time)
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].second - time >= Map_SStatusTime.find(SBuffStatus[i].first)->second){
            if(SBuffStatus[i].first == SSInvisible) SBuffStatus.push_back(make_pair(SSHalfInvisible,Map_SStatusTime.find(SSHalfInvisible)->second));
            SBuffStatus.erase(SBuffStatus.begin() + i);break;
        }
    }
}

void Snake::dealOtherBuffStatus(snakeStatus ss)
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == ss){
            SBuffStatus[i].second += Map_SStatusTime.find(ss)->second;return ;
        }
    }
    SBuffStatus.push_back(make_pair(ss,Map_SStatusTime.find(ss)->second));
}

void Snake::dealAccelerate()
{
    int deceleratePos = -1;
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSAccelarate){
            SBuffStatus[i].second += Map_SStatusTime.find(SSAccelarate)->second;return ;
        }
        if(SBuffStatus[i].first == SSDecelerate) deceleratePos = i;
    }
    if(deceleratePos == -1){
        SBuffStatus.push_back(make_pair(SSAccelarate,Map_SStatusTime.find(SSAccelarate)->second));
    }
    else{
        SBuffStatus.erase(SBuffStatus.begin()+deceleratePos);
    }
}

void Snake::dealDecelerate()
{
    int acceleratePos = -1;
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSDecelerate){
            SBuffStatus[i].second += Map_SStatusTime.find(SSDecelerate)->second;return ;
        }
        if(SBuffStatus[i].first == SSAccelarate) acceleratePos = i;
    }
    if(acceleratePos == -1){
        SBuffStatus.push_back(make_pair(SSDecelerate,Map_SStatusTime.find(SSDecelerate)->second));
    }
    else{
        SBuffStatus.erase(SBuffStatus.begin()+acceleratePos);
    }
}

void Snake::dealInvicible()
{
    int deceleratePos = -1;
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSInvincible){
            SBuffStatus[i].second += Map_SStatusTime.find(SSInvincible)->second;return ;
        }
        if(SBuffStatus[i].first == SSInvincible) deceleratePos = i;
    }
    if(deceleratePos == -1){
        SBuffStatus.push_back(make_pair(SSDecelerate,Map_SStatusTime.find(SSDecelerate)->second));
    }
    else{
        SBuffStatus.erase(SBuffStatus.begin()+deceleratePos);
    }
}

//可以改进
bool Snake::addWeapon(object w)
{
    snakeStatus weapon;
    switch(w){
        case FOOD_Weapon_Attack : weapon = SSWeapon_Fire;break;
        case Food_Weapon_Bramble: weapon = SSWeapon_Bramble;break;
        default : return false;
    }
    for(int i = 0;i < SWeaponStatus.size();i ++){
        if(SWeaponStatus[i] == weapon){
            currentUsingWeapon = weapon;
            return true;
        }
    }
    SWeaponStatus.insert(SWeaponStatus.begin(),weapon);
    return true;
}

bool Snake::canAccelerate()
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSDecelerate) return false;
    }
    return true;
}

bool Snake::isInvisible()
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSInvisible) return true;
    }
    return false;
}

bool Snake::isHalfInvisible()
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSHalfInvisible) return true;
    }
    return false;
}

bool Snake::isInvincible()
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSInvincible) return true;
    }
    return false;
}

//这里还没有考虑速度对其他蛇身影响
bool Snake::move(Field& f)
{
    position nhead = asnake[0] + Direction[dir];
    nhead.currect();
    //检测是否与自己身体碰撞
    for(int i = 0;i < asnake.size() - 1;i ++){
        if(asnake[i] == nhead){
            return hurtAtPoint(f,0);
        }
    }
    //不碰撞
    asnake.erase(asnake.begin() + asnake.size() - 1);
    asnake.insert(asnake.begin(),nhead);
    return true;

}

bool Snake::eatAndMove(Field& f)
{
    position nhead = asnake[0] + Direction[dir];
    nhead.currect();
    if(nhead != asnake[0]){
        asnake.insert(asnake.begin(),nhead);
        vector<Food>& foods = f.getFood();
        for(int i = 0;i < foods.size();i ++){
            if(foods[i].getPosition() == nhead) {
                foods.erase(foods.begin() + i);break;
            }
        }
        return true;
    }
    return hurtAtPoint(f,0);
}

bool Snake::Move(Field& f,double time)
{
    //所有的食物增益均在此处处理
    /*蛇的移动规则
    1.按方向进行平移
    2.遇到食物，增长，获得食物加成
    3.遇到障碍物，判定蛇的加成
    4.遇到蛇体，判定位置关系，进行生成碰撞结果
    5.遇到墙体，死亡
    */
    updateSBuffStatus(time);

    position nhead = asnake[0] + Direction[dir]*speed;
    nhead.currect();

    switch(f[nhead]){
        //空白
        case NONE             : return move(f);
        //边界墙
        case WALL             : whetherAlive = false;return hurtAtPoint(f,0);
        //障碍物
        case OBSTACLE_Normal  : {
            if(isInvincible()){/*break and pass*/}
            if(isInvisible()){return move(f);/*pass*/}
            whetherAlive = false;return hurtAtPoint(f,0);
        }
        case OBSTACLE_Bramble : dealDecelerate(); return true;
        //食物
        case FOOD_Accelerate  : dealAccelerate();return eatAndMove(f);
        case FOOD_Decelerate  : dealDecelerate();return eatAndMove(f);
        case Food_Normal      : return eatAndMove(f);
        case FOOD_Invisible   : dealOtherBuffStatus(objectToSnakeStatus(FOOD_Invisible));return eatAndMove(f);
        case FOOD_Invincible  : dealInvicible();return eatAndMove(f);
        //武器
        case FOOD_Weapon_Attack  : return addWeapon(FOOD_Weapon_Attack) && eatAndMove(f);
        case Food_Weapon_Bramble : return addWeapon(Food_Weapon_Bramble) && eatAndMove(f);
        //其他蛇
        default :{
            vector<Snake>& ss = f.getSnake();
            for(int i = 0;i < ss.size();i ++){
                if(ss[i].isAlive() && (ss[i].isHalfInvisible() || ss[i].isInvisible())){
                    //活着或者无敌状态
                }
            }
        }
    }
}

bool Snake::autoMove(Field& f,double time)
{
    for(int i = 0;i < 4;i ++){
        setDirection(direction(i));
        if(Move(f,time)) return true;
    }
    return hurtAtPoint(f,0);
}

bool Snake::cutAtPoint(Field& f,position p)
{
    int pos;
    for(pos = 0;pos < asnake.size();pos ++){
        if(asnake[pos] == p) break;
    }
    return cutAtPoint(f,pos);
}

bool Snake::hurtAtNormalPoint(Field&f,position p)
{
    int pos;
    for(pos = 0;pos < asnake.size();pos ++){
        if(asnake[pos] == p) break;
    }
    hurtAtNormalPoint(f,pos);
}

bool Snake::hurtAtPoint(Field& f,position p)
{
    int pos;
    for(pos = 0;pos < asnake.size();pos ++){
        if(asnake[pos] == p) break;
    }
    return hurtAtPoint(f,pos);
}

//csdn 做标记，浮点数除法

bool Snake::cutAtPoint(Field& f,int pos)
{
    if(pos > asnake.size() - 1) return false;
    for(int i = pos;i < asnake.size();i ++){
        if((rand()%101)/100. < hurt_rate_cutPoint){
            //变成食物
            f.setObject(asnake[i],Food_Normal);
            Food food(asnake[i]);
            food.setFoodType(Food_Normal);
            f.getFood().push_back(food);
        }
        else f.setObject(asnake[i],NONE);
    }
    //自身截断,删除蛇体
    asnake.erase(asnake.begin() + pos,asnake.end());
//    cout << "cut position " << pos << endl;
    return true;
}

bool Snake::hurtAtNormalPoint(Field&f,int pos)
{
    cout << "normal hurt " << pos << "........"<< endl;
    if(pos > asnake.size() - 1) return false;
    int newFoodNum = (asnake.size() - pos)*(asnake.size() - pos)*1./asnake.size()*hurt_rate_noramlPoint;
    int FoodScale = newFoodNum/2;//生成的食物的溅射范围
    if(FoodScale == 0) FoodScale = 1;
    if(newFoodNum == 0) newFoodNum = 1;
    position Start = asnake[pos] - position(FoodScale,FoodScale);
    position End = asnake[pos] + position(FoodScale,FoodScale);
    Start.currect();End.currect();
    vector<position>nonePos;position tmp;
    for(int i = Start.X();i <= End.X();i ++){
        for(int j = Start.Y();j <= End.Y();j ++){
            tmp = position(i,j);
            if(f[tmp] == NONE){
                nonePos.push_back(tmp);
            }
        }
    }
    int declineLength = 0;
    while(newFoodNum -- > 0 || nonePos.empty()){
        int pi = rand()%nonePos.size();
        Food food(nonePos[pi]);
        food.setFoodType(Food_Normal);
        f.setObject(nonePos[pi],Food_Normal);
        f.getFood().push_back(food);
        nonePos.erase(nonePos.begin() + pi);
        declineLength ++;
    }

    //去除蛇身长度
    asnake.erase(asnake.end()-declineLength,asnake.end());
    return true;
}

bool Snake::hurtAtPoint(Field& f,int pos)
{
    if(pos < 0 || pos >= asnake.size()) return false;

    //爆头伤害 || 恰好其中七寸
    if(pos == 0 ){
//        f.deleteSnake(id);
        whetherAlive = false;
        //产生食物
        return cutAtPoint(f,0);
    }
    //普通七寸伤害
    if( asnake.size()*0.3 == pos ){
        if(asnake.size()%10 == 0){
            //恰好击中七寸
//            f.deleteSnake(id);
            whetherAlive = false;
            return cutAtPoint(f,0);
        }
        else{
            //击中七寸附近
            if((rand()%101)/100. < hurt_rate_heart) return cutAtPoint(f,pos);
            else return hurtAtNormalPoint(f,pos);
        }
    }

    //普通伤害
    return hurtAtNormalPoint(f,pos);
}

