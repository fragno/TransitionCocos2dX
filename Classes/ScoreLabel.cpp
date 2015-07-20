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

void ScoreLabel::onEnter()
{
    Layer::onEnter();
    
//    this->setContentSize(Size(Vec2(20, 20)));
    auto scoreLabel = Sprite::create("textures/gui/demo_background.png");
    scoreLabel->setScale(0.5);
    
    addChild(scoreLabel);
    
}


void ScoreLabel::onExit()
{
    Layer::onExit();
}

