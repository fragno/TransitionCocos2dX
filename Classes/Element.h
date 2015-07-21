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
    Element(const unsigned int number, const Size size);
    virtual ~Element(void);
    
    // overrides
    virtual bool init(void) override;
    
private:
    unsigned int m_number;
    Size m_size;
};

#endif /* defined(__TransitionCocos2dX__Element__) */
