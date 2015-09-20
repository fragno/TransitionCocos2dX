//
//  SceneTrans.cpp
//  TransitionCocos2dX
//
//  Created by fragno on 15/9/4.
//
//

#include "GameManager.h"
#include "GameField.h"
#include "GameMain.h"
#include "GameOver.h"


void GameManager::startFlipInterface(int iType)
{
    Scene* pScene = NULL;
    
    switch (iType) {
        case GAME_START:
            pScene = GameMain::createScene();
            break;
            
        case GAME_OVER:
            pScene = TransitionCrossFade::create(1.0f, GameOver::createScene());
            break;
            
        default:
            return;
    }
    
    Director::getInstance()->replaceScene(pScene);
}