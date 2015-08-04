#include "GameScene.h"
#include "Element.h"
#include "ScoreLabel.h"
#include "BestLabel.h"
#include "GameField.h"

USING_NS_CC;

Scene* GameMain::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameMain::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // create Score Lable
    auto scoreLabel = ScoreLabel::create();
    scoreLabel->setAnchorPoint(Vec2(0, 0));
    scoreLabel->setPosition(Vec2(origin.x, origin.y + visibleSize.height - 10));
    this->addChild(scoreLabel, 2);
    
    // create bestScore Label
    auto bestScoreLabel = BestLabel::create();
    bestScoreLabel->setAnchorPoint(Vec2(0, 0));
    bestScoreLabel->setPosition(Vec2(origin.x + visibleSize.width - 10, origin.y + visibleSize.height - 10));
    this->addChild(bestScoreLabel, 2);
    
    
    // restart menu
    auto restartItem = MenuItemImage::create("textures/gui/demo_background.png", "textures/gui/demo_background.png", CC_CALLBACK_1(GameMain::menuRestartCallback, this));
    
    // restart label
    auto restartLabel = Label::createWithTTF("restart","fonts/Marker Felt.ttf", 200);
    restartLabel->setAnchorPoint(Vec2(0.5, 0.5));
    restartLabel->setPosition(restartItem->getContentSize().width/2, restartItem->getContentSize().height/2 + 150);
    restartLabel->setTextColor(Color4B::YELLOW);
    restartLabel->setName("restart");
    restartItem->addChild(restartLabel);
    
    restartItem->setScale(0.3, 0.16);
    restartItem->setAnchorPoint(Vec2(1,1));
    restartItem->setPosition(bestScoreLabel->getPosition().x, bestScoreLabel->getPosition().y - 92);
    
    auto menu = Menu::create(restartItem, NULL);
    menu->setAnchorPoint(Vec2(0,0));
    menu->setPosition(Vec2(0,0));
    addChild(menu, 2);
    
    
    // game field
    gameField = GameField::create();
    gameField->setAnchorPoint(Vec2(0.5,0.5));
    gameField->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    addChild(gameField, 0);
    
    return true;
}


void GameMain::menuRestartCallback(Ref* pSender)
{
    CCLOG("menu restart clicked");
    gameField->init();
}

// TODO: add close menu
void GameMain::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


