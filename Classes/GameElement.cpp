//
//  GameElement.cpp
//  TransitionCocos2dX
//
//  Created by chrisfnxu on 7/22/15.
//
//

#include "GameElement.h"

GameElement::GameElement()
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
    
    return true;
}


void GameElement::updateElementWithPosAndNumber(const int x, const int y, const int number)
{
    Size winSize = Director::getInstance()->getWinSize();
    float sideLen = (winSize.width - 10)/4;
    
    Sprite *gamefield = Sprite::create();
    switch (number) {
        case 0:
            gamefield->setColor(Color3B::WHITE);
            break;
        case 2:
            gamefield->setColor(Color3B::YELLOW);
            break;
        case 4:
            gamefield->setColor(Color3B::BLUE);
            break;
        case 8:
            gamefield->setColor(Color3B::GREEN);
            break;
        case 16:
            gamefield->setColor(Color3B::RED);
            break;
        case 32:
            gamefield->setColor(Color3B::MAGENTA);
            break;
        case 64:
            gamefield->setColor(Color3B::BLACK);
            break;
        case 128:
            gamefield->setColor(Color3B::ORANGE);
            break;
        case 256:
            gamefield->setColor(Color3B::GRAY);
            break;
        case 512:
            gamefield->setColor(Color3B::ORANGE);
            break;
        case 1024:
            gamefield->setColor(Color3B::ORANGE);
            break;
        case 2048:
            gamefield->setColor(Color3B::ORANGE);
            break;
        case 4096:
            gamefield->setColor(Color3B::ORANGE);
            break;
        case 8192:
            gamefield->setColor(Color3B::ORANGE);
            break;
            
        default:
            gamefield->setColor(Color3B::MAGENTA);
            break;
    }
    gamefield->setTextureRect(Rect(0, 0, sideLen, sideLen));
    gamefield->setAnchorPoint(Vec2(0.5,0.5));
    gamefield->setPosition(Vec2((x+1)*sideLen, (4-y)*sideLen));
    
    // add number
    auto numberLabel = Label::createWithTTF("","fonts/Marker Felt.ttf", 50);
    numberLabel->setAnchorPoint(Vec2(0.5, 0.5));
    numberLabel->setPosition(gamefield->getContentSize().width/2, gamefield->getContentSize().height/2);
    numberLabel->setTextColor(Color4B::BLACK);
    numberLabel->setString(std::to_string(number));
    gamefield->addChild(numberLabel);
    
    addChild(gamefield);
    setContentSize(gamefield->getContentSize());
}

