//
//  Element.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/18.
//
//

#include "Element.h"

Element::Element(const std::string& elementname)
{
    m_element_name = elementname;
}


Element::~Element()
{
    // TODO: release
}

void Element::onEnter()
{
    Layer::onEnter();
    
    this->setContentSize(Size(85, 90));
    
    auto element = Sprite::create(m_element_name);
    element->setAnchorPoint(Vec2(0.5, 0.5));
    element->runAction(RepeatForever::create(Sequence::create(RotateBy::create(1.0, 360), NULL)));
    addChild(element);
}

void Element::onExit()
{
    Layer::onExit();
    
}

#pragma mark -
#pragma mark - touch event

bool Element::onTouchBegan(Touch *touch, Event *unused_event)
{
    CCLOG("Element#onTouchBegan, touchPoint: x[%f], y[%f]", touch->getLocation().x, touch->getLocation().y);
    return true;
}

void Element::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("Element#onTouchMoved");
}

void Element::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("Element#onTouchEnded");
}

void Element::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("Element#onTouchCancelled");
}