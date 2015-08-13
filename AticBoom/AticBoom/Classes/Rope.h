//
//  Rope.h
//  AticBoom
//
//  Created by Claudio Alvial on 1/5/12.
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

#ifndef AticBoom_Rope_h
#define AticBoom_Rope_h

#include <vector>
#include <string>

#include "Config.h"
#include "Music.h"

#include "json.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
//#include "CDAudioManager.h"

#include "Geometry.h"

namespace aticboom {
    class Rope : public cocos2d::CCNode {
    public:
        Rope(int burningTime);
        ~Rope();
        
        int burningTime;
        
        void stopRope();
        void pauseRope();
        void resumeRope();
        void explode();
        void addRope(int extraTime);
        
        void pauseAudio(bool pause);
        
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_ROPE_BURN;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_ROPE_STAY;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_EXTRA_ROPE_BURN;
        cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >* ANIMATION_EXTRA_ROPE_STAY;
    
    private:
        void initAnimations();
    };
}


#endif
