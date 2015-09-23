//
//  GameField.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#include "GameField.h"
#include "GameElement.h"
#include "GameOver.h"

#define MoveAnimationTime 0.1f
#define AddAnimationTime 0.2f

GameField::GameField()
: _moveDireciton(MoveDirectionNone)
, _isMerged(false)
, _isMoved(false)
, _isPressed(false)
, _touchBeginPoint(Point(0,0))
, _score(0)
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
    
    this->removeAllChildrenWithCleanup(true);
    
    // valid anchor point
    ignoreAnchorPointForPosition(false);
    
    // create game field
    _gamefield = Sprite::create();
    _gamefield->setColor(Color3B::WHITE);
    _gamefield->setTextureRect(Rect(0, 0, FieldWidth, FieldWidth));
    _gamefield->setAnchorPoint(Vec2(0,0));
    _gamefield->setPosition(Vec2(0, 0));
    addChild(_gamefield);
    
    setContentSize(_gamefield->getContentSize());
    
    // create event listener
    auto dispatch = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameField::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameField::onTouchMoved, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameField::onTouchCancelled, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameField::onTouchEnded, this);
    listener->setSwallowTouches(true);
    dispatch->addEventListenerWithSceneGraphPriority(listener, this);
    
    // create array
    createElemArray();
    
    // add first elem
    addRandomElem();
    addRandomElem();
    
    return true;
}

void GameField::restartGame()
{
    createElemArray();
    addRandomElem();
    addRandomElem();
}

#pragma mark - 
#pragma mark - private
void GameField::createElemArray()
{
    _gamefield->removeAllChildren();
    
    // create cardArray
    for (int col=0; col<DIMENSION; col++) {
        for (int row=0; row<DIMENSION; row++) {
            GameElement *elemBack = GameElement::create();
            elemBack->setNumber(0);
            elemBack->setPos(Vec2(col, row));
            _gamefield->addChild(elemBack, 0);
            
            GameElement *elem = GameElement::create();
            elem->setNumber(0);
            elem->setPos(Vec2(col, row));
            _gamefield->addChild(elem, 1);
            _gameElems[col][row] = elem;
            
            _gameElemsAni[col][row] = GameElement::create();
            _gameElemsAni[col][row]->setNumber(0);
            _gameElemsAni[col][row]->setPos(Vec2(col, row));
            _gamefield->addChild(_gameElemsAni[col][row], 10);
            _gameElemsAni[col][row]->setVisible(false);
        }
    }
}

bool GameField::addRandomElem()
{
    int emptyCellNum = 0;
    printf("empty Cells: \n");
    for (int col=0; col<DIMENSION; col++) {
        for (int row=0; row<DIMENSION; row++) {
            if (_gameElems[col][row]->getNumber() == 0) {
                printf("col: %d, row: %d \n", col, row);
                emptyCellNum ++;
            }
        }
    }
    printf("emptyCellNum: %d\n", emptyCellNum);
    
    if (emptyCellNum <= 0) {
        return false;
    }
    
    int randomIndex = RandomHelper::random_int(0, emptyCellNum-1);
    int random2or4 = RandomHelper::random_int(1, 2);
    int number = (random2or4 == 1) ? 2 : 4;
    
    
    int tmpEmptyCellNum = 0;
    for (int col=0; col<DIMENSION; col++) {
        for (int row=0; row<DIMENSION; row++) {
            if (_gameElems[col][row]->getNumber() == 0) {
                if (tmpEmptyCellNum == randomIndex) {
                    CCLOG("randomIndex: %d", randomIndex);
                    _gameElems[col][row]->setIsNew(true);
                    _gameElems[col][row]->setNumber(number);
                    
                    _gameElemsAni[col][row]->setNumber(number);
                }
                tmpEmptyCellNum ++;
            }
        }
    }
    
    bool bGameOver = checkGameOver();
    if (bGameOver) {
        CCLOG("game over");
        gameOver();
        return true;
    }
    
    return true;
}


#pragma mark -
#pragma mark - move action

void GameField::moveElem(GameElement *elemFrom, GameElement *elemTo)
{
    int x = elemFrom->getPos().x;
    int y = elemFrom->getPos().y;
    
    auto place = Place::create(elemFrom->getPosition());
    _gameElemsAni[x][y]->setNumber(_gameElems[x][y]->getNumber());
    auto show = Show::create();
    auto move = MoveBy::create(MoveAnimationTime, Point(-(elemFrom->getSideLen() - ElemSpace)*(elemFrom->getPos().x - elemTo->getPos().x - ElemSpace), 0));
    auto hide = Hide::create();
    _gameElemsAni[x][y]->runAction(Sequence::create(place, show, move, hide, NULL));
    
    // 目的elem是空的，直接移动
    if (elemTo->isEmpty()) {
        elemTo->setNumber(elemFrom->getNumber());
        elemFrom->setNumber(0);
        _isMoved = true;
        
        return;
    }
    
    // 目的elem和源elem相同，merge
    if (elemFrom->getNumber() == elemTo->getNumber()) {
        // TODO: add merge animation
        
        mergeElems(elemFrom, elemTo);
        _isMoved = true;
        return;
    }
}


void GameField::mergeElems(GameElement *elemFrom, GameElement *elemTo)
{
    if (elemFrom->getNumber() != elemTo->getNumber()) {
        return;
    }
    
    if (elemFrom->getIsMerged() || elemTo->getIsMerged()) {
        CCLOG("elem has already merged, can not merge again, pass");
        return;
    }
    
    elemTo->mergeElement(elemFrom);
    elemFrom->setNumber(0);
    
    auto merge = Sequence::create(ScaleTo::create(0.1f, 1.2f), ScaleTo::create(0.1f, 1.0f), NULL);
    elemTo->runAction(merge);
}

void GameField::moveLeft()
{
    CCLOG("moveLeft called");

    for (int col=1; col<DIMENSION; col++) {
        for (int row=0; row<DIMENSION; row++) {
            
            // only not empty cell need move
            if (_gameElems[col][row]->getNumber() > 0) {
                
                int innerCol = col;
                for (; innerCol>0; innerCol--) {
                    
                    // left cell is empty or left cell is same, move cell
                    if (_gameElems[innerCol-1][row]->getNumber() == 0 ||
                        (_gameElems[innerCol-1][row]->getNumber() == _gameElems[innerCol][row]->getNumber()))
                    {
                        moveElem(_gameElems[innerCol][row], _gameElems[innerCol-1][row]);
                        
                    }else{
                        break;
                    }
                    
                }// the cell is moved left, from [col][row] -> [innerCol][row]
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
            if (_gameElems[col][row]->getNumber() > 0) {
                
                int innerCol = col;
                for (; innerCol<DIMENSION-1; innerCol++) {
                    
                    // right cell is empty or right cell is the same, mvoe cell
                    if (_gameElems[innerCol+1][row]->getNumber() == 0 ||
                        (_gameElems[innerCol+1][row]->getNumber() == _gameElems[innerCol][row]->getNumber()))
                    {
                        moveElem(_gameElems[innerCol][row], _gameElems[innerCol+1][row]);
                        
                    }else{
                        break;
                    }
                    
                }// the cell is moved right, from [col][row]->[innerCol][row]
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
            if (_gameElems[col][row]->getNumber() > 0) {
                
                int innerRow = row;
                for (; innerRow>0; innerRow--) {
                    
                    // up cell is emtpy or up cell is same, move cell
                    if (_gameElems[col][innerRow-1]->getNumber() == 0 ||
                        (_gameElems[col][innerRow-1]->getNumber() == _gameElems[col][innerRow]->getNumber()))
                    {
                        moveElem(_gameElems[col][innerRow], _gameElems[col][innerRow-1]);
                        
                    }else{
                        break;
                    }
                } // the cell is moved up, from [col][row] -> [col][innerRow]
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
            if (_gameElems[col][row]->getNumber() > 0) {
                
                int innerRow = row;
                for (; innerRow<DIMENSION-1; innerRow++) {
                    
                    // the down cell is empty or the down cell is same, move cell
                    if (_gameElems[col][innerRow+1]->getNumber() == 0 ||
                        (_gameElems[col][innerRow+1]->getNumber() == _gameElems[col][innerRow]->getNumber()))
                    {
                        moveElem(_gameElems[col][innerRow], _gameElems[col][innerRow+1]);
                        
                    }else{
                        break;
                    }
                    
                } // the cell is moved down, from [col][row] -> [col][innerRow]
            }
        }
    }
}

void GameField::gameOver()
{
    CCLOG("game over!");
    Director::getInstance()->replaceScene(GameOver::createScene());
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
        _touchBeginPoint = location;
        _isPressed = true;
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
    if (_isPressed && _touchBeginPoint != Point(0, 0)) {
        
        // decide move direction
        Point location = touch->getLocationInView();
        location = Director::getInstance()->convertToGL(location);
        int deltaX = location.x - _touchBeginPoint.x;
        int deltaY = location.y - _touchBeginPoint.y;
        if (abs(deltaX) < 10 && abs(deltaY) < 10) {
            return;
        }
        
        if (abs(deltaX) >= abs(deltaY)) {
            _moveDireciton = deltaX > 0 ?  MoveDirectionRight : MoveDirectionLeft;
            
        }else{
            _moveDireciton = deltaY > 0 ? MoveDirectionUp : MoveDirectionDown;
        }
        CCLOG("onTouch move direction %d", _moveDireciton);
        
        // do the move work
        switch (_moveDireciton) {
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
        
        if (_isMoved) {
            this->runAction(Sequence::create(
                                             DelayTime::create(AddAnimationTime),
                                             CallFunc::create(CC_CALLBACK_0(GameField::addRandomElem, this)), NULL)
                            );
            
            _score += 2;
            
            // add custom event
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            EventCustom event("CellMoved");
            char* buf = new char[10];
            sprintf(buf, "%d", _score);
            event.setUserData((void *)buf);
            dispatcher->dispatchEvent(&event);
            
            CCLOG("score = %u", _score);
            _isMoved = false;
        }
        
        for (int row=0; row<DIMENSION; row++) {
            for (int col=0; col<DIMENSION; col++) {
                _gameElems[col][row]->setIsMerged(false);
                printf("%d ", _gameElems[col][row]->getNumber());
            }
            printf("\n");
        }
        
        _isPressed = false;
        _touchBeginPoint = Point(0, 0);
        deltaY = 0;
        deltaX = 0;
    }
}

bool GameField::checkGameOver()
{
    bool bGameOver = true;
    
    // check whether field is full，if not return false
    for (int row=0; row<DIMENSION; row++) {
        for (int col=0; col<DIMENSION; col++) {
            if (_gameElems[col][row]->getNumber() == 0) {
                bGameOver = false;
                return bGameOver;
            }
        }
    }
    
    // check whether can be moved， if yes， return false
    for (int row=1; row<DIMENSION; row++) {
        for (int col=1; col<DIMENSION; col++) {
            if (_gameElems[col][row]->getNumber() == _gameElems[col][row-1]->getNumber() // 和它左边的相等
                || _gameElems[col][row]->getNumber() == _gameElems[col-1][row]->getNumber()) // 和它上边的相等
            {
                // 还有可以移动的空间，游戏没结束
                bGameOver = false;
                return bGameOver;
            }
        }
    }
    
    // 游戏结束
    return bGameOver;
}



