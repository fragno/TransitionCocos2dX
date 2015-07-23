//
//  GameElement.h
//  TransitionCocos2dX
//
//  Created by chrisfnxu on 7/22/15.
//
//

#ifndef __TransitionCocos2dX__GameElement__
#define __TransitionCocos2dX__GameElement__

#include "cocos2d.h"
#include "Element.h"

USING_NS_CC;

class GameElement : public cocos2d::Layer
{
public:
    GameElement();
    virtual ~GameElement(void);
    
    // overrides
    virtual bool init(void) override;
    
    // update
    void updateElement(Element *elem);
    
    CREATE_FUNC(GameElement);
    
public:
    Sprite *gamefield;
    float sideLen;
};

#endif /* defined(__TransitionCocos2dX__GameElement__) */
