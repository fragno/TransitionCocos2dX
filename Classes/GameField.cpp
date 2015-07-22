//
//  GameField.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#include "GameField.h"
#include "GameElement.h"

GameField::GameField()
{
    moveDireciton = MoveDirectionNone;
    isPressed = false;
    isMoved = false;
    touchBeginPoint = Point(0, 0);
    
    emptyElemIndexes.clear();
    for (int i=0; i<DIMENSION; i++) {
        for (int j=0; j<DIMENSION; j++) {
            emptyElemIndexes.push_back(j*DIMENSION+i);
            elems[i][j] = new Element();
            elems[i][j]->setPosition(i, j);
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
    
    addRandomElem();
    
    return true;
}


#pragma mark - 
#pragma mark - move action

void GameField::moveLeft()
{
    CCLOG("moveLeft called");
    for (int i=1; i<DIMENSION; i++) {
        for (int j=0; j<DIMENSION; j++) {
            if (elems[i][j]->number > 0) {
                if (elems[i-1][j]->number == 0) {
                    elems[i-1][j]->number = elems[i][j]->number;
                    elems[i][j]->number = 0;
                    isMoved = true;
                    moveLeft();
                    
                }else if (elems[i-1][j]->number == elems[i][j]->number){
                    elems[i-1][j]->number = elems[i-1][j]->number + elems[i][j]->number;
                    elems[i][j]->number = 0;
                    isMoved = true;
                    moveLeft();
                }
            
            }
        }
    }
}

void GameField::moveRight()
{
    CCLOG("moveRight called");
    for (int i=DIMENSION-2; i>=0; i--) {
        for (int j=0; j<DIMENSION; j++) {
            if (elems[i][j]->number > 0) {
                if (elems[i+1][j]->number == 0) {
                    elems[i+1][j]->number = elems[i][j]->number;
                    elems[i][j]->number = 0;
                    isMoved = true;
                    moveRight();
                    
                }else if (elems[i+1][j]->number == elems[i][j]->number) {
                    elems[i+1][j]->number = elems[i+1][j]->number + elems[i][j]->number;
                    elems[i][j]->number = 0;
                    isMoved = true;
                    moveRight();
                }
            }
        }
    }
}

void GameField::moveUp()
{
    CCLOG("moveUp called");
    for (int j=1; j<DIMENSION; j++) {
        for (int i=0; i<DIMENSION; i++) {
            if (elems[i][j]->number > 0) {
                if (elems[i][j-1]->number == 0) {
                    elems[i][j-1]->number = elems[i][j]->number;
                    elems[i][j]->number = 0;
                    isMoved = true;
                    moveUp();
                
                }else if (elems[i][j-1]->number == elems[i][j]->number){
                    elems[i][j-1]->number = elems[i][j-1]->number + elems[i][j]->number;
                    elems[i][j]->number = 0;
                    isMoved = true;
                    moveUp();
                }
            }
        }
    }
}

void GameField::moveDown()
{
    CCLOG("moveDown called");
    for (int j=DIMENSION-2; j>=0; j--) {
        for (int i=0; i<DIMENSION; i++) {
            if (elems[i][j]->number > 0) {
                if (elems[i][j+1]->number == 0) {
                    elems[i][j+1]->number = elems[i][j]->number;
                    elems[i][j]->number = 0;
                    isMoved = true;
                    moveDown();
                    
                }else if (elems[i][j+1]->number == elems[i][j]->number){
                    elems[i][j+1]->number = elems[i][j+1]->number + elems[i][j]->number;
                    elems[i][j]->number = 0;
                    isMoved = true;
                    moveDown();
                }
            }
        }
    }
}

bool GameField::addRandomElem()
{
    emptyElemIndexes.clear();
    printf("empty indexes: ");
    for (int j=0; j<DIMENSION; j++) {
        for (int i=0; i<DIMENSION; i++) {
            if (elems[i][j]->number == 0) {
                emptyElemIndexes.push_back(j*DIMENSION + i);
                printf("%d ", j*DIMENSION + i);
            }
        }
    }
    printf("\n");
    
    int maxInt = (int)emptyElemIndexes.size();
    if (maxInt < 1) {
        CCLOG("no empty field for elem!");
        gameOver();
        return false;
    }
    
    int randomIndex = RandomHelper::random_int(0, maxInt-1);
    int number = randomIndex % 2 ? 2 : 4;
    randomIndex = emptyElemIndexes[randomIndex];
    CCLOG("randomIndex: %d", randomIndex);
    
    elems[randomIndex%DIMENSION][randomIndex/DIMENSION]->number = number;
    
    for (int j=0; j<DIMENSION; j++) {
        for (int i=0; i<DIMENSION; i++) {
            printf("%d ", elems[i][j]->number);
        }
        printf("\n");
    }
    
    refreshGameField();
    
    return true;
}


void GameField::refreshGameField()
{
    removeAllChildren();
    for (int i=0; i<DIMENSION; i++) {
        for (int j=0; j<DIMENSION; j++) {
                GameElement *gameElem = GameElement::create();
                gameElem->updateElementWithPosAndNumber(i, j, elems[i][j]->number);
                addChild(gameElem);
        }
    }
}

void GameField::gameOver()
{
    CCLOG("game over!");
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
        
        if (isMoved) {
            addRandomElem();
            isMoved = false;
        }
        
        isPressed = false;
        touchBeginPoint = Point(0, 0);
        deltaY = 0;
        deltaX = 0;
    }
}

