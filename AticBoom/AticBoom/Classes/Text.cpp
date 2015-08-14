//
//  Text.cpp
//  AticBoom
//
//  Created by Juan Rodriguez on 02/01/2012.
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

#include "Text.h"

namespace aticboom {
    
    using namespace cocos2d;
    
    Text::Text(Json::Value txt) : cocos2d::CCNode() {
        this->image = txt["image"].asInt();
        this->index = txt["index"].asInt();
        this->tileWidth = TEXT_TILES_WIDTH;
        this->tileHeight = TEXT_TILES_HEIGHT;
        this->autorelease();
        this->initSimpleSprite();
        this->setPosition(Geometry::getFloorPosition(this->index));
    };
    
    Text::~Text() {
    };
    
    void Text::initSimpleSprite() {
    }
    
}
