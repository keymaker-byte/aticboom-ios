//
//  ExtraBubble.cpp
//  AticBoom
//
//  Created by Marcelo Sanchez on 3/27/12.
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

#include "ExtraRope.h"

namespace aticboom {
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    ExtraRope::ExtraRope(Json::Value rope, int world) : ExtraRope::GameObject(rope, world){
        this->tileWidth = STAR_TILES_WIDTH;
        this->tileHeight = STAR_TILES_HEIGHT;
        this->extraTime = rope["extraTime"].asInt();
        this->initAnimations();
        this->setTilePosition();
    }
    
    ExtraRope::~ExtraRope() {
    };
    
    void ExtraRope::initAnimations() {
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName("pw-time.png");
        this->addChild(pSprite, 1, EXTRA_BUBBLE_SPRITE_TAG);
    }
    
    void ExtraRope::hide() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(EXTRA_BUBBLE_SPRITE_TAG);
        pSprite->stopAllActions();
        this->stopAllActions();
        this->runAction(CCHide::action());
    }
    
    void ExtraRope::grab() {
        this->hide();
    }
    
    void ExtraRope::makeDark(){
    }
}
