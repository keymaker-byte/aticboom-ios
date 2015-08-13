//
//  Wall.cpp
//  AticBoom
//
//  Created by Claudio Alvial on 1/27/12.
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

#include "Wall.h"

namespace aticboom {
    
    using namespace cocos2d;
    
    Wall::Wall(Json::Value wall, int world) : Wall::GameObject(wall, world){
        this->tileWidth = 4;
        this->tileHeight = 7;
        this->initSimpleSprite();
        this->setTilePosition();
    };
    
    Wall::~Wall() {
        
    };
    
    void Wall::initSimpleSprite() {
        char buffer [50];
        
        bool night = Geometry::isNight(this->world);
        
        sprintf (buffer, WALL_PNG.c_str(), this->world);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        if(night) {
            pSprite->setColor(ccc3(NIGHT_COLOR_CORRECTOR_R, NIGHT_COLOR_CORRECTOR_G, NIGHT_COLOR_CORRECTOR_B));
        }
        this->addChild(pSprite, 0, WALL_SPRITE_TAG);
    }
    
    void Wall::makeDark() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(WALL_SPRITE_TAG);
        pSprite->setColor(ccc3(DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR));
    }

}