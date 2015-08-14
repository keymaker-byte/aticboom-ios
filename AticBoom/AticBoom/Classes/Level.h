//
//  Level.h
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

#ifndef AticBoom_Level_h
#define AticBoom_Level_h

#include <vector>
#include <string>
#include "Config.h"
#include "json.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Bubble.h"
#include "Floor.h"
#include "Stair.h"
#include "Hole.h"
#include "Star.h"
#include "Exit.h"
#include "Player.h"
#include "Key.h"
#include "Text.h"
#include "Fancy.h"
#include "Enemy.h"
#include "Fan.h"
#include "Wall.h"
#include "Mesh.h"
#include "Button.h"
#include "ExtraRope.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

namespace aticboom {
    
    class Level : public cocos2d::CCNode {
        
    public:
        Level(Json::Value level);
        ~Level();
        
        string name;
        int time;
        int totalTime;
        int world;
        int state;
        int floorSize;
        int starSize;
        int extraBubblesSize;
        int levelHint;
        int bubbleNumber;
        Mesh* mesh;
        int fancyCount;
        
        void addChild(CCNode *child, int zOrder, int tag);
        void addChild(CCNode *child, int zOrder);
        void addChild(CCNode *child);
        
    };
    
}

#endif
