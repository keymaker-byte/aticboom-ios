//
//  Button.cpp
//  AticBoom
//
//  Created by Tae Sandoval Murgan on 3/27/12.
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

#include "Button.h"

namespace aticboom
{
    using namespace cocos2d;
    
    Button::Button(Json::Value button, int world) : Button::GameObject(button, world)
    {
        this->tileWidth = BUTTON_TILES_WIDTH;
        this->tileHeight = BUTTON_TILES_HEIGHT;
        this->stairIndex = button["stairIndex"].asInt();
        this->state = 0;
        this->initAnimations();
        this->setTilePosition();
    }
    
    Button::~Button()
    {
    }
    
    void Button::press()
    {
        if(this->state == 0) {
            this->state = 1;
            this->removeChildByTag(KEY_SPRITE_TAG, true);
            CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName("pw-btnoff.png");
            this->addChild(pSprite, 0, KEY_SPRITE_TAG);
        }
        else {
            this->state = 0;
            this->removeChildByTag(KEY_SPRITE_TAG, true);
            CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName("pw-btnon.png");
            this->addChild(pSprite, 0, KEY_SPRITE_TAG);    
        }
    }
    
    void Button::makeDark()
    {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(KEY_SPRITE_TAG);
        pSprite->setColor(ccc3(DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR));
    }
    
    void Button::initAnimations()
    {
        
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName("pw-btnon.png");
        this->addChild(pSprite, 0, KEY_SPRITE_TAG);
    }
}
