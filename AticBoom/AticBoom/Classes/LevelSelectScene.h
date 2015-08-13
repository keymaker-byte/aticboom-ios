//
//  LevelSelectScene.h
//  AticBoom
//
//  Created by Claudio Alvial on 1/11/12.
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

#ifndef AticBoom_LevelSelectScene_h
#define AticBoom_LevelSelectScene_h

#include <vector>
#include <string>
#include <assert.h>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCTouchDispatcher.h"
#include "MenuScene.h"
#include "CCScrollLayer.h"
#include "MenuScene.h"
#include "LoadingScene.h"
#include "ComicScene.h"
#include "Border.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

//Escena de seleccion
class LevelSelectScene : public cocos2d::CCLayer
{
public:
    LevelSelectScene();
    ~LevelSelectScene();
	virtual bool init();
    
	static cocos2d::CCScene* scene(int worldId);
    
    static LevelSelectScene* node(int worldId) 
    {
        LevelSelectScene *pRet = new LevelSelectScene();
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
    
    int worldId;
    int levelId;
    bool cleanAfterExit;
    
    int states[aticboom::LEVELS_PER_WORLD];
    
    void goToWorld(CCObject* pSender);
    void goToLevel(CCObject* pSender);
    void onEnter();
    void onExit();
    void keyBackClicked();
};

#endif