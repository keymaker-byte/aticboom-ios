//
//  Fan.h
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

#ifndef AticBoom_Fan_h
#define AticBoom_Fan_h

#include <vector>
#include <string>

#include "Config.h"
#include "Music.h"

#include "json.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "GameObject.h"

namespace aticboom {
    class Fan: public GameObject 
    {
    public:
        Fan(Json::Value fan, int world);
        ~Fan();
        
        
        
    private:
        void initParticles();
        
    };
}

#endif