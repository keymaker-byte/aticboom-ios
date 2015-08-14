//
//  Music.h
//  AticBoom
//
//  Created by Juan Rodriguez on 06/01/2012.
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

#ifndef AticBoom_Audio_h
#define AticBoom_Audio_h

#include "SimpleAudioEngine.h"

namespace aticboom {
    
    static string SOUND_FORMAT = ".mp3";
    static string SOUND_BUBBLE = std::string("bubble").append(SOUND_FORMAT);
    static string SOUND_POP = std::string("pop").append(SOUND_FORMAT);
    static string SOUND_UP = std::string("up").append(SOUND_FORMAT);
    static string SOUND_KEY = std::string("key").append(SOUND_FORMAT);
    static string SOUND_BOMB = std::string("bomb").append(SOUND_FORMAT);
    static string SOUND_FALL = std::string("fall").append(SOUND_FORMAT);
    static string SOUND_STAR = std::string("star").append(SOUND_FORMAT);
    static string SOUND_FAN = std::string("fan").append(SOUND_FORMAT);
    static string SOUND_SPLASH = std::string("splash").append(SOUND_FORMAT);
    static string SOUND_LOGO = std::string("logo").append(SOUND_FORMAT);
    static string SOUND_PAPER1 = std::string("paper1").append(SOUND_FORMAT);
    static string SOUND_PAPER2 = std::string("paper2").append(SOUND_FORMAT);
    static string SOUND_PAPER3 = std::string("paper3").append(SOUND_FORMAT);
    static string SOUND_SCREEN = std::string("screen").append(SOUND_FORMAT);
    static string SOUND_KNIFE = std::string("paso2").append(SOUND_FORMAT);
    static string SOUND_CELEBRATION1 = std::string("celebration2").append(SOUND_FORMAT);
    static string SOUND_CELEBRATION2 = std::string("celebration1").append(SOUND_FORMAT);
    static string MUSIC_MENU = std::string("music1").append(SOUND_FORMAT);
    static string MUSIC_LEVEL1 = std::string("music2").append(SOUND_FORMAT);
    static string MUSIC_LEVEL2 = std::string("music3").append(SOUND_FORMAT);
    
}

#endif
