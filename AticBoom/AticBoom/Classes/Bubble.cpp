//
//  Bubble.cpp
//  AticBoom
//
//  Created by Juan Rodriguez on 23/12/2011.
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

#include "Bubble.h"

namespace aticboom {
    
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    Bubble::Bubble(Json::Value bubble, int world) : Bubble::GameObject(bubble, world){
        this->tileWidth = BUBBLE_TILES_WIDTH;
        this->tileHeight = BUBBLE_TILES_HEIGHT;
        this->state = BUBBLE_STATE_NORMAL;
        this->initAnimations();
        this->setTilePosition();
    };
    
    Bubble::~Bubble() {
        this->ANIMATION_BUBBLE_STAY->release();
        this->ANIMATION_BUBBLE_UP->release();
        this->ANIMATION_BUBBLE_EXPLODE->release();
    };
    
    void Bubble::initAnimations() {
        char buffer [50];
        sprintf (buffer, BUBLE_FRAME_A.c_str(), 1);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        this->addChild(pSprite, 1, BUBBLE_SPRITE_TAG);
        ANIMATION_BUBBLE_STAY = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 5; i <= 5; i++) {
            sprintf (buffer, BUBLE_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_BUBBLE_STAY->addObject(frame);
        }
        ANIMATION_BUBBLE_UP = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 30; i++) {
            sprintf (buffer, BUBLE_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_BUBBLE_UP->addObject(frame);
        }
        ANIMATION_BUBBLE_EXPLODE = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 30; i++) {
            sprintf (buffer, BUBLE_FRAME_B.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_BUBBLE_EXPLODE->addObject(frame);
        }
        this->runAnimationAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_BUBBLE_STAY, 0.03), false));
    }
    
    void Bubble::runAnimationAction(CCAction* action) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(BUBBLE_SPRITE_TAG);
        pSprite->runAction(action);
    }
    
    void Bubble::runMovingAction(CCAction* action){
        this->runAction(action);
    }
    
    void Bubble::changeSpriteSize(float newsize) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(BUBBLE_SPRITE_TAG);
        pSprite->setScale(newsize);
    }
    
    void Bubble::hide(CCNode* bubble) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(BUBBLE_SPRITE_TAG);
        pSprite->stopAllActions();
        this->stopAllActions();
        this->runAction(CCHide::action());
    }
    
    void Bubble::moveUp(double speed, int power) {
        if(power > 1) {
            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_FAN.c_str()));
        }
        else {
            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_UP.c_str()));
        }
        CCPoint hudPos = Geometry::getTilePosition(this->position[0], this->position[1] + FLOORS_TILES_HEIGHT*power, this->tileWidth, this->tileHeight);
        this->stopAllActions();
        this->setPosition(this->touchcoords);
        CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(speed * FLOORS_TILES_HEIGHT , hudPos);
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Bubble::moveUpFinished));
        this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_BUBBLE_UP, 0.02), false)));
        this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
    }
    
    void Bubble::moveUpFinished(CCNode* bubble) {
        CCFiniteTimeAction* action = CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_BUBBLE_EXPLODE, 0.015), false);
        CCFiniteTimeAction* actionDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Bubble::hide));
        CCParticleSystemPoint* explotion = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->BUBLE_PARTICLE_EXPLODE.c_str());
        explotion->setPosition( CCPoint(0,0) );
        this->addChild(explotion, 0, BUBBLE_EXPLOTION_TAG);
        this->runAnimationAction( CCSequence::actions(action, actionDone, NULL));
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_POP.c_str()));
    }
    
}
