//
//  Hole.cpp
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

#include "Hole.h"

namespace aticboom {
    
    using namespace cocos2d;
    
    Hole::Hole(Json::Value hole, int world) : Hole::GameObject(hole, world) {
        this->tileWidth = HOLE_TILES_WIDTH;
        this->tileHeight = HOLE_TILES_HEIGHT;
        this->initAnimations();
        this->setTilePosition();
    };
    
    Hole::~Hole() {
    };
    
    void Hole::initAnimations() {
        char buffer [50];
        bool night = Geometry::isNight(this->world);
        sprintf (buffer, HOLE_PNG.c_str(), this->world);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        if(night) {
            pSprite->setColor(ccc3(NIGHT_COLOR_CORRECTOR_R, NIGHT_COLOR_CORRECTOR_G, NIGHT_COLOR_CORRECTOR_B));
        }
        this->addChild(pSprite, 0, HOLE_SPRITE_TAG);
    }
    
    void Hole::runAnimationAction(CCAction* action) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(HOLE_SPRITE_TAG);
        pSprite->runAction(action);
    }
    
    void Hole::runMovingAction(CCAction* action){
        this->runAction(action);
    }
    
    void Hole::hide() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(HOLE_SPRITE_TAG);
        pSprite->stopAllActions();
        this->stopAllActions();
        this->runAction(CCHide::action());
    }
    
    void Hole::makeDark() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(HOLE_SPRITE_TAG);
        pSprite->setColor(ccc3(DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR));
    }
    
}