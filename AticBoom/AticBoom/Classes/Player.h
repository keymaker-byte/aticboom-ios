//
//  Player.h
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

#ifndef AticBoom_Player_h
#define AticBoom_Player_h


#include <vector>
#include <string>

#include "Config.h"
#include "Music.h"

#include "json.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "GameObject.h"
#include "Bubble.h"
#include "ExtraBubble.h"
#include "Level.h"
#include "GameScene.h"
#include "Button.h"

namespace aticboom {
    class Player : public GameObject
    {
    public:
        Player(Json::Value player, int world);
        ~Player();
        int state;
        int floor;
        bool hasKey;
        bool hasStar;
        int starNumber;
        double speed;
        
        int floorsUpNumber;
        int floorsDownFollow;
        int floorsUpFollow;
        bool floorsDownFollowOk;
        bool floorsUpFollowOk;
        
            
        void setFlipRight();
        void setFlipLeft();
        
        void runAnimationAction(cocos2d::CCAction* action);
        void runMovingAction(cocos2d::CCAction* action);
        void hide();
        void move();
        void moveFinished(CCNode* player);
        bool checkColision();
        void throwBomb(CCNode* player);
        void explode();
        void fallDown(CCNode* player);
        void laughForever(CCNode* player);
        bool checkForFans();
        bool checkForFire();
        void clearFloor(int floorNumber);
        
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_PLAYER_RUN;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_PLAYER_STAIR;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_PLAYER_HOLE;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_PLAYER_BUBBLE;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_PLAYER_WIN;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_PLAYER_THROW;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_PLAYER_EXPLODE;
        
    private:
        void initAnimations();
    };
}

#endif
