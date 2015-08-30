#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameField.h"
#include "ScoreLabel.h"

class GameMain : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
    
    // menu functions
    void menuRestartCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void cellMoved(EventCustom* event);
    
private:
    GameField *gameField;
    ScoreLabel *scoreLabel;
};

#endif // __GAME_SCENE_H__
