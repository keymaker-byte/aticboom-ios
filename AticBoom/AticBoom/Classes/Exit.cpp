//
//  Exit.cpp
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

#include "Exit.h"

namespace aticboom {
    
    using namespace cocos2d;
    
    Exit::Exit(Json::Value exit, int world) : Exit::GameObject(exit, world){
        this->tileWidth =  EXIT_TILES_WIDTH;
        this->tileHeight = EXIT_TILES_HEIGHT;
        this->initAnimations();
        this->setTilePosition();
    };
    
    Exit::~Exit() {
        this->ANIMATION_EXIT_NORMAL->release();
        this->ANIMATION_EXIT_FINISH->release();
        this->ANIMATION_EXIT_END->release();
    };
    
    void Exit::initAnimations() {
        char buffer [50];
        sprintf (buffer, EXIT_FRAME_A.c_str(), 1);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        this->addChild(pSprite, 0, EXIT_SPRITE_TAG);
        ANIMATION_EXIT_NORMAL = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 14; i++) {
            sprintf (buffer, EXIT_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_EXIT_NORMAL->addObject(frame);
        }
        ANIMATION_EXIT_FINISH = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 15; i <= 30; i++) {
            sprintf (buffer, EXIT_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_EXIT_FINISH->addObject(frame);
        }
        ANIMATION_EXIT_END = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 31; i <= 44; i++) {
            sprintf (buffer, EXIT_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_EXIT_END->addObject(frame);
        }
        this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_EXIT_NORMAL, 0.02), false)));
    }
    
    void Exit::runAnimationAction(CCAction* action) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(EXIT_SPRITE_TAG);
        pSprite->runAction(action);
    }
    
    void Exit::runMovingAction(CCAction* action){
        this->runAction(action);
    }
    
    void Exit::hide() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(EXIT_SPRITE_TAG);
        pSprite->stopAllActions();
        this->stopAllActions();
        this->runAction(CCHide::action());
    }
    
    void Exit::finish() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(EXIT_SPRITE_TAG);
        pSprite->stopAllActions();
        this->stopAllActions();
        CCFiniteTimeAction* action = CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_EXIT_FINISH, 0.03), false);
        CCFiniteTimeAction* actionB = (CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_EXIT_END, 0.02), false));
        this->runAnimationAction( CCSequence::actions(action,actionB,  NULL) );
    }
    
}