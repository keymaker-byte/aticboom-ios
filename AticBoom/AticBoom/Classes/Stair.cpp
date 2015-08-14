//
//  Stair.cpp
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

#include "Stair.h"

namespace aticboom {
    
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    Stair::Stair(Json::Value stair, int world) : Stair::GameObject(stair, world){
        this->type = stair["type"].asInt();
        this->tileWidth = STAIR_TILES_WIDTH;
        this->tileHeight = STAIR_TILES_HEIGHT;
        this->setTilePosition();
        this->initAnimations();
    };
    
    Stair::~Stair() {
    };
    
    void Stair::initAnimations() {
        char buffer [50];
        bool night = Geometry::isNight(this->world);
        sprintf (buffer, STAIR_PNG.c_str(), this->world);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        if(night) {
            pSprite->setColor(ccc3(NIGHT_COLOR_CORRECTOR_R, NIGHT_COLOR_CORRECTOR_G, NIGHT_COLOR_CORRECTOR_B));
        }
        this->addChild(pSprite, 0, STAIR_SPRITE_TAG);
        if (this->type == 1) {
            CCPoint currentPosition = this->getPosition();
            float currentYPosition = currentPosition.y;
            this->setPositionY(currentYPosition + STAIR_TILES_HEIGHT / 3 * Config::sharedConfig()->TILE_WIDTH);
        }
        CCNode* sTapa = CCNode::node();
        CCSprite* pSpriteTapa = CCSprite::spriteWithSpriteFrameName("stair_door.png");
        pSpriteTapa->setAnchorPoint(CCPoint(1, 0.5f));
        pSpriteTapa->setPosition(CCPoint(pSpriteTapa->getContentSize().width,0));
        sTapa->addChild(pSpriteTapa, 1, STAIRDOOR_TAG);
        sTapa->setPosition(CCPoint(-pSprite->getContentSize().width/2,pSprite->getContentSize().height * 0.25));
        this->addChild(sTapa, 1, STAIRDOORPARENT_TAG);
    }
    
    void Stair::runAnimationAction(CCAction* action) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(STAIR_SPRITE_TAG);
        pSprite->runAction(action);
    }
    
    void Stair::runMovingAction(CCAction* action){
        this->runAction(action);
    }
    
    void Stair::hide() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(STAIR_SPRITE_TAG);
        pSprite->stopAllActions();
        this->stopAllActions();
        this->runAction(CCHide::action());
    }
    
    void Stair::makeDark() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(STAIR_SPRITE_TAG);
        pSprite->setColor(ccc3(DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR));
    }
    
    void Stair::switchPosition() {
        if (this->type == 1) {
            this->runAction(CCMoveBy::actionWithDuration(0.5, CCPoint(0, -(STAIR_TILES_HEIGHT / 3) * Config::sharedConfig()->TILE_HEIGHT)));
            this->type = 0;
        }
        else if (this->type == 0) {
            this->runAction(CCMoveBy::actionWithDuration(0.5, CCPoint(0, (STAIR_TILES_HEIGHT / 3) * Config::sharedConfig()->TILE_HEIGHT)));
            this->type = 1;
        }
    }
    
    void Stair::doorOpenLeft() {
        CCNode* nParent = (CCNode*)this->getChildByTag(STAIRDOORPARENT_TAG);
        CCSprite* pSpriteTapa = (CCSprite*)nParent->getChildByTag(STAIRDOOR_TAG);
        CCFiniteTimeAction* rotateAction = CCEaseBounceOut::actionWithAction(CCRotateBy::actionWithDuration(0.5, 90));
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Stair::doorCloseLeft));
        pSpriteTapa->runAction(CCSequence::actions(rotateAction, CCMoveBy::actionWithDuration(0.5, CCPoint(0,0)), actionMoveDone, NULL));
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_KNIFE.c_str()));
    }
    
    void Stair::doorCloseLeft(CCNode* sender) {
        CCNode* nParent = (CCNode*)this->getChildByTag(STAIRDOORPARENT_TAG);
        CCSprite* pSpriteTapa = (CCSprite*)nParent->getChildByTag(STAIRDOOR_TAG);
        CCFiniteTimeAction* rotateAction = CCEaseBounceOut::actionWithAction(CCRotateBy::actionWithDuration(0.25, -90));
        pSpriteTapa->runAction(rotateAction);
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_KNIFE.c_str()));
    }
    
    void Stair::doorOpenRight() {
        CCNode* nParent = (CCNode*)this->getChildByTag(STAIRDOORPARENT_TAG);
        CCFiniteTimeAction* rotateAction = CCEaseBounceOut::actionWithAction(CCRotateBy::actionWithDuration(0.5, -90));
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Stair::doorCloseRight));
        nParent->runAction(CCSequence::actions(rotateAction, CCMoveBy::actionWithDuration(0.5, CCPoint(0,0)), actionMoveDone, NULL));
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_KNIFE.c_str()));
    }
    
    void Stair::doorCloseRight(CCNode* sender) {
        CCNode* nParent = (CCNode*)this->getChildByTag(STAIRDOORPARENT_TAG);
        CCFiniteTimeAction* rotateAction = CCEaseBounceOut::actionWithAction(CCRotateBy::actionWithDuration(0.25, 90));
        nParent->runAction(rotateAction);
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_KNIFE.c_str()));
    }
    
}