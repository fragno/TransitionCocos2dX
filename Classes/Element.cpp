//
//  Element.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/18.
//
//

#include "Element.h"

Element::Element(const unsigned int number, Size size)
{
    m_number = number;
    m_size = size;
}


Element::~Element()
{
    // TODO: release
}


bool Element::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size winSize = Director::getInstance()->getWinSize();
    
    auto element = Sprite::create();
    element->setColor(Color3B::BLACK);
    element->setTextureRect(Rect(0, 0, m_size.width, m_size.height));
    element->setAnchorPoint(Vec2(0, 0));
    element->setPosition(Vec2(0, 0));
    addChild(element);
    
    setContentSize(m_size);
    
    return true;
}
