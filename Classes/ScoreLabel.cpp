//
//  ScoreLabel.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#include "ScoreLabel.h"

ScoreLabel::ScoreLabel()
{
    // init variable
    score = 0;
}

ScoreLabel::~ScoreLabel()
{
    
}

bool ScoreLabel::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // valid anchor point

    // scoreBg
    auto scoreBg = Sprite::create("textures/gui/demo_background.png");
    scoreBg->setScale(0.4, 0.3);
    scoreBg->setAnchorPoint(Vec2(0,1));
    
    // scoreLabel
    scoreLabel = Label::createWithTTF("1024","fonts/Marker Felt.ttf", 200);
    scoreLabel->setAnchorPoint(Vec2(0.5, 0.5));
    scoreLabel->setPosition(scoreBg->getContentSize().width/2, scoreBg->getContentSize().height/2 + 150);
    scoreLabel->setTextColor(Color4B::YELLOW);
    scoreLabel->setString(std::to_string(score));
    scoreBg->addChild(scoreLabel);
    
    addChild(scoreBg);
 
    return true;
}

void ScoreLabel::updateScore(int score)
{
    scoreLabel->setString(std::to_string(score));
}

