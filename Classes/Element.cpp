//
//  Element.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/18.
//
//

#include "Element.h"

Element::Element()
{
    number = 0;
    pos_x = 0;
    pos_y = 0;
    isNew = false;
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
    
    return true;
}

void Element::setPosition(int x, int y)
{
    pos_x = x;
    pos_y = y;
}

