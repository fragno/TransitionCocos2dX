#include "GameScene.h"
#include "Element.h"
#include "ScoreLabel.h"

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
    
    // create Score lable
    auto scoreLabel = ScoreLabel::create();
    scoreLabel->setPosition(Vec2(origin.x + 24, origin.y + visibleSize.height - 50));
    this->addChild(scoreLabel);
    
    
    auto apple_golden = new Element("textures/items/apple_golden.png");
    auto apple = new Element("textures/items/apple.png");
    auto arrow = new Element("textures/items/arrow.png");
    auto barrier = new Element("textures/items/barrier.png");
    auto bed = new Element("textures/items/bed.png");
    
    // set attrs
    apple_golden->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    apple->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100));
    arrow->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 200));
    barrier->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 100));
    bed->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 200));

    // add elem as a child to this layer
    this->addChild(apple_golden, 0);
    this->addChild(apple, 0);
    this->addChild(arrow, 0);
    this->addChild(barrier, 0);
    this->addChild(bed, 0);
    
    return true;
}


void GameMain::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

