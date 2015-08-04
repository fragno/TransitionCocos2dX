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
    Element();
    virtual ~Element(void);
    
    // overrides
    virtual bool init(void) override;
    
    // set position
    void setPosition(int x, int y);

public:
    int number;
    bool isNew;
    bool isMerged;
    int pos_x;
    int pos_y;
};

#endif /* defined(__TransitionCocos2dX__Element__) */
