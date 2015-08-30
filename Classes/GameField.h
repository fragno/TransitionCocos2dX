//
//  GameField.h
//  TransitionCocos2dX
//
//  Created by fragno on 15/7/19.
//
//

#ifndef __TransitionCocos2dX__GameField__
#define __TransitionCocos2dX__GameField__

#include "cocos2d.h"
#include "Element.h"
#include "GameElement.h"

USING_NS_CC;

enum MoveDirection: unsigned {
    MoveDirectionNone,
    MoveDirectionLeft,
    MoveDirectionRight,
    MoveDirectionUp,
    MoveDirectionDown,
};

#define DIMENSION 4

class GameField : public cocos2d::Layer
{
public:
    GameField();
    virtual ~GameField(void);
    
    virtual bool init(void) override;
    
    // touch event
    virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
    virtual void onTouchMoved(Touch *touch, Event *unused_event) override;
    virtual void onTouchCancelled(Touch *touch, Event *unused_event) override;
    virtual void onTouchEnded(Touch *touch, Event *unused_event) override;
    
    CREATE_FUNC(GameField);
    
    // game over
    void gameOver();
    
private:
    void addRandomElem(Node * node);
//    void refreshGameField();
    void moveAnimation(int fromRow, int fromCol, int toRow, int toCol);
    
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
private:
    Element* elems[DIMENSION][DIMENSION];
    GameElement* gameElems[DIMENSION][DIMENSION];
    std::vector<int> emptyElemIndexes;
    
    MoveDirection moveDireciton;
    bool isPressed;
    Point touchBeginPoint;
    bool isMoved;
    bool isMerged;
    unsigned int score;
};

#endif /* defined(__TransitionCocos2dX__GameField__) */
