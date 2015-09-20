//
//  BestLabel.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#include "BestLabel.h"


BestLabel::BestLabel()
{
    bestScore = 0;
}

BestLabel::~BestLabel()
{
}

bool BestLabel::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // valid anchor point
    ignoreAnchorPointForPosition(false);
    
    // bestScoreBg
    auto bestScoreBg = Sprite::create("textures/gui/demo_background.png");
    bestScoreBg->setScale(0.3, 0.10);
    bestScoreBg->setAnchorPoint(Vec2(1,1));
    
    
    // bestScoreLabel
    auto bestScoreLabel = Label::createWithTTF("1024","fonts/Marker Felt.ttf", 200);
    bestScoreLabel->setAnchorPoint(Vec2(0.5, 0.5));
    bestScoreLabel->setPosition(bestScoreBg->getContentSize().width/2, bestScoreBg->getContentSize().height/2 + 150);
    bestScoreLabel->setTextColor(Color4B::RED);
    bestScoreLabel->setString(std::to_string(bestScore));
    bestScoreBg->addChild(bestScoreLabel);
    
    addChild(bestScoreBg);
    
    
    return true;
}
