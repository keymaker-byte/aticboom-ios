//
//  Key.cpp
//  AticBoom
//
//  Created by Juan Rodriguez on 26/12/2011.
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

#include "Key.h"

namespace aticboom {
    
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    Key::Key(Json::Value key, int world) : Key::GameObject(key, world) {
        this->tileWidth = KEY_TILES_WIDTH;
        this->tileHeight = KEY_TILES_HEIGHT;
        this->floorIndex = key["floorIndex"].asInt();
        this->initAnimations(); 
        this->setTilePosition();
    };
    
    Key::~Key() {
        this->ANIMATION_KEY_STAY->release();
        this->ANIMATION_KEY_GRAB->release();
    };
    
    void Key::initAnimations() {
        char buffer [50];
        
        //init a sprite
        sprintf (buffer, KEY_FRAME_A.c_str(), 1);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        this->addChild(pSprite,1,KEY_SPRITE_TAG);
        
        ANIMATION_KEY_STAY = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 30; i++) {
            sprintf (buffer, KEY_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_KEY_STAY->addObject(frame);
        }
        
        ANIMATION_KEY_GRAB = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 30; i++) {
            sprintf (buffer, KEY_FRAME_B.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_KEY_GRAB->addObject(frame);
        }

        CCParticleSystemPoint* shine = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->PARTICLE_SHINE.c_str());
        shine->setPosition( CCPoint(0,0) );
        shine->setPositionType(kCCPositionTypeRelative);
        this->addChild(shine, 0, KEY_SHINE_TAG);
        
        this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_KEY_STAY, 0.03), false)));
        
    }
    
    void Key::runAnimationAction(CCAction* action) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(KEY_SPRITE_TAG);
        pSprite->runAction(action);
    }
    
    void Key::runMovingAction(CCAction* action){
        this->runAction(action);
    }
    
    
    void Key::hide(CCNode* key) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(KEY_SPRITE_TAG);
        pSprite->stopAllActions();
        CCParticleSystemPoint* shine = (CCParticleSystemPoint*)this->getChildByTag(KEY_SHINE_TAG);
        shine->stopSystem();
        this->stopAllActions();
        this->runAction(CCHide::action());
    }
    
    void Key::grab() {
        CCFiniteTimeAction* action = CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_KEY_GRAB, 0.03), false);
        CCFiniteTimeAction* actionDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Key::hide));
        this->runAnimationAction( CCSequence::actions(action, actionDone, NULL) );
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_KEY.c_str()));
    }
    
    void Key::makeDark() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(KEY_SPRITE_TAG);
        pSprite->setColor(ccc3(DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR));
        CCParticleSystemPoint* shine = (CCParticleSystemPoint*)this->getChildByTag(KEY_SHINE_TAG);
        shine->stopSystem();
    }

}
