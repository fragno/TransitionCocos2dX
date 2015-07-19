//
//  Element.h
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/18.
//
//

#ifndef __TransitionCocos2dX__Element__
#define __TransitionCocos2dX__Element__

#include "cocos2d.h"

USING_NS_CC;

class Element : public cocos2d::Layer
{
public:
    Element(const std::string& elementname);
    virtual ~Element(void);
    
    // overrides
    virtual void onEnter() override;
    virtual void onExit() override;
    
    // override event
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
    virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;
  
    
private:
    std::string m_element_name;
};

#endif /* defined(__TransitionCocos2dX__Element__) */
