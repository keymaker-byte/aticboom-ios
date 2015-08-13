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

#include "AticBoomObjC.h"
#include "Export.h"
#include <stddef.h>
#include <string>
#include "RootViewController.h"
#include "cocos2d.h"
#import <AudioToolbox/AudioToolbox.h>

static NSMutableArray *pendingAchievements = [[NSMutableArray alloc] init];
static NSMutableArray *pendingScores = [[NSMutableArray alloc] init];

static void static_vibrate()
{
    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
}

namespace aticboom
{
	static AticBoomObjC *s_obj;
    
	AticBoomObjC::AticBoomObjC()
	{
        
	}
    
	AticBoomObjC::~AticBoomObjC()
	{
        
	}
    
	AticBoomObjC* AticBoomObjC::shared()
	{
		if (! s_obj)
		{
			s_obj = new AticBoomObjC();
		}
		return s_obj;
	}
    
    void AticBoomObjC::vibrate()
    {
        static_vibrate();
    }
    
    
    long AticBoomObjC::memory()
	{
        return -1;
	}
    
}