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

USING_NS_CC;

class GameElement : public cocos2d::Layer
{
public:
    GameElement();
    virtual ~GameElement(void);
    
    // overrides
    virtual bool init(void) override;
    
    // update
    void updateElementWithPosAndNumber(const int x, const int y, const int number);
    
    CREATE_FUNC(GameElement);
};

#endif /* defined(__TransitionCocos2dX__GameElement__) */
