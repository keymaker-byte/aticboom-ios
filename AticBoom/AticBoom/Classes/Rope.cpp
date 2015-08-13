//
//  Rope.cpp
//  AticBoom
//
//  Created by Juan Rodriguez on 1/5/12.
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

#include "Rope.h"
#include <algorithm>



namespace aticboom {
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    Rope::Rope(int burningTime) : cocos2d::CCNode() {
        this->burningTime = burningTime;
        this->autorelease();
        this->initAnimations();
    };
    
    Rope::~Rope() {
        this->ANIMATION_ROPE_BURN->release();
        this->ANIMATION_ROPE_STAY->release();
    };
    
    void Rope::initAnimations() {
        char buffer [50];
        
        sprintf (buffer, ROPE_FRAME_A.c_str(), 21);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        pSprite->setPosition(CCPoint(Config::sharedConfig()->SCREEN_WIDTH + Config::sharedConfig()->SCREEN_WIDTH_MARGEN + Config::sharedConfig()->ROPE_WIDTH_MARGEN - (ROPE_TILES_WIDTH * Config::sharedConfig()->TILE_WIDTH/2), Config::sharedConfig()->SCREEN_HEIGHT/2));
        this->addChild(pSprite, 1, ROPE_ROPE_TAG);
        
        ANIMATION_ROPE_BURN = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 10; i <= 47; i++) {
            sprintf (buffer, ROPE_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_ROPE_BURN->addObject(frame);
        }
        ANIMATION_ROPE_STAY = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 10; i <= 10; i++) {
            sprintf (buffer, ROPE_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_ROPE_STAY->addObject(frame);
        }

        
        pSprite->runAction(CCAnimate::actionWithDuration(this->burningTime, CCAnimation::animationWithFrames(ANIMATION_ROPE_BURN), false));
        
        CCSprite* burnSprite = CCSprite::spriteWithSpriteFrameName(ROPE_BURN_FRAME.c_str());
        burnSprite->setPosition( CCPoint(pSprite->getPosition().x, -(ROPE_TILES_BOMB * Config::sharedConfig()->TILE_HEIGHT / 2)) );
        burnSprite->runAction(CCMoveTo::actionWithDuration(this->burningTime, CCPoint(pSprite->getPosition().x, (ROPE_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT - ROPE_TILES_BOMB * Config::sharedConfig()->TILE_HEIGHT))));
        this->addChild(burnSprite, 2, ROPE_BURN_TAG);
        
        CCParticleSystemPoint* fire = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->ROPE_PARTICLE_FIRE.c_str());
        fire->setPosition( CCPoint(burnSprite->getContentSize().width / 2,burnSprite->getContentSize().height) ); 
        burnSprite->addChild(fire, 1, ROPE_FIRE_TAG);
              
        ANIMATION_EXTRA_ROPE_BURN = new CCMutableArray<CCSpriteFrame*>();
        ANIMATION_EXTRA_ROPE_STAY = new CCMutableArray<CCSpriteFrame*>();
    }
    
    void Rope::stopRope() {
        this->stopAllActions();
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(ROPE_ROPE_TAG);
        pSprite->stopAllActions();
        CCSprite* burnSprite = (CCSprite*)this->getChildByTag(ROPE_BURN_TAG);
        burnSprite->stopAllActions();
        CCParticleSystemPoint* fire = (CCParticleSystemPoint*)burnSprite->getChildByTag(ROPE_FIRE_TAG);
        fire->stopSystem();
    }
    
    void Rope::pauseRope() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(ROPE_ROPE_TAG);
        pSprite->stopAllActions();
        pSprite->runAction(CCAnimate::actionWithDuration(this->burningTime, CCAnimation::animationWithFrames(ANIMATION_ROPE_STAY), false));
        CCSprite* burnSprite = (CCSprite*)this->getChildByTag(ROPE_BURN_TAG);
        burnSprite->stopAllActions();

    }
    
    void Rope::resumeRope() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(ROPE_ROPE_TAG);
        pSprite->runAction(CCAnimate::actionWithDuration(this->burningTime, CCAnimation::animationWithFrames(ANIMATION_ROPE_BURN), false));
        CCSprite* burnSprite = (CCSprite*)this->getChildByTag(ROPE_BURN_TAG);
        burnSprite->runAction(CCMoveTo::actionWithDuration(this->burningTime, CCPoint(pSprite->getPosition().x, (ROPE_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT - ROPE_TILES_BOMB * Config::sharedConfig()->TILE_HEIGHT))));
    }
    
    void Rope::addRope(int extraTime){
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(ROPE_ROPE_TAG);
        pSprite->stopAllActions();
        CCSprite* burnSprite = (CCSprite*)this->getChildByTag(ROPE_BURN_TAG);
        burnSprite->stopAllActions();
        
        if(ANIMATION_EXTRA_ROPE_BURN->count()>0){
            ANIMATION_EXTRA_ROPE_BURN->removeAllObjects();
        }
        int toKeep = (int)extraTime*ANIMATION_ROPE_BURN->count()/this->burningTime;
        if(toKeep > 37){
            toKeep = 0;
        }
        for(int i = 37-toKeep; i<37; i++){
            ANIMATION_EXTRA_ROPE_BURN->addObject(ANIMATION_ROPE_BURN->getObjectAtIndex(i));
        }
        if(ANIMATION_EXTRA_ROPE_STAY->count()>0){
            ANIMATION_EXTRA_ROPE_STAY->removeAllObjects();
        }
        ANIMATION_EXTRA_ROPE_STAY->addObject(ANIMATION_EXTRA_ROPE_BURN->getObjectAtIndex(ANIMATION_EXTRA_ROPE_BURN->count()-1));
        pSprite->runAction(CCAnimate::actionWithDuration(extraTime, CCAnimation::animationWithFrames(ANIMATION_EXTRA_ROPE_STAY), false));
        pSprite->runAction(CCAnimate::actionWithDuration(extraTime, CCAnimation::animationWithFrames(ANIMATION_EXTRA_ROPE_BURN), false));
        burnSprite->setPosition( CCPoint(pSprite->getPosition().x, -(ROPE_TILES_BOMB * Config::sharedConfig()->TILE_HEIGHT / 2)+(38-ANIMATION_EXTRA_ROPE_BURN->count()) * Config::sharedConfig()->WOOD_OBJECT_MARGEN)  ); 
        //pSprite->runAction(CCAnimate::actionWithDuration(this->burningTime+extraTime, CCAnimation::animationWithFrames(ANIMATION_ROPE_BURN), false));
        burnSprite->runAction(CCMoveTo::actionWithDuration(extraTime, CCPoint(pSprite->getPosition().x, (ROPE_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT - ROPE_TILES_BOMB * Config::sharedConfig()->TILE_HEIGHT))));
    }
    
    void Rope::pauseAudio(bool pause) {
    }
    
    void Rope::explode() {
        this->stopRope();
        this->runAction(CCHide::action());
    }
    
}
