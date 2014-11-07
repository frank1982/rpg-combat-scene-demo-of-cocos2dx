
#ifndef __OneVsOne2__FSM__
#define __OneVsOne2__FSM__

#include "cocos2d.h"
using namespace cocos2d;




class FSM:public Node{
    
public:
    
    static FSM* create();
    void doEvent(std::string mEventName);
    void changeStatus(std::string mStatus);
    std::string getStatus();
    void addEvents(std::string eventName,std::string From,std::string To);
    std::unordered_map<std::string, std::function<void()>> _onEnters;
    
private:
    
    //eventName from status A to status B;
    std::unordered_map<std::string, std::unordered_map<std::string,std::string>> _events;
    //StatusName onEnter;
    
    //String of Status
    Array *_status=Array::create();
    std::string _oldStatus;
    std::string _curStatus=String::createWithFormat("idle")->getCString();
    
};
//status list idle\walk\attack\beHit\dead


#endif /* defined(__OneVsOne2__FSM__) */
