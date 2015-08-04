//
//  GameField.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#include "GameField.h"
#include "GameElement.h"

#define MoveAnimationTime 0.2f

GameField::GameField()
{
    
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
    
    moveDireciton = MoveDirectionNone;
    isPressed = false;
    isMoved = false;
    isMerged = false;
    touchBeginPoint = Point(0, 0);
    
    emptyElemIndexes.clear();
    for (int col=0; col<DIMENSION; col++) {
        for (int row=0; row<DIMENSION; row++) {
            emptyElemIndexes.push_back(col*DIMENSION+row);
            elems[col][row] = new Element();
            elems[col][row]->setPosition(col, row);
            
//            GameElement *gameElem = new GameElement();
//            gameElem->init();
//            gameElemsAction[col][row] = gameElem;
            
//            addChild(gameElem,2);
            
//            auto hide = Hide::create();
//            gameElemsAction[col][row]->runAction(hide);
        }
    }
    
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
    
    addRandomElem(this);
    
    return true;
}


#pragma mark -
#pragma mark - move action

void GameField::moveLeft()
{
    CCLOG("moveLeft called");
    
    for (int col=1; col<DIMENSION; col++) {
        for (int row=0; row<DIMENSION; row++) {
            
            // only not empty cell need move
            if (elems[col][row]->number > 0) {
                
                int innerCol = col;
                for (; innerCol>0; innerCol--) {
                    
                    // left cell is empty
                    if (elems[innerCol-1][row]->number == 0) {
                        elems[innerCol-1][row]->number = elems[innerCol][row]->number;
                        elems[innerCol][row]->number = 0;
                        
                        isMoved = true;
                        
                        // left cell is same, merge cell
                    }else if (elems[innerCol-1][row]->number == elems[innerCol][row]->number){
                        if (isMerged) {
                            break;
                        }
                        
                        elems[innerCol-1][row]->number = elems[innerCol-1][row]->number + elems[innerCol][row]->number;
                        elems[innerCol][row]->number = 0;
                        
                        isMoved = true;
                        isMerged = true;
                        
                    // not same
                    }else{
                        break;
                    }
                    
                }// the cell is moved left, from [col][row] -> [innerCol][row]
             
                moveAnimation(row, col, row, innerCol);
                isMerged = false;
            }
        }
    }
}


void GameField::moveRight()
{
    CCLOG("moveRight called");
    
    for (int col=DIMENSION-2; col>=0; col--) {
        for (int row=0; row<DIMENSION; row++) {
            
            // only not empty cell needs move
            if (elems[col][row]->number > 0) {
                
                int innerCol = col;
                for (; innerCol<DIMENSION-1; innerCol++) {
                    
                    // right cell is empty
                    if (elems[innerCol+1][row]->number == 0) {
                        elems[innerCol+1][row]->number = elems[innerCol][row]->number;
                        elems[innerCol][row]->number = 0;
                        isMoved = true;
                        
                    // right cell is the same, merge cell
                    }else if (elems[innerCol+1][row]->number == elems[innerCol][row]->number) {
                        if (isMerged) {
                            break;
                        }
                        
                        elems[innerCol+1][row]->number = elems[innerCol+1][row]->number + elems[innerCol][row]->number;
                        elems[innerCol][row]->number = 0;
                        isMoved = true;
                        isMerged = true;
                        
                    // not same
                    }else{
                        break;
                    }
                    
                }// the cell is moved right, from [col][row]->[innerCol][row]
                
                moveAnimation(row, col, row, innerCol);
                isMerged = false;
            }
        }
    }
}

void GameField::moveUp()
{
    CCLOG("moveUp called");
    
    for (int row=1; row<DIMENSION; row++) {
        for (int col=0; col<DIMENSION; col++) {
            
            // only not empty cell needs move
            if (elems[col][row]->number > 0) {
                
                int innerRow = row;
                for (; innerRow>0; innerRow--) {
                    
                    // up cell is emtpy
                    if (elems[col][innerRow-1]->number == 0) {
                        elems[col][innerRow-1]->number = elems[col][innerRow]->number;
                        elems[col][innerRow]->number = 0;
                        isMoved = true;
                        
                    // up cell is the same, merge
                    }else if (elems[col][innerRow-1]->number == elems[col][innerRow]->number){
                        if (isMerged) {
                            break;
                        }
                        
                        elems[col][innerRow-1]->number = elems[col][innerRow-1]->number + elems[col][innerRow]->number;
                        elems[col][innerRow]->number = 0;
                        isMoved = true;
                        isMerged = true;
                        
                    // not same
                    }else{
                        break;
                    }
                } // the cell is moved up, from [col][row] -> [col][innerRow]
                
                moveAnimation(row, col, innerRow, col);
                isMerged = false;
            }
        }
    }
}

void GameField::moveDown()
{
    CCLOG("moveDown called");
    
    for (int row=DIMENSION-2; row>=0; row--) {
        for (int col=0; col<DIMENSION; col++) {
            
            // only not empty cell needs move
            if (elems[col][row]->number > 0) {
                
                int innerRow = row;
                for (; innerRow<DIMENSION-1; innerRow++) {
                    
                    // the down cell is empty
                    if (elems[col][innerRow+1]->number == 0) {
                        elems[col][innerRow+1]->number = elems[col][innerRow]->number;
                        elems[col][innerRow]->number = 0;
                        isMoved = true;
                        
                    // the down cell is same, merge
                    }else if (elems[col][innerRow+1]->number == elems[col][innerRow]->number){
                        if (isMerged) {
                            break;
                        }
                        
                        elems[col][innerRow+1]->number = elems[col][innerRow+1]->number + elems[col][innerRow]->number;
                        elems[col][innerRow]->number = 0;
                        isMoved = true;
                        isMerged = true;
                        
                    // not same
                    }else{
                        break;
                    }
                    
                } // the cell is moved down, from [col][row] -> [col][innerRow]
                
                moveAnimation(row, col, innerRow, col);
                isMerged = false;
            }
        }
    }
}

void GameField::addRandomElem(Node* node)
{
    emptyElemIndexes.clear();
    printf("empty indexes: ");
    for (int col=0; col<DIMENSION; col++) {
        for (int row=0; row<DIMENSION; row++) {
            if (elems[col][row]->number == 0) {
                emptyElemIndexes.push_back(col*DIMENSION + row);
                printf("%d ", col*DIMENSION + row);
            }
        }
    }
    printf("\n");
    
    int maxInt = (int)emptyElemIndexes.size();
    if (maxInt < 1) {
        CCLOG("no empty field for elem!");
        gameOver();
        return;
    }
    
    int randomIndex = RandomHelper::random_int(0, maxInt-1);
    int random2or4 = RandomHelper::random_int(1, 2);
    int number = (random2or4 == 1) ? 2 : 4;
    randomIndex = emptyElemIndexes[randomIndex];
    CCLOG("randomIndex: %d", randomIndex);
    
    int col = randomIndex/DIMENSION;
    int row = randomIndex%DIMENSION;
    elems[col][row]->number = number;
    elems[col][row]->isNew = true;
    
    GameElement *gameElem = GameElement::create();
    gameElem->updateElement(elems[col][row]);
    addChild(gameElem);
    
    
    // add to array
    gameElems[col][row] = gameElem;
    
    for (int row=0; row<DIMENSION; row++) {
        for (int col=0; col<DIMENSION; col++) {
            printf("%d ", elems[col][row]->number);
        }
        printf("\n");
    }
    
//    refreshGameField();
}

void GameField::moveAnimation(int fromRow, int fromCol, int toRow, int toCol)
{
    if (fromRow == toRow && fromCol == toCol) {
        return;
    }
    
    GameElement *tmp1 = gameElems[toCol][toRow];
    GameElement *tmp2 = gameElems[fromCol][fromRow];
    gameElems[fromCol][fromRow] = NULL;
    
    // add moved cell
    GameElement *gameElem = GameElement::create();
    gameElem->updateElement(elems[toCol][toRow]);
    addChild(gameElem);
    
    auto hide = Hide::create();
    auto show = Show::create();
    gameElem->runAction(hide);
    gameElems[toCol][toRow] = gameElem;
    
    // add move animation
    TargetedAction *targetAction = TargetedAction::create(gameElem, show);
    
    MoveBy *move = NULL;
    if (toCol != fromCol) {
        move = MoveBy::create(MoveAnimationTime, 1.0 * Vec2(tmp2->getContentSize().height * (toCol - fromCol), 0));
        
    }else if(toRow != fromRow) {
        move = MoveBy::create(MoveAnimationTime, -1.0 * Vec2(0, tmp2->getContentSize().width * (toRow - fromRow)));
    }
    
    if (tmp1 == NULL) {
        tmp2->runAction(Sequence::create(move, hide, targetAction,
                                         CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, tmp2)),
                                         NULL));
    }else{
       tmp2->runAction(Sequence::create(move, hide, targetAction,
                                        CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, tmp1)),
                                        CallFunc::create(CC_CALLBACK_0(Node::removeFromParent, tmp2)),
                                        NULL));
    }
    
}

/*
void GameField::refreshGameField()
{
    for (int col=0; col<DIMENSION; col++) {
        for (int row=0; row<DIMENSION; row++) {
            removeChild(gameElems[col][row]);
            GameElement *gameElem = GameElement::create();
            gameElem->updateElement(elems[col][row]);
            addChild(gameElem);
            
            gameElems[col][row] = gameElem;
        }
    }
}
 */

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
        CCLOG("onTouchBegan inside gamefield, point x:%f, y:%f", location.x, location.y);
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
        if (abs(deltaX) < 4 && abs(deltaY) < 4) {
            return;
        }
        
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
            auto delay = DelayTime::create(MoveAnimationTime+0.1f);
            auto addCell = CallFuncN::create(CC_CALLBACK_1(GameField::addRandomElem, this));
            this->runAction(Sequence::create(delay, addCell, NULL));
            isMoved = false;
        }
        
        isPressed = false;
        touchBeginPoint = Point(0, 0);
        deltaY = 0;
        deltaX = 0;
    }
}

