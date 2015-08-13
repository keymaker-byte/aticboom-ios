//
//  ComicScene.h
//  AticBoom
//
//  Created by Claudio Alvial on 2/9/12.
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

#ifndef AticBoom_ComicScene_h
#define AticBoom_ComicScene_h

#include <vector>
#include <string>

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCTouchDispatcher.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Border.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

namespace aticboom {
    
class ComicScene : public cocos2d::CCLayer
{
    public:
        ComicScene();
        ~ComicScene();
        virtual bool init();
    
        static cocos2d::CCScene* scene(int sequence);

        static ComicScene* node(int sequence) 
        {
            ComicScene *pRet = new ComicScene();
            pRet->sequence = sequence;
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
    
        int sequence;
        int currentPage;
        int totalPages;
        bool touchEnabled;
        bool cleanAfterExit;
        void onEnter();
        void onExit();
        void showCurrentPage();
        void enableTouch();
        void cleanPages();
        void actionStopper(CCObject* pSender);
        void setupPlay();
        bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    };
}

#endif
