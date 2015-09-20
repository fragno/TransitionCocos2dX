//
//  GameOver.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/9/4.
//
//

#include "GameOver.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameOver::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool GameOver::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    // gameOver
    auto gameOverLabel = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 100);
    gameOverLabel->setAnchorPoint(Vec2(0.5, 0.5));
    gameOverLabel->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height*2/3));
    gameOverLabel->setTextColor(Color4B::RED);
    this->addChild(gameOverLabel, 1);
    
    
    // restart
    auto restartItem = MenuItemImage::create("textures/gui/demo_background.png",
                                             "textures/gui/demo_background.png",
                                             CC_CALLBACK_1(GameOver::menuRestartCallback, this));
    auto restartLabel = Label::createWithTTF("restart","fonts/Marker Felt.ttf", 100);
    restartLabel->setAnchorPoint(Vec2(0.5, 0.5));
    restartLabel->setPosition(restartItem->getContentSize().width/2, restartItem->getContentSize().height/2 + 150);
    restartLabel->setTextColor(Color4B::YELLOW);
    restartItem->addChild(restartLabel);
    restartItem->setScale(0.3, 0.16);
    restartItem->setAnchorPoint(Vec2(0.5,0.5));
    restartItem->setPosition(origin.x + visibleSize.width/2, visibleSize.height/2);
    
    
    auto menu = Menu::create(restartItem, NULL);
    menu->setAnchorPoint(Vec2(0,0));
    menu->setPosition(Vec2(0,0));
    this->addChild(menu, 2);
    
    return true;
}

void GameOver::menuRestartCallback(Ref* pSender)
{
    CCLOG("menu restart clicked");
//    SceneTrans::startFlipInterface(GAME_START);
}
