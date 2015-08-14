//
//  Enemy.h
//  AticBoom
//
//  Created by Claudio Alvial on 1/19/12.
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

#ifndef AticBoom_Enemy_h
#define AticBoom_Enemy_h

#include <vector>
#include <string>
#include "Config.h"
#include "json.h"
#include "cocos2d.h"
#include "GameObject.h"
#include "GameScene.h"

namespace aticboom {
    
    class Enemy : public GameObject {
        
    public:
        Enemy(Json::Value enemy, int world);
        ~Enemy();
        
        int state;
        double speed;
        
        void setFlipRight();
        void setFlipLeft();
        void runAnimationAction(cocos2d::CCAction* action);
        void runMovingAction(cocos2d::CCAction* action);
        void hide();
        void move();
        void moveFinished(CCNode* enemy);
        bool safeToMove(int enemyX, int enemyY);
        void updateGridPosition();
        
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_ENEMY_RUN;
        
    private:
        void initAnimations();
        
    };
    
}

#endif