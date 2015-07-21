//
//  GameField.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#include "GameField.h"

GameField::GameField()
{
    moveDireciton = MoveDirectionNone;
    isPressed = false;
    touchBeginPoint = Point(0, 0);
    for (int i=0; i<DIMENSION; i++) {
        for (int j=0; j<DIMENSION; j++) {
            elems[i][j] = NULL;
        }
    }
}


GameField::~GameField()
{
    
}

bool GameField::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // valid anchor point
    ignoreAnchorPointForPosition(false);
    
    Size winSize = Director::getInstance()->getWinSize();
    
    Sprite *gamefield = Sprite::create();
    gamefield->setColor(Color3B::WHITE);
    gamefield->setTextureRect(Rect(0, 0, winSize.width - 10, winSize.width - 10));
    gamefield->setAnchorPoint(Vec2(0,0));
    gamefield->setPosition(Vec2(0, 0));
    addChild(gamefield);
    
    setContentSize(gamefield->getContentSize());
    
    // create event listener
    auto dispatch = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameField::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameField::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameField::onTouchCancelled, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameField::onTouchEnded, this);
    listener->setSwallowTouches(true);
    dispatch->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


#pragma mark - 
#pragma mark - move action

void GameField::moveLeft()
{
    CCLOG("moveLeft called");
}

void GameField::moveRight()
{
    CCLOG("moveRight called");
}

void GameField::moveUp()
{
    CCLOG("moveUp called");
}

void GameField::moveDown()
{
    CCLOG("moveDown called");
}

bool GameField::addRandomElem()
{
    int randomX = RandomHelper::random_int(1, DIMENSION);
    int randomY = RandomHelper::random_int(1, DIMENSION);
    return true;
}

#pragma mark -
#pragma mark - touch event

bool GameField::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    // get gamefield rect
    Size size = getContentSize();
    Point pos = getPosition();
    Rect pRect = Rect(pos.x - size.width/2, pos.y - size.height/2, size.width, size.height);
    
    // get touch point
    Point location = touch->getLocationInView();
    location = Director::getInstance()->convertToGL(location);
    
    // is touch inside game field
    if (pRect.containsPoint(location)) {
        CCLOG("onTouchBegan inside gamefield");
        touchBeginPoint = location;
        isPressed = true;
        return true;
    }
    
    return false;
}


void GameField::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("onTouchMoved");
}

void GameField::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    CCLOG("onTouchCancelled");
}

void GameField::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    if (isPressed && touchBeginPoint != Point(0, 0)) {
        
        // decide move direction
        Point location = touch->getLocationInView();
        location = Director::getInstance()->convertToGL(location);
        int deltaX = location.x - touchBeginPoint.x;
        int deltaY = location.y - touchBeginPoint.y;
        if (abs(deltaX) >= abs(deltaY)) {
            moveDireciton = deltaX > 0 ?  MoveDirectionRight : MoveDirectionLeft;
            
        }else{
            moveDireciton = deltaY > 0 ? MoveDirectionUp : MoveDirectionDown;
        }
        CCLOG("onTouch move direction %d", moveDireciton);
        
        // do the move work
        switch (moveDireciton) {
            case MoveDirectionLeft:
                moveLeft();
                break;
                
            case MoveDirectionRight:
                moveRight();
                break;
                
            case MoveDirectionUp:
                moveUp();
                break;
                
            case MoveDirectionDown:
                moveDown();
                break;
                
            default:
                CCLOGWARN("invalid direction");
                break;
        }
        
        isPressed = false;
        touchBeginPoint = Point(0, 0);
        deltaY = 0;
        deltaX = 0;
    }
}

