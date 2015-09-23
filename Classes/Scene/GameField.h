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
#include "GameElement.h"
#include "GameConfig.h"

USING_NS_CC;

enum MoveDirection: unsigned {
    MoveDirectionNone,
    MoveDirectionLeft,
    MoveDirectionRight,
    MoveDirectionUp,
    MoveDirectionDown,
};

enum ElemStatus: unsigned {
    ElemStatusEmpty,
    ElemStatusNew,
    ElemStatusMerged,
    ElemStatusNormal,
};

class GameElement;
class GameField : public Layer
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
    
    void restartGame();

    
private:
    void createElemArray(void);
    bool addRandomElem();
    
    void moveElem(GameElement *elemFrom, GameElement *elemTo);
    void mergeElems(GameElement *elemFrom, GameElement *elemTo);
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
    bool checkGameOver();
    void gameOver();
    
private:
    GameElement *_gameElems[DIMENSION][DIMENSION];
    GameElement *_gameElemsAni[DIMENSION][DIMENSION];
    ElemStatus _emptyElemIndexes[DIMENSION][DIMENSION];
    
    MoveDirection _moveDireciton;
    bool _isPressed;
    Point _touchBeginPoint;
    bool _isMoved;
    bool _isMerged;
    unsigned int _score;
    Sprite *_gamefield;
};

#endif /* defined(__TransitionCocos2dX__GameField__) */
