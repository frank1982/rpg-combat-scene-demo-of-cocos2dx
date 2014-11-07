

#include "Role.h"

using namespace cocos2d;


Role* Role::create(enum Relation mRelation){
    
    Role* role=new Role();
    role->_relation=mRelation;
    if(role&&role->init(mRelation)){
        
        return role;
    }
   
};
bool Role::init(enum Relation mRelation){
    
    
    if(mRelation==good){
        
        _body=Sprite::create("warrior.jpg");
        
        _body->setScale(_scaleOfBody);
        _showWidth=_scaleOfBody*(_body->getContentSize().width);
        _showHeight=_scaleOfBody*(_body->getContentSize().height);
        
        _blood=ProgressTimer::create(Sprite::create("bloodProgress.png"));
        _blood->setScale(_showWidth/_blood->getContentSize().width);
        _blood->setPosition(0,_showHeight/2+5);
        _blood->setMidpoint(Point(0,0.5));
        _blood->setType(ProgressTimer::Type::BAR);
        _blood->setPercentage(100);
        addChild(_body);
        addChild(_blood);
        
    }else{
        
        _body=Sprite::create("e_warrior.jpg");
        _body->setScale(_scaleOfBody);
        _showWidth=_scaleOfBody*_body->getContentSize().width;
        _showHeight=_scaleOfBody*_body->getContentSize().height;
        
        _blood=ProgressTimer::create(Sprite::create("bloodProgress.png"));
        _blood->setScale(_showWidth/_blood->getContentSize().width);
        _blood->setPosition(0,_showHeight/2+5);
        _blood->setMidpoint(Point(1,0.5));
        _blood->setType(ProgressTimer::Type::BAR);
        _blood->setPercentage(100);
        addChild(_body);
        addChild(_blood);
       
    }
   
   
    _fsm=FSM::create();
    initFSM();
    
    
    //_fsm->doEvent("doWalk");
    //_fsm->doEvent("doAttack");
    //_fsm->doEvent("doBeHit");
    //_fsm->doEvent("doAttack");
    //_fsm->doEvent("doDead");
        
    
    return true;
};
float Role::getShowWidth(){
    
    return _showWidth;
};
float Role::getShowHeight(){
    
    return _showHeight;
    
};
void Role::setTargetPoint(Point mPoint){
    
    _tagetPoint=mPoint;
};

void Role::initFSM(){
    
    auto onIdle=[&](){log("i am idle");};
    
    
    auto onWalk=[&](){
        
        log("i am walk");
        auto moveTo=MoveTo::create(8, _tagetPoint);
        this->runAction(moveTo);
        
    };
    
    
    auto onAttack=[&](){
        log("i am attack");
        
        if(_health>0){
            
            this->stopAllActions();
            
            if(_relation==good){
                this->schedule(schedule_selector(Role::attackFromPlayer),2);
            }
            else{
                this->schedule(schedule_selector(Role::attackFromMonster),3);}
            
        }else{
            //this->unscheduleAllSelectors();
            if(_fsm->getStatus()=="dead"){
                
                
            }else{
                
                _fsm->doEvent("doDead");

            }
                    }
       
       
     };
    
    
    auto onBeHit=[&](){
        log("i am beHit");
        //this->stopAllActions();
        if(_health>0){
            
                auto moveLeft=MoveBy::create(0.1, Point(-20,0));
                auto moveRight=MoveBy::create(0.1, Point(20,0));
                auto onBeHitCall=CallFunc::create([&](){
                _health=_health-400;
                _blood->setPercentage((_health/1000)*100);
                    
                    if(_health>0){
                        
                        this->_fsm->doEvent("doAttack");
                        
                    }else{
                        
                        log("signa, h1");
                        _fsm->doEvent("doDead");
                    }
                    
                
            });
            auto delay=DelayTime::create(2);
            
            if(_relation!=good){
                
                auto seq=Sequence::create(moveRight,moveLeft,onBeHitCall,NULL);
                
                this->runAction(seq);
                //this->_fsm->doEvent("doAttack");
                
            }else{
                
                auto seq=Sequence::create(moveLeft,moveRight,onBeHitCall,NULL);
                this->runAction(seq);
            }
            
        }
            
        else{
            log("%f",_health);
        
        }
};
    
    
    auto onDead=[&](){
        this->unscheduleAllSelectors();
        this->stopAllActions();
        log("i am dead");
        CCNotificationCenter::sharedNotificationCenter()->postNotification("someone is killed", NULL);
    };
    
    
    //intial _onEnters
    _fsm->_onEnters.insert(std::pair<std::string,std::function<void()>>(String::createWithFormat("idle")->getCString(), onIdle));
    _fsm->_onEnters.insert(std::pair<std::string,std::function<void()>>(String::createWithFormat("walk")->getCString(), onWalk));
    _fsm->_onEnters.insert(std::pair<std::string,std::function<void()>>(String::createWithFormat("attack")->getCString(), onAttack));
    _fsm->_onEnters.insert(std::pair<std::string,std::function<void()>>(String::createWithFormat("beHit")->getCString(), onBeHit));
    _fsm->_onEnters.insert(std::pair<std::string,std::function<void()>>(String::createWithFormat("dead")->getCString(), onDead));
    

};
void Role::attackFromPlayer(float dt){
    
    auto rotateLeft=RotateTo::create(0.1, -30);
    auto rotateRight=RotateTo::create(0.1, 30);
    auto rotateBack=RotateTo::create(0.1, 0);
    
    auto attackCall=CallFunc::create([&](){
        if(_relation==good){
            CCNotificationCenter::sharedNotificationCenter()->postNotification("player give a hit", NULL);
            
        }
    });
    
    if(_relation==good){

         auto seq=Sequence::create(rotateLeft,rotateRight,rotateBack,attackCall,NULL);
        this->runAction(seq);
        
        
    }
};
void Role::attackFromMonster(float dt){
    
    auto rotateLeft=RotateTo::create(0.1, -30);
    auto rotateRight=RotateTo::create(0.1, 30);
    auto rotateBack=RotateTo::create(0.1, 0);

    
    auto attackCall=CallFunc::create([&](){
        if(_relation==good){
                    }else{
            CCNotificationCenter::sharedNotificationCenter()->postNotification("monster give a hit", NULL);
            
            
        }
        
    });
    
    if(_relation==good){
        
       }else{
        
        auto seq=Sequence::create(rotateRight,rotateLeft,rotateBack,attackCall,NULL);
        this->runAction(seq);
        
    }
    
};
