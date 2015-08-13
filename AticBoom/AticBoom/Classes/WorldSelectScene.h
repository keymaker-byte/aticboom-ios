//
//  WorldSelectScene.h
//  AticBoom
//
//  Created by Claudio Alvial on 1/9/12.
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

#ifndef AticBoom_WorldSelectScene_h
#define AticBoom_WorldSelectScene_h

#include <vector>
#include <string>
#include <assert.h>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCTouchDispatcher.h"
#include "MenuScene.h"
#include "CCScrollLayer.h"
#include "MenuScene.h"
#include "LevelSelectScene.h"
#include "AticBoomObjC.h"
#include "Border.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class WorldSelectScene : public cocos2d::CCLayer
{
public:
    WorldSelectScene();
    ~WorldSelectScene();
	virtual bool init();
    
	static cocos2d::CCScene* scene(int worldId);

    static WorldSelectScene* node(int worldId) 
    {
        WorldSelectScene *pRet = new WorldSelectScene();
        pRet->worldId = worldId;
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
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    
    bool movingTouch;
    int touchMoved;
    int worldTouch;
    CCPoint previousTouch;
    int worldId;
    int totalGold;
    int totalStar;

    void goToMenu(CCObject* pSender);
    void goToLevels(int worldId);
    void makeVisible();
    void reloopCloud(CCNode* cloud);
    int checkAllLevels(Json::Value rootL, int worldId);
    Json::Value readLevelsJson();
    
    bool* enabled;
    
    void onEnter();
    void onExit();
    void showConfirmation();
    void hideConfirmation();
    bool confirmationMode;
    void keyBackClicked();

};

#endif