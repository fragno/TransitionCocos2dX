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

class ScoreLabel : public Layer
{
public:
    ScoreLabel();
    virtual ~ScoreLabel(void);
    
    // overrides
    virtual bool init(void) override;
    
    CREATE_FUNC(ScoreLabel);
    
    void updateScore(int score);
    
private:
    unsigned int score;
    Label* scoreLabel;
};

#endif /* defined(__TransitionCocos2dX__ScoreLabel__) */
