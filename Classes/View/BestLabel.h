//
//  BestLabel.h
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#ifndef __TransitionCocos2dX__BestLabel__
#define __TransitionCocos2dX__BestLabel__

#include "cocos2d.h"

USING_NS_CC;

class BestLabel : public Layer
{
public:
    BestLabel();
    virtual ~BestLabel(void);
    
    // overrides
    virtual bool init(void) override;
    
    CREATE_FUNC(BestLabel);
    
private:
    unsigned int bestScore;
};

#endif /* defined(__TransitionCocos2dX__BestLabel__) */
