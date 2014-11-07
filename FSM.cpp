

#include "FSM.h"
using namespace cocos2d;

FSM* FSM::create(){
    
    FSM* fsm=new FSM();

    //initial _status
    fsm->_status->addObject(String::createWithFormat("idle"));
    fsm->_status->addObject(String::createWithFormat("walk"));
    fsm->_status->addObject(String::createWithFormat("attack"));
    fsm->_status->addObject(String::createWithFormat("beHit"));
    fsm->_status->addObject(String::createWithFormat("dead"));
    
    
   
    
    fsm->addEvents("doWalk","idle","walk");
    fsm->addEvents("doAttack","walk","attack");
    fsm->addEvents("doBeHit","attack","beHit");
    fsm->addEvents("doAttack","beHit","attack");
    fsm->addEvents("doAttack","attack","attack");
    fsm->addEvents("doDead","attack","dead");
    fsm->addEvents("doDead","beHit","dead");
    
    return fsm;
    
    
};

void FSM::doEvent(std::string mEventName){
    
    log("FSM::doEvent %s",mEventName.c_str());
    changeStatus(_events[mEventName][_curStatus]);
};
void FSM::changeStatus(std::string mStatus){
    
    _oldStatus=_curStatus;
    _curStatus=mStatus;

    _onEnters[_curStatus]();

};
std::string FSM::getStatus(){
    
    return _curStatus;
};

void FSM::addEvents(std::string eventName,std::string From,std::string To){
    
    
    std::unordered_map<std::string, std::string> &oneEvent = _events[eventName];
    oneEvent[From] = To;
    
    
}








