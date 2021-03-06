#include "GameMain.h"
#include "BestLabel.h"
#include "GameField.h"
#include "ScoreLabel.h"
#include "GameOver.h"

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
    scoreLabel = ScoreLabel::create();
    scoreLabel->setAnchorPoint(Vec2(0, 1));
    scoreLabel->setPosition(Point(origin.x, origin.y + visibleSize.height));
    this->addChild(scoreLabel, 2);
    
    // create bestScore Label
    auto bestScoreLabel = BestLabel::create();
    bestScoreLabel->setAnchorPoint(Vec2(0, 0));
    bestScoreLabel->setPosition(Vec2(origin.x + visibleSize.width - 10, origin.y + visibleSize.height - 10));
    this->addChild(bestScoreLabel, 2);
    
    
    // restart menu
    auto restartItem = MenuItemImage::create("textures/gui/demo_background.png",
                                             "textures/gui/demo_background.png",
                                             CC_CALLBACK_1(GameMain::menuRestartCallback, this));
    
    auto restartLabel = Label::createWithTTF("restart","fonts/Marker Felt.ttf", 200);
    restartLabel->setAnchorPoint(Vec2(0.5, 0.5));
    restartLabel->setPosition(restartItem->getContentSize().width/2, restartItem->getContentSize().height/2 + 150);
    restartLabel->setTextColor(Color4B::YELLOW);
    restartLabel->setName("restart");
    
    restartItem->addChild(restartLabel);
    restartItem->setScale(0.3, 0.10);
    restartItem->setAnchorPoint(Vec2(1,1));
    restartItem->setPosition(bestScoreLabel->getPosition().x, bestScoreLabel->getPosition().y - 70);
    
    auto menu = Menu::create(restartItem, NULL);
    menu->setAnchorPoint(Vec2(0,0));
    menu->setPosition(Vec2(0,0));
    this->addChild(menu, 2);
    
    
    // game field
    gameField = GameField::create();
    gameField->setAnchorPoint(Vec2(0.5,0.5));
    gameField->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(gameField, 0);
    
    
    // add event listener
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto cellMovedEventListener = EventListenerCustom::create("CellMoved", CC_CALLBACK_1(GameMain::cellMoved, this));
    dispatcher->addEventListenerWithSceneGraphPriority(cellMovedEventListener, this);
    
    return true;
}


void GameMain::menuRestartCallback(Ref* pSender)
{
    CCLOG("menu restart clicked");
    scoreLabel->updateScore(0);
    gameField->restartGame();
}


void GameMain::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameMain::cellMoved(EventCustom* event)
{
    char* buf = static_cast<char*>(event->getUserData());
    
    int score = atoi(buf);
    
    scoreLabel->updateScore(score);
    CCLOG("cell Moved， score: %d", score);
}



