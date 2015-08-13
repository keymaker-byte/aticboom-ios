//
//  IntroScene.h
//  AticBoom
//
//  Created by Claudio Alvial on 1/6/12.
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

#ifndef AticBoom_IntroScene_h
#define AticBoom_IntroScene_h

#include <vector>
#include <string>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCTouchDispatcher.h"
#include "MenuScene.h"
#include "Border.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

class IntroScene : public cocos2d::CCLayerColor
{
public:
    IntroScene();
    ~IntroScene();
	virtual bool init();
    
	static cocos2d::CCScene* scene();
    
    static IntroScene* node() 
    {
        IntroScene *pRet = new IntroScene();
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
    
    void goToTitle(CCObject* pSender); 
    
    void onEnter();
    void onExit();
    
    void loadTextures();
    void readSoundSettings();
};

#endif
