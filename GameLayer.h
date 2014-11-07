#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Role.h"

class GameLayer : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    CREATE_FUNC(GameLayer);
    
    void start();
    void moveToFind(float dt);
    void func(CCObject* pSender);
    void func2(CCObject* pSender);
    void func3(CCObject* pSender);
    
private:
    
    LabelTTF *_label;
    Role *_player,*_monster;
    bool isMeet();
    
};

#endif // __HELLOWORLD_SCENE_H__
