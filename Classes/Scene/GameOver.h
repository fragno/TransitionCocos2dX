//
//  GameOver.h
//  TransitionCocos2dX
//
//  Created by fragno on 15/9/4.
//
//

#ifndef __TransitionCocos2dX__GameOver__
#define __TransitionCocos2dX__GameOver__

#include "cocos2d.h"

class GameOver : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameOver);
    
    void menuRestartCallback(Ref* pSender);
};

#endif /* defined(__TransitionCocos2dX__GameOver__) */
