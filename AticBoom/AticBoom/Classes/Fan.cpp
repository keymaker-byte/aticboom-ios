//
//  Fan.cpp
//  AticBoom
//
//  Created by Claudio Alvial on 24/01/2012.
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

#include "Fan.h"

namespace aticboom {
    
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    Fan::Fan(Json::Value fan, int world) : Fan::GameObject(fan, world) {
        this->tileWidth = FAN_TILES_WIDTH;
        this->tileHeight = FAN_TILES_HEIGHT;
        this->initParticles();
        this->setTilePosition();
    };
    
    Fan::~Fan() {
    };
    
    void Fan::initParticles() {
        CCParticleSystemPoint* wind = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->FAN_PARTICLE_PLIST.c_str());
        wind->setPosition(CCPoint(0,0));
        wind->setPositionType(kCCPositionTypeRelative);
        this->addChild(wind, 3, FAN_SHINE_TAG);
    }
    
}
