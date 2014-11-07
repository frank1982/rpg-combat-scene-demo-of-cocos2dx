

#ifndef __OneVsOne2__Role__
#define __OneVsOne2__Role__
#include "cocos2d.h"
#include "FSM.h"
using namespace cocos2d;


enum Relation{
    
    good,
    bad,
};


class Role:public Node{
    
public:
    
    static Role* create(enum Relation mRelation);
    bool init(enum Relation mRelation);
    float getShowWidth();
    float getShowHeight();
    void setTargetPoint(Point mPoint);
    void initFSM();
    Point _tagetPoint;
    FSM* _fsm;
    
private:
    
    enum Relation _relation;
    float _health=1000;
    float _damage;
    float _attackRate;
    float _showWidth;
    float _showHeight;
    float _scaleOfBody=0.15;
    float _scaleOfBlood;
    ProgressTimer *_blood;
    Sprite *_body;
    void attackFromPlayer(float dt);
    void attackFromMonster(float dt);
    
    
    
};


#endif /* defined(__OneVsOne2__Role__) */
