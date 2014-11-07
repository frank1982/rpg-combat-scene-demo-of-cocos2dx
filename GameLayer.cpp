#include "GameLayer.h"

USING_NS_CC;

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    this->schedule(schedule_selector(GameLayer::moveToFind));
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
                                                                  this,
                                                                  callfuncO_selector(GameLayer::func),  // 处理的消息的回调函数
                                                                  "player give a hit",                    // 感兴趣的消息名称
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
                                                                  this,
                                                                  callfuncO_selector(GameLayer::func2),  // 处理的消息的回调函数
                                                                  "monster give a hit",                    // 感兴趣的消息名称
                                                                  NULL);
    CCNotificationCenter::sharedNotificationCenter()->addObserver(
                                                                  this,
                                                                  callfuncO_selector(GameLayer::func3),  // 处理的消息的回调函数
                                                                  "someone is killed",                    // 感兴趣的消息名称
                                                                  NULL);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _player=Role::create(good);
    _player->setPosition(_player->getShowWidth()/2+20,visibleSize.height/2);
    _monster=Role::create(bad);
    _monster->setPosition(visibleSize.width-_monster->getShowWidth()/2-20,visibleSize.height/2);
    
    addChild(_player);
    addChild(_monster);
    
    _label=LabelTTF::create("start", "Arial", 36);
    _label->setColor(Color3B::RED);
    MenuItemLabel *item=MenuItemLabel::create(_label, CC_CALLBACK_0(GameLayer::start, this));
    Menu *menu=Menu::create();
    menu->addChild(item);
    menu->setPosition(visibleSize.width/2,60);
    addChild(menu);

    
    return true;
    
}

void GameLayer::start(){

   
    _player->_fsm->doEvent("doWalk");
    _monster->_fsm->doEvent("doWalk");

}
void GameLayer::moveToFind(float dt){
    
    //log("GameLayer::moveToFind");
    //_player->_fsm->doEvent("walk");
    if(!isMeet()){
        
        _player->_tagetPoint=_monster->getPosition();
        _monster->_tagetPoint=_player->getPosition();
        
    }else{
        this->unscheduleAllSelectors();
        
        _player->_fsm->doEvent("doAttack");
        _monster->_fsm->doEvent("doAttack");
        log("meet");
    }
};

bool GameLayer::isMeet(){
    
    auto Rect1=CCRectMake(_player->getPosition().x-_player->getShowWidth()/2, _player->getPosition().y-_player->getShowHeight()/2, _player->getShowWidth()+10, _player->getShowHeight());
    auto Rect2=CCRectMake(_monster->getPosition().x-_monster->getShowWidth()/2, _monster->getPosition().y-_monster->getShowHeight()/2, _monster->getShowWidth(), _monster->getShowHeight());
    
    return Rect1.intersectsRect(Rect2);
    
    
}

void GameLayer::func(CCObject* pSender){
    
    _monster->_fsm->doEvent("doBeHit");
}


void GameLayer::func2(CCObject* pSender){
    
    _player->_fsm->doEvent("doBeHit");
}

void GameLayer::func3(CCObject* pSender){
    
    if(_player->_fsm->getStatus()!="dead"){
        
        _player->_fsm->doEvent("doDead");
    }
    
    
}

