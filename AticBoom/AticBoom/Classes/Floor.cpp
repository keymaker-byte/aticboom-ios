//
//  Floor.cpp
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

#include "Floor.h"

namespace aticboom {
    using namespace cocos2d;
    
    Floor::Floor(Json::Value floor, int world) : cocos2d::CCNode() {
        this->name = floor["name"].asString();
        this->image = floor["image"].asInt();
        this->index = floor["index"].asInt();
        this->resLeft = floor["resleft"].asDouble();
        this->resRight = floor["resright"].asDouble();
        this->type = floor["type"].asInt();
        this->dark = floor["dark"].asInt();
        this->world = world;
        this->autorelease();
        this->initSimpleSprite();
        this->setPosition(Geometry::getFloorPosition(this->index));
    };
    
    Floor::~Floor() {
    };
    
    void Floor::initSimpleSprite() {
        char buffer [30];
        bool night = Geometry::isNight(this->world);
        sprintf (buffer, FLOOR_PNG.c_str(),this->image);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        this->addChild(pSprite, 2);
        if (this->dark == 1) {
            pSprite->setColor(ccc3(DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR, DARK_COLOR_CORRECTOR_B));
        }
        else if(night) {
            pSprite->setColor(ccc3(NIGHT_COLOR_CORRECTOR_R, NIGHT_COLOR_CORRECTOR_G, NIGHT_COLOR_CORRECTOR_B));
        }
        if(this->resLeft < 1) {
            CCParticleSystemPoint* wind = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->FLOOR_PARTICLE_WINDLEVEL.c_str());
            wind->setPosition( CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, 0) );
            wind->setPositionType(kCCPositionTypeRelative);
            this->addChild(wind, 3, FLOOR_WIND_TAG);
        }
        if(this->resRight < 1) {
            CCParticleSystemPoint* wind = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->FLOOR_PARTICLE_WINDLEVEL.c_str());
            wind->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH/2 - Config::sharedConfig()->SCREEN_WIDTH_MARGEN, 0) );
            wind->setAngle(360);
            wind->setPositionType(kCCPositionTypeRelative);
            this->addChild(wind, 3, FLOOR_WIND_TAG);
        }
        if(this->image >= 4) {
            sprintf (buffer, FLOOR_BACK_PNG.c_str(), this->world);
            CCSprite* backSprite = CCSprite::spriteWithSpriteFrameName(buffer);
            if(night) {
                backSprite->setColor(ccc3(NIGHT_COLOR_CORRECTOR_R, NIGHT_COLOR_CORRECTOR_G, NIGHT_COLOR_CORRECTOR_B));
            }
            this->addChild(backSprite, 0);
        }
        if(this->image == 5) {
            sprintf (buffer, FLOOR_SUPER_PNG.c_str(), this->world);
            CCSprite* mastSprite = CCSprite::spriteWithSpriteFrameName(buffer);
            mastSprite->setPosition(CCPoint(0, FLOORS_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT * 2 - 1));
            if(night) {
                mastSprite->setColor(ccc3(NIGHT_COLOR_CORRECTOR_R, NIGHT_COLOR_CORRECTOR_G, NIGHT_COLOR_CORRECTOR_B));
            }
            this->addChild(mastSprite, 2);
            sprintf (buffer, FLOOR_SUPER_BACK_PNG.c_str(), this->world);
            CCSprite* mastbackSprite = CCSprite::spriteWithSpriteFrameName(buffer);
            mastbackSprite->setPosition(CCPoint(0, FLOORS_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT * 2 - 1));
            if(night) {
                mastbackSprite->setColor(ccc3(NIGHT_COLOR_CORRECTOR_R, NIGHT_COLOR_CORRECTOR_G, NIGHT_COLOR_CORRECTOR_B));
            }
            this->addChild(mastbackSprite, 0);
            CCParticleSystemPoint* wind = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->FLOOR_PARTICLE_WIND.c_str());
            wind->setPosition( CCPoint(FLOORS_TILES_WIDTH * Config::sharedConfig()->TILE_WIDTH /2, Config::sharedConfig()->TILE_HEIGHT * FLOORS_TILES_HEIGHT) );
            this->addChild(wind, 1);
        }
    }
    
    void Floor::open() {
        if(this->type == FLOOR_TYPE_CLOSE) {
            Level* level = (Level *)this->getParent();
            CCParticleSystemPoint* fire = (CCParticleSystemPoint*)level->getChildByTag(FIRE_TAG + this->index);
            fire->stopSystem();
            this->type =  FLOOR_TYPE_OPEN;
        }
    }
    
}