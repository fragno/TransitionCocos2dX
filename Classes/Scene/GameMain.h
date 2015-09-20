#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameField;
class ScoreLabel;
class GameMain : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameMain);
    
    // menu functions
    void menuRestartCallback(Ref* pSender);
    void menuCloseCallback(Ref* pSender);
    void cellMoved(EventCustom* event);
    void gameOver(EventCustom* event);
    
private:
    GameField *gameField;
    ScoreLabel *scoreLabel;
};

#endif // __GAME_SCENE_H__
