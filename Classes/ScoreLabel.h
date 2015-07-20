//
//  ScoreLabel.h
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#ifndef __TransitionCocos2dX__ScoreLabel__
#define __TransitionCocos2dX__ScoreLabel__

#include "cocos2d.h"

USING_NS_CC;

class ScoreLabel : public cocos2d::Layer
{
public:
    ScoreLabel();
    virtual ~ScoreLabel(void);
    
    // overrides
    virtual void onEnter() override;
    virtual void onExit() override;
    
    CREATE_FUNC(ScoreLabel);
    
private:
    unsigned int score;
};

#endif /* defined(__TransitionCocos2dX__ScoreLabel__) */
