//
//  GameObject.h
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

#ifndef AticBoom_GameObject_h
#define AticBoom_GameObject_h

#include <vector>
#include <string>
#include "Config.h"
#include "json.h"
#include "cocos2d.h"
#include "Geometry.h"

namespace aticboom {
    
    class GameObject : public cocos2d::CCNode {
        
    public:
        GameObject(Json::Value gameObject, int world);
        ~GameObject();
        
        int position[2];
        int tileHeight;
        int tileWidth;
        int world;
        
        void setTilePosition();
        virtual void runAnimationAction(cocos2d::CCAction* action);
        virtual void runMovingAction(cocos2d::CCAction* action);
        virtual void hide();
        
    };
    
}

#endif
