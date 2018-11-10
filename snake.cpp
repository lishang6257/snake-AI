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
    {SSHalfInvisible,5},
    {SSSTILL,5}
};

snakeStatus objectToSnakeStatus(object w)
{
    switch(w){
        case FOOD_Weapon_Fire   : return SSWeapon_Fire;
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
    gameTime = 0;
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
    gameTime = 0;
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
    SBuffStatus.clear();
    SWeaponStatus.clear();
}

bool Snake::updateGameTime(double time)
{
    if(time - gameTime > max_gameTimeDistance) return false;
    gameTime = time;
    return true;
}

void Snake::updateSBuffStatus()
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(gameTime - SBuffStatus[i].second >= Map_SStatusTime.find(SBuffStatus[i].first)->second){//状态时限到达
            //处理幽灵态
            if(SBuffStatus[i].first == SSInvisible) SBuffStatus.push_back(make_pair(SSHalfInvisible,gameTime));
            SBuffStatus.erase(SBuffStatus.begin() + i);break;
        }
    }
}

void Snake::dealOtherBuffStatus(snakeStatus ss)
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == ss){
            SBuffStatus[i].second -= Map_SStatusTime.find(ss)->second;return ;
        }
    }
    SBuffStatus.push_back(make_pair(ss,gameTime));
}

void Snake::dealAccelerate()
{
    //消除减速或者添加加速效果
    int deceleratePos = -1;
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSAccelarate){
            SBuffStatus[i].second -= Map_SStatusTime.find(SSAccelarate)->second;return ;
        }
        if(SBuffStatus[i].first == SSDecelerate) deceleratePos = i;
    }
    if(deceleratePos == -1){
        SBuffStatus.push_back(make_pair(SSAccelarate,gameTime));
    }
    else{
        SBuffStatus.erase(SBuffStatus.begin()+deceleratePos);
    }
}

void Snake::dealDecelerate()
{
    //无敌不受影响
    if(isInvincible()) return ;
    //消除加速或者添加减速效果
    int acceleratePos = -1;
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSDecelerate){
            SBuffStatus[i].second -= Map_SStatusTime.find(SSDecelerate)->second;return ;
        }
        if(SBuffStatus[i].first == SSAccelarate) acceleratePos = i;
    }
    if(acceleratePos == -1){
        SBuffStatus.push_back(make_pair(SSDecelerate,gameTime));
    }
    else{
        SBuffStatus.erase(SBuffStatus.begin()+acceleratePos);
    }
}

void Snake::dealInvincible()
{
    //消除减速并添加无敌效果
    int deceleratePos = -1;
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSInvincible){
            SBuffStatus[i].second -= Map_SStatusTime.find(SSInvincible)->second;return ;
        }
        if(SBuffStatus[i].first == SSInvincible) deceleratePos = i;
    }
    if(deceleratePos == -1){
        SBuffStatus.push_back(make_pair(SSDecelerate,gameTime));
    }
    else{
        SBuffStatus.erase(SBuffStatus.begin()+deceleratePos);
    }
}

void Snake::dealInvisible()
{
    //消除减速并清除半幽灵态
    int halfInvisiblePos = -1;
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSInvincible){
            SBuffStatus[i].second -= Map_SStatusTime.find(SSInvincible)->second;return ;
        }
        if(SBuffStatus[i].first == SSInvincible) halfInvisiblePos = i;
    }
    if(halfInvisiblePos != -1){
        SBuffStatus.erase(SBuffStatus.begin()+halfInvisiblePos);
    }
    SBuffStatus.push_back(make_pair(SSDecelerate,gameTime));
}

void Snake::dealStill()
{
    //无敌不受影响
    if(isInvincible()) return ;
    dealOtherBuffStatus(SSSTILL);
}
//可以改进
bool Snake::addWeapon(object w)
{
    snakeStatus weapon;
    switch(w){
        case FOOD_Weapon_Fire   : weapon = SSWeapon_Fire;break;
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
    currentUsingWeapon = weapon;
    return true;
}

bool Snake::isStill()
{
    for(int i = 0;i < SBuffStatus.size();i ++){
        if(SBuffStatus[i].first == SSSTILL) return true;
    }
    return false;
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

bool Snake::isHalfInvinsible()
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


//为了减少搜索范围，考虑增加ID_MAP
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

    //更新时间，掉线时间过长
    if(!updateGameTime(time)) return false;

    updateSBuffStatus();

    if(isStill()) return true;

    position nhead = asnake[0] + Direction[dir]*speed;
    nhead.currect();

    //检测幽灵态;无视其他实体蛇;障碍物;食物
    if(isInvisible()){
        if(f[nhead] == WALL){
            return hurtAtPoint(f,0,false);
        }
        //其他幽灵态玩家

        return move(f,false);
    }

    if(isHalfInvinsible()){
        //半幽灵态
        cout << "半幽灵态\n";
        return false;
    }

    //实体蛇
    switch(f[nhead]){
        //空白
        case NONE             : return move(f);
        //边界墙
        case WALL             : return hurtAtPoint(f,0);
        //障碍物
        case OBSTACLE_Normal  : {
            //无敌
            if(isInvincible()){f.deleteObstacle(nhead);return move(f);/*break and pass*/}
            //其他状态
            return hurtAtPoint(f,0);
        }
        case OBSTACLE_Bramble : {
            //其他状态
            dealDecelerate();
            return move(f);
        }
        //食物
        case FOOD_Accelerate  : dealAccelerate();return eatAndMove(f);
        case FOOD_Decelerate  : dealDecelerate();return eatAndMove(f);
        case Food_Normal      : return eatAndMove(f);
        case FOOD_Invisible   : dealInvisible();return eatAndMove(f);
        case FOOD_Invincible  : dealInvincible();f.clearObject(asnake);return eatAndMove(f);//清除蛇的坐标
        //武器果实
        case FOOD_Weapon_Fire    : return addWeapon(FOOD_Weapon_Fire) && eatAndMove(f);
        case Food_Weapon_Bramble : return addWeapon(Food_Weapon_Bramble) && eatAndMove(f);
        //其他蛇
        case SNAKEHEAD           : {
            //蛇头碰蛇头
            vector<Snake>& ss = f.getSnake();
            for(int i = 0;i < ss.size();i ++){
                //死蛇 || 幽灵蛇 || 自己 跳过
                if(!ss[i].isAlive() || ss[i].isInvisible() || ss[i].getID() == id) continue;
                //其他蛇
                if(ss[i].getSnake()[0] == nhead){
                    //比较长度，结算碰撞伤害
                    if(ss[i].getSnake().size() > asnake.size()) return hurtAtPoint(f,0);//长度不足，自己死亡
                    if(ss[i].getSnake().size() < asnake.size()) return move(f) & ss[i].hurtAtPoint(f,0);
                    return hurtAtPoint(f,0) & ss[i].hurtAtPoint(f,0);
                }
            }
        }
        case SNAKE                :{
            vector<Snake>& ss = f.getSnake();
            for(int i = 0;i < ss.size();i ++){
                //自掘坟墓
//                if(ss[i].getID() == id) continue;
                //死蛇 || 幽灵蛇 跳过
                if(ss[i].getID() == id || !ss[i].isAlive() || ss[i].isInvisible()) continue;
                //其他
                for(int j = 0;j < ss[i].getSnake().size();j ++){
                    if( ss[i].getSnake()[j] == nhead ){
                        return hurtAtPoint(f,0) & ss[i].hurtAtPoint(f,j);
                    }
                }

            }
            //自能是自己的身体了
            return move(f);
        }
        case WEAPON_Bramble   :{
            f.deleteWeapon(nhead);
            dealDecelerate();
            return move(f);
        }
        case WEAPON_Fire      :{
            f.deleteWeapon(nhead);
            return hurtAtPoint(f,0);
        }
        default : cout << "snake move error\n";
    }
    return false;
}

bool Snake::autoMove(Field& f,double time)
{
    for(int i = 0;i < 4;i ++){
        setDirection(direction(i));
        if(Move(f,time)) return true;
    }
    return hurtAtPoint(f,0);
}

bool Snake::hurtAtPoint(Field& f,int pos,bool flag)
{
    if(pos < 0 || pos >= asnake.size()) return false;

    //爆头伤害 || 恰好其中七寸
    if(pos == 0 ){
        whetherAlive = false;
        //产生食物
        return cutAtPoint(f,0,flag);
    }
    //普通七寸伤害
    if( asnake.size()*0.3 == pos ){
        if(asnake.size()%10 == 0){
            //恰好击中七寸
            whetherAlive = false;
            //产生食物
            return cutAtPoint(f,0,flag);
        }
        else{
            //击中七寸附近
            if((rand()%101)/100. < hurt_rate_heart) return cutAtPoint(f,pos,flag);
            else return hurtAtNormalPoint(f,pos,flag);
        }
    }

    //普通伤害
    return hurtAtNormalPoint(f,pos,flag);
}

void Snake::switchWeapon()
{
    int pos;
    for(pos = 0;pos < SWeaponStatus.size();pos ++){
        if(SWeaponStatus[pos] == currentUsingWeapon) break;
    }
    if(pos < SWeaponStatus.size() - 1) currentUsingWeapon = SWeaponStatus[pos+1];
    else if(pos == SWeaponStatus.size() - 1) currentUsingWeapon = SWeaponStatus[0];
    else currentUsingWeapon = SSNormal;
}

bool Snake::launchWeapon(Field& f)
{
    //weapon(position p,object wt,direction d,double speed,double time)
    //过短，无法发射
    if(asnake.size() < 8) return false;
    position weaponPos = asnake[0] + Direction[dir]*2;
    weaponPos.currect();
    switch(currentUsingWeapon){
        case SSWeapon_Fire    :{
            Weapon w(weaponPos,WEAPON_Fire,dir,max_weaponSpeedRate*speed,gameTime);
            f.addWeapon(w);
            return true;
        }
        case SSWeapon_Bramble :{
            Weapon w(weaponPos ,WEAPON_Bramble,dir,max_weaponSpeedRate*speed,gameTime);
            f.addWeapon(w);
            return true;
        }
        default : return false;
    }
}

//这里还没有考虑速度对其他蛇身影响
bool Snake::move(Field& f,bool flag)
{
    position nhead = asnake[0] + Direction[dir];
    nhead.currect();
    //检测是否与自己身体碰撞
    for(int i = 0;i < asnake.size() - 1;i ++){
        if(asnake[i] == nhead){
            return hurtAtPoint(f,0,flag);
        }
    }
    //不碰撞
    asnake.erase(asnake.begin() + asnake.size() - 1);
    asnake.insert(asnake.begin(),nhead);
    return true;

}

bool Snake::eatAndMove(Field& f)
{
    //这里一定有前方是食物，外层判定
    position nhead = asnake[0] + Direction[dir];
    nhead.currect();
    //修改蛇身
    asnake.insert(asnake.begin(),nhead);
    //删除食物
    return f.deleteFood(nhead);

}

bool Snake::cutAtPoint(Field& f,position p,bool flag)
{
    int pos;
    for(pos = 0;pos < asnake.size();pos ++){
        if(asnake[pos] == p) break;
    }
    return cutAtPoint(f,pos,flag);
}

bool Snake::hurtAtNormalPoint(Field&f,position p,bool flag)
{
    int pos;
    for(pos = 0;pos < asnake.size();pos ++){
        if(asnake[pos] == p) break;
    }
    return hurtAtNormalPoint(f,pos,flag);
}

bool Snake::hurtAtPoint(Field& f,position p,bool flag)
{
    int pos;
    for(pos = 0;pos < asnake.size();pos ++){
        if(asnake[pos] == p) break;
    }
    return hurtAtPoint(f,pos,flag);
}

//csdn 做标记，浮点数除法

bool Snake::cutAtPoint(Field& f,int pos,bool flag)
{
    if(pos > asnake.size() - 1) return false;
    for(int i = pos;i < asnake.size();i ++){
        if(flag && (rand()%101)/100. < hurt_rate_cutPoint){
            //变成食物
            f.addFood(asnake[i],Food_Normal);
        }
        else f.setObject(asnake[i],NONE);
    }

    //自身截断,删除蛇体
    asnake.erase(asnake.begin() + pos,asnake.end());
//    cout << "cut position " << pos << endl;
    return true;
}

bool Snake::hurtAtNormalPoint(Field&f,int pos,bool flag)
{
    cout << "normal hurt " << pos << "........"<< endl;
    if(pos > asnake.size() - 1) return false;
    int declineLength = 0;
    int newFoodNum = (asnake.size() - pos)*(asnake.size() - pos)*1./asnake.size()*hurt_rate_noramlPoint;
    if(flag){
        //生成食物
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
        while(newFoodNum -- > 0 && !nonePos.empty()){
            int pi = rand()%nonePos.size();
            f.addFood(nonePos[pi],Food_Normal);
            nonePos.erase(nonePos.begin() + pi);
            declineLength ++;
        }
    }
    else{
        //不产生食物
        declineLength = newFoodNum;
    }
    if(declineLength == 0) declineLength = 1;
    //去除蛇身长度
    asnake.erase(asnake.end()-declineLength,asnake.end());
    return true;
}

