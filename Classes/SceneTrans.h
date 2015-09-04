//
//  SceneTrans.h
//  TransitionCocos2dX
//
//  Created by fragno on 15/9/4.
//
//

#ifndef __TransitionCocos2dX__SceneTrans__
#define __TransitionCocos2dX__SceneTrans__

#include "cocos2d.h"

USING_NS_CC;

enum{
    GAME_START,     // game start
    GAME_OVER,      // game over
};

class SceneTrans : public Layer
{
public:
    static void startFlipInterface(int iType);
};

#endif /* defined(__TransitionCocos2dX__SceneTrans__) */
