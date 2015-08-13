//
//  GameObject.cpp
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

#include "GameObject.h"

namespace aticboom {
    
    using namespace cocos2d;
    
    GameObject::GameObject(Json::Value gameObject, int world) : cocos2d::CCNode() {
        this->position[0] = gameObject["position"]["x"].asInt();
        this->position[1] = gameObject["position"]["y"].asInt() * FLOORS_TILES_HEIGHT;
        this->world = world;
        this->autorelease();
    };
    
    GameObject::~GameObject() {
        
    };
    
    void GameObject::setTilePosition() {
        this->setPosition(Geometry::getTilePosition(this->position[0], this->position[1], this->tileWidth, this->tileHeight));
    }
    
    void GameObject::runAnimationAction(CCAction *action) {
        
    }
    
    void GameObject::runMovingAction(CCAction *action) {
        
    }
    
    void GameObject::hide() {
        
    }

}