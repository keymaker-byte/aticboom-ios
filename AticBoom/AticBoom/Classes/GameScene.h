//
//  GameScene.h
//  AticBoom
//
//  Created by Juan Rodriguez on 21/12/2011.
//

/*
 * Copyright (C) 2015 Juan Francisco Rodríguez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef AticBoom_GameScene_h
#define AticBoom_GameScene_h

#include <vector>
#include <string>
#include <fstream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "json.h"
#include "Level.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Rope.h"
#include "Music.h"
#include "MenuScene.h"
#include "WorldSelectScene.h"
#include "Hud.h"
#include "Helm.h"
#include "AticBoomObjC.h"
#include "Border.h"
#include "CCTouchDispatcher.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace aticboom;

class GameScene : public cocos2d::CCLayer {
    
public:
    GameScene();
    ~GameScene();
    virtual bool init();
    
    static cocos2d::CCScene* scene(int worldId, int levelId);
    static GameScene* node(int worldId, int levelId)
    {
        GameScene *pRet = new GameScene();
        pRet->worldId = worldId;
        pRet->levelId = levelId;
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    };
    
    int worldId;
    int levelId;
    int scroll;
    int levelScore;
    double labelScore;
    int bestScore;
    int usedBubbles;
    bool musicLoaded;
    bool isBestScore;
    bool cleanAfterExit;
    bool paused;
    bool isNewGolden;
    bool isGoldenWorld;
    bool isCompletedWorld;
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void scrollUp();
    void scrollUpFinished(CCNode* sender);
    void secondTimer(ccTime delta);
    void drawInformation();
    void winLevel(CCNode* nada);
    void loseLevel(CCNode* nada);
    void pause();
    void funlose();
    void writeLevelJson(bool starState);
    void writeLevelScore();
    void reachScore();
    void scrollDown();
    void scrollDownFinished(CCNode* sender);
    void pane();
    void paneFinished(CCNode* sender);
    void nextLevel();
    void playAgain();
    void mainMenu();
    static void worldSelectScreen();
    void onEnter();
    void onExit();
    void destroyLevel();
    void makeLevel();
    void keyBackClicked();
    
};

#endif
