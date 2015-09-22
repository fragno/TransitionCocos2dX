//
//  GameElement.h
//  TransitionCocos2dX
//
//  Created by chrisfnxu on 7/22/15.
//
//

#ifndef __TransitionCocos2dX__GameElement__
#define __TransitionCocos2dX__GameElement__

#include "cocos2d.h"
#include "GameConfig.h"

USING_NS_CC;

class GameElement : public Layer
{
public:
    GameElement();
    virtual ~GameElement(void);
    
    // overrides
    virtual bool init(void) override;
    
    CREATE_FUNC(GameElement);

    void mergeElement(GameElement *elem);
    
    bool isEmpty();
    
    GameElement *copy();
    
    // getter && setter
    void setNumber(int number);
    int getNumber();
    void setSideLen(float sideLen);
    float getSideLen();
    void setPos(Vec2 pos);
    Vec2 getPos();
    void setIsMerged(bool isMerged);
    bool getIsMerged();
    void setIsNew(bool isNew);
    
private:
    bool _isNew;
    float _sideLen;
    int _number;
    bool _isMerged;
    Vec2 _pos;
    
private:
    Sprite *_elem;
    Label *_numberLabel;
};

#endif /* defined(__TransitionCocos2dX__GameElement__) */
