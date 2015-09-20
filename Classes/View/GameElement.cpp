//
//  GameElement.cpp
//  TransitionCocos2dX
//
//  Created by chrisfnxu on 7/22/15.
//
//

#include "GameElement.h"

GameElement::GameElement()
: _sideLen(0)
, _number(0)
, _isMerged(false)
, _isNew(true)
, _pos(-1, -1)
{
}

GameElement::~GameElement()
{
    
}


bool GameElement::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // valid anchor point
    ignoreAnchorPointForPosition(false);
    
    // get the side length
    _sideLen = (FieldWidth - (DIMENSION + 1)*ElemSpace)/DIMENSION;
    
    // create element
    _elem = Sprite::create();
    _elem->setColor(Color3B::GRAY);
    _elem->setTextureRect(Rect(0, 0, _sideLen, _sideLen));
    _elem->setAnchorPoint(Vec2(0, 0));
    
    // add number
    _numberLabel = Label::createWithTTF("","fonts/Marker Felt.ttf", 50);
    _numberLabel->setAnchorPoint(Vec2(0.5, 0.5));
    _numberLabel->setPosition(_elem->getContentSize().width/2, _elem->getContentSize().height/2);
    _numberLabel->setTextColor(Color4B::ORANGE);
    _numberLabel->setVisible(false);
    _elem->addChild(_numberLabel);
    
    setContentSize(Size(_sideLen, _sideLen));
    this->setColor(Color3B::WHITE);
    
    this->setAnchorPoint(Point(0.5, 0.5));
    this->setPosition(Point((_pos.x + 0.5)*_sideLen + ElemSpace * (_pos.x + 1), (3-_pos.y+0.5)*_sideLen + ElemSpace * (3 - _pos.y + 1)));
    addChild(_elem);
    
    return true;
}


void GameElement::mergeElement(GameElement *elem)
{
    if (_number != elem->_number) {
        CCLOGERROR("number is not equal, could not merge");
    }
    
    // merge elem set numer to number * 2
    setNumber(_number * 2);
    _isMerged = true;
}

bool GameElement::isEmpty()
{
    return _number == 0 ? true : false;
}

#pragma mark -
#pragma mark - setter && getter

void GameElement::setNumber(int number)
{
    // update number
    if (_number != number) {
        _number = number;
        
        if (_number == 0) {
            _elem->setColor(Color3B::GRAY);
            _numberLabel->setVisible(false);
            
        }else{
            _numberLabel->setVisible(true);
            _numberLabel->setString(std::to_string(_number));
            _elem->setColor(Color3B((_number+10)%128, ((_number+10)*2)%128, ((_number+10)*3)%128));
        }
    }
}

int GameElement::getNumber()
{
    return _number;
}

float GameElement::getSideLen()
{
    return _sideLen;
}

void GameElement::setPos(Vec2 pos)
{
    // update position
    if (_pos != pos) {
        _pos.set(pos);
        this->setPosition(Point((_pos.x+0.5)*_sideLen + ElemSpace * (_pos.x + 1), (3-_pos.y+0.5)*_sideLen + ElemSpace * (3 - _pos.y + 1)));
        
        // add animation
        if (_isNew && _number != 0) {
            auto action = Sequence::createWithTwoActions(ScaleTo::create(0, 0), ScaleTo::create(0.3f, 1));  //在0.3秒内从小缩放到大
            this->runAction(action);
            _isNew = false;
        }
    }
}

bool GameElement::getIsMerged()
{
    return _isMerged;
}

void GameElement::setIsMerged(bool isMerged)
{
    _isMerged = isMerged;
}


