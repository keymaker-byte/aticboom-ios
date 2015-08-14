//
//  Config.cpp
//  AticBoom

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

#include "Config.h"

namespace aticboom {
    
    Config::Config() {
        setLanguage();
        readFullGame();
        SCREEN_WIDTH = 320;
        SCREEN_HEIGHT = 480;
        SCREEN_WIDTH_MARGEN = 0;
        SCREEN_HEIGHT_MARGEN = 0;
        TILE_HEIGHT = 16;
        TILE_WIDTH = 16;
        PLAYER_SMOKE_HEIGHT_MARGEN = 15;
        FLOOR_HEIGHT_MARGEN = 7;
        ROPE_WIDTH_MARGEN = 12;
        HUD_TEXT_MARGEN = 64;
        HUD_BUBBLE_SEPARATOR = 15;
        HUD_STAR_SEPARATOR = 30;
        MENU_MAIN_BUTTON_MARGEN = 250;
        MENU_MAIN_BUTTON_WIDTH = 230;
        MENU_MAIN_BUTTON_HEIGHT = 33;
        MENU_MAIN_PLAY_FONT = 35;
        MENU_MAIN_ANCHOR_MARGEN = 180;
        MENU_KID_MARGEN_LEFT = 260;
        MENU_KID_MARGEN_BOTTOM = 80;
        MENU_KID_WATER_MARGIN = 7;
        MENU_KID_MOVE_VERT = 5;
        MENU_KID_MOVE_HOR = 5;
        MENU_KID_ROT = 3;
        MENU_BUTTON_FONT = 25;
        MENU_BUTTON_FONT2 = 20;
        MENU_FONT_SMALL = 17;
        MENU_BUTTON_WIDTH = 136;
        MENU_BUTTON_HEIGHT = 42;
        MINI_SCROLL_WIDTH = 150;
        MINI_SCROLL_HEIGHT = 151;
        MENU_SETTINGS_BUTTON_MARGEN = 181;
        MENU_CREDITS_TEXT_MARGEN = 24;
        COMIC_ADJUST_PAGE_A = 150;
        COMIC_ADJUST_TXT_A = 140;
        COMIC_ADJUST_PAGE_B = 170;
        COMIC_ADJUST_TXT_B = 195;
        COMIC_ADJUST_PAGE_C = 140;
        COMIC_ADJUST_TXT_C = 120;
        COMIC_ADJUST_PAGE_E = 195;
        COMIC_ADJUST_TXT_E = 110;
        COMIC_MARGIN_TXT_A = 65;
        COMIC_MARGIN_TXT_B = 60;
        COMIC_MARGIN_TXT_C = 85;
        COMIC_MARGIN_TXT_D = 65;
        COMIC_MARGIN_TXT_E = 30;
        MENU_HELP_BUTTON_MARGEN = 140;
        MENU_ABOUT_BUTTON_MARGEN = 100;
        MENU_OF_BUTTON_MARGEN_A = 25;
        MENU_OF_BUTTON_MARGEN_B = 20;
        MENU_WORLD_BUTTON_MARGEN = 220;
        MENU_WORLD_AD_MARGEN_A = 45;
        MENU_WORLD_AD_MARGEN_B = 15;
        MENU_WORLD_BUTTON_FONT = 20;
        MENU_START_WORLD_FONT = 24;
        MENU_WORLD_TEXT_MARGEN = 70;
        MENU_WORLD_WATER_MARGEN = 33;
        MENU_WORLD_ARROW_MARGEN = 17;
        MENU_WORLD_MEDAL_MARGEN = 330;
        MENU_WORLD_MEDAL_MARGEN_B = 320;
        MENU_LEVEL_TEXT_MARGEN = 35;
        MENU_LEVEL_TEXT_FONT = 23;
        MENU_WORLD_TITLE_MARGEN = 80;
        WOOD_MARGEN = 0;
        WOOD_OBJECT_MARGEN = 10;
        HEML_MARGEN = 190;
        HEML_MENU_MARGEN = 270;
        HEML_OBJECT_MARGEN = 40;
        SETTING_MENU_FIRST_ROW = 130;
        SETTING_MENU_SECOND_ROW = 200;
        SETTING_MENU_THIRD_ROW = 270;
        SETTING_MENU_FOUR_ROW = 340;
        SETTING_MARGIN_TOP = 0;
        SETTING_MARGIN_BOTTOM = 16;
        SETTING_MENU_OF_ROW = 200;
        SETTING_MENU_LEFT_ITEM = 90;
        SETTING_MENU_LEFT_ITEM2 = 70;
        SETTING_MENU_RIGHT_ITEM = 220;
        SETTING_MENU_RIGHT_ITEM2 = 200;
        SETTING_MENU_SAVE_MARGIN = 150;
        CLOUD_WIDTH = 230;
        CLOUD_POS1 = 100;
        CLOUD_POS2 = 200;
        CLOUD_POS3 = 250;
        CLOUD_POS4 = 350;
        CLOUD_POS5 = 400;
        CLOUD_RAN1 = 60;
        CLOUD_RAN2 = 35;
        WORLD_DELTA = 60;
        HINT_TOUCH_XMARGIN = 40;
        HINT_TOUCH_YMARGIN = 35;
        LEVEL_W_MARGIN_MARGIN = 190;
        KNIFE_MARGINX = 130;
        KNIFE_MARGINY = 85;
        FONT_SCALE = 1;
        SHADOW_TEXT = 2;
        BUBLE_PARTICLE_EXPLODE = "pop.plist";
        FLOOR_PARTICLE_FIRE = "floorfire.plist";
        FLOOR_PARTICLE_WIND = "wind.plist";
        FLOOR_PARTICLE_WINDLEVEL = "windlevel.plist";
        PLAYER_PARTICLE_SMOKE = "smoke.plist";
        PLAYER_PARTICLE_EXPLODE = "explode.plist";
        PLAYER_PARTICLE_EXPLODESMOKE = "explode-smoke.plist";
        PLAYER_PARTICLE_FIREWORKS = "fireworks.plist";
        SHIP_PARTICLE_EXPLODE = "shipexplode.plist";
        ROPE_PARTICLE_FIRE = "fire.plist";
        PARTICLE_SHINE = "shine.plist";
        WORLD_BURNING_PARTICLE = "burning.plist";
        FAN_PARTICLE_PLIST = "fan.plist";
        WATER_PARTICLE = "waterpart.plist";
        MENU_PNG = "mainmenu.png";
        MENU_PLIST = "mainmenu.plist";
        ANIMATIONS_PNG = "animations.png";
        ANIMATIONS_PLIST = "animations.plist";
        COMIC_PNG = "comic.png";
        COMIC_PLIST = "comic.plist";
        BLACK_PNG = "black.png";
        BLACK_PLIST = "black.plist";
        HELP_PLIST = "hints.plist";
        HELP_PNG = "hints.png";
        HELPHIATORY_PLIST = "help.plist";
        HELPHIATORY_PNG = "help.png";
        LOADING_PNG = "loading.png";
        LOADING_PLIST = "loading.plist";
        W_PNG = "w%d.png";
        W_PLIST = "w%d.plist";
        HUD_PNG = "hud.png";
        HUD_PLIST = "hud.plist";
        BMFONT_NAME = "PiecesofEight.fnt";
        CONFETI_PARTICLE = "confeti.plist";
        INTRO_PNG = "gff.png";
        INTRO_PNG2 = "gff2.png";
        POWERUPS_PNG = "powerups.png";
        POWERUPS_PLIST = "powerups.plist";
    }
    
    static Config *s_config;
    
    Config* Config::sharedConfig() {
        if (! s_config)
        {
            s_config = new Config();
        }
        return s_config;
    }
    
    void Config::iPadFix() {
        SCREEN_WIDTH = 640;
        SCREEN_HEIGHT = 960;
        SCREEN_WIDTH_MARGEN = 64;
        SCREEN_HEIGHT_MARGEN = 64;
        TILE_HEIGHT = 32;
        TILE_WIDTH = 32;
        PLAYER_SMOKE_HEIGHT_MARGEN = 15  * 2;
        FLOOR_HEIGHT_MARGEN = 7 * 2;
        ROPE_WIDTH_MARGEN = 12 * 2;
        HUD_TEXT_MARGEN = 64 * 2;
        HUD_BUBBLE_SEPARATOR = 15 * 2;
        HUD_STAR_SEPARATOR = 30 * 2;
        MENU_MAIN_BUTTON_MARGEN = 250 * 2;
        MENU_MAIN_BUTTON_WIDTH = 230 * 2;
        MENU_MAIN_BUTTON_HEIGHT = 33 * 2;
        MENU_MAIN_PLAY_FONT = 35 * 2;
        MENU_MAIN_ANCHOR_MARGEN = 180 * 2;
        MENU_KID_MARGEN_LEFT = 260 * 2;
        MENU_KID_MARGEN_BOTTOM = 80 * 2;
        MENU_KID_WATER_MARGIN = 7 * 2;
        MENU_KID_MOVE_VERT = 5 * 2;
        MENU_KID_MOVE_HOR = 5 * 2;
        MENU_KID_ROT = 3 * 2;
        MENU_BUTTON_FONT = 25 * 2;
        MENU_BUTTON_FONT2 = 20 * 2;
        MENU_FONT_SMALL = 17 * 2;
        MENU_BUTTON_WIDTH = 136 * 2;
        MENU_BUTTON_HEIGHT = 42 * 2;
        MINI_SCROLL_WIDTH = 150 * 2;
        MINI_SCROLL_HEIGHT = 151 * 2;
        MENU_SETTINGS_BUTTON_MARGEN = 180 * 2;
        MENU_CREDITS_TEXT_MARGEN = 27 * 2;
        COMIC_ADJUST_PAGE_A = 150 * 2;
        COMIC_ADJUST_TXT_A = 140 * 2;
        COMIC_ADJUST_PAGE_B = 170 * 2;
        COMIC_ADJUST_TXT_B = 195 * 2;
        COMIC_ADJUST_PAGE_C = 140 * 2;
        COMIC_ADJUST_TXT_C = 120 * 2;
        COMIC_ADJUST_PAGE_E = 195 * 2;
        COMIC_ADJUST_TXT_E = 110 * 2;
        COMIC_MARGIN_TXT_A = 65 * 2;
        COMIC_MARGIN_TXT_B = 60 * 2;
        COMIC_MARGIN_TXT_C = 85 * 2;
        COMIC_MARGIN_TXT_D = 65 * 2;
        COMIC_MARGIN_TXT_E = 30 * 2;
        MENU_HELP_BUTTON_MARGEN = 140 * 2;
        MENU_ABOUT_BUTTON_MARGEN = 100 * 2;
        MENU_OF_BUTTON_MARGEN_A = 25 * 2;
        MENU_OF_BUTTON_MARGEN_B = 20 * 2;
        MENU_WORLD_BUTTON_MARGEN = 220 * 2;
        MENU_WORLD_AD_MARGEN_A = 45 * 2;
        MENU_WORLD_AD_MARGEN_B = 15 * 2;
        MENU_WORLD_BUTTON_FONT = 20 * 2;
        MENU_START_WORLD_FONT = 24 * 2;
        MENU_WORLD_TEXT_MARGEN = 70 * 2;
        MENU_WORLD_WATER_MARGEN = 33 * 2;
        MENU_WORLD_ARROW_MARGEN = 17 * 2;
        MENU_WORLD_MEDAL_MARGEN = 330 * 2;
        MENU_WORLD_MEDAL_MARGEN_B = 320 * 2;
        MENU_LEVEL_TEXT_MARGEN = 35 * 2;
        MENU_LEVEL_TEXT_FONT = 23 * 2;
        MENU_WORLD_TITLE_MARGEN = 80 * 2;
        WOOD_MARGEN = 0 * 2;
        WOOD_OBJECT_MARGEN = 10 * 2;
        HEML_MARGEN = 190 * 2;
        HEML_MENU_MARGEN = 270 * 2;
        HEML_OBJECT_MARGEN = 40 * 2;
        SETTING_MENU_FIRST_ROW = 130 * 2;
        SETTING_MENU_SECOND_ROW = 200 * 2;
        SETTING_MENU_THIRD_ROW = 270 * 2;
        SETTING_MENU_FOUR_ROW = 340 * 2;
        SETTING_MARGIN_TOP = 0;
        SETTING_MARGIN_BOTTOM = 32;
        SETTING_MENU_OF_ROW = 200 * 2;
        SETTING_MENU_LEFT_ITEM = 90 * 2;
        SETTING_MENU_LEFT_ITEM2 = 70 * 2;
        SETTING_MENU_RIGHT_ITEM = 220 * 2;
        SETTING_MENU_RIGHT_ITEM2 = 200 * 2;
        SETTING_MENU_SAVE_MARGIN = 150 * 2;
        CLOUD_WIDTH = 230 * 2;
        CLOUD_POS1 = 100 * 2;
        CLOUD_POS2 = 200 * 2;
        CLOUD_POS3 = 250 * 2;
        CLOUD_POS4 = 350 * 2;
        CLOUD_POS5 = 400 * 2;
        CLOUD_RAN1 = 60 * 2;
        CLOUD_RAN2 = 35 * 2;
        WORLD_DELTA = 250;
        HINT_TOUCH_XMARGIN = 40 * 2;
        HINT_TOUCH_YMARGIN = 35 * 2;
        LEVEL_W_MARGIN_MARGIN = 190 * 2;
        KNIFE_MARGINX = 130 * 2;
        KNIFE_MARGINY = 85 * 2;
        FONT_SCALE = 1;
        SHADOW_TEXT = 2;
        BUBLE_PARTICLE_EXPLODE = "pop-ipad.plist";
        FLOOR_PARTICLE_FIRE = "floorfire-ipad.plist";
        FLOOR_PARTICLE_WIND = "wind-ipad.plist";
        FLOOR_PARTICLE_WINDLEVEL = "windlevel-ipad.plist";
        PLAYER_PARTICLE_SMOKE = "smoke-ipad.plist";
        PLAYER_PARTICLE_EXPLODE = "explode-ipad.plist";
        PLAYER_PARTICLE_EXPLODESMOKE = "explode-smoke-ipad.plist";
        PLAYER_PARTICLE_FIREWORKS = "fireworks-ipad.plist";
        ROPE_PARTICLE_FIRE = "fire-ipad.plist";
        PARTICLE_SHINE = "shine-ipad.plist";
        WORLD_BURNING_PARTICLE = "burning-ipad.plist";
        FAN_PARTICLE_PLIST = "fan-ipad.plist";
        WATER_PARTICLE = "waterpart-ipad.plist";
        MENU_PNG = "mainmenu-hd.png";
        MENU_PLIST = "mainmenu-hd.plist";
        ANIMATIONS_PNG = "animations-hd.png";
        ANIMATIONS_PLIST = "animations-hd.plist";
        COMIC_PNG = "comic-hd.png";
        COMIC_PLIST = "comic-hd.plist";
        BLACK_PNG = "black-hd.png";
        BLACK_PLIST = "black-hd.plist";
        HELP_PLIST = "hints-hd.plist";
        HELP_PNG = "hints-hd.png";
        HELPHIATORY_PLIST = "help-hd.plist";
        HELPHIATORY_PNG = "help-hd.png";
        LOADING_PNG = "loading-hd.png";
        LOADING_PLIST = "loading-hd.plist";
        W_PNG = "w%d-hd.png";
        W_PLIST = "w%d-hd.plist";
        HUD_PNG = "hud-hd.png";
        HUD_PLIST = "hud-hd.plist";
        BMFONT_NAME = "PiecesofEight-hd.fnt";
        CONFETI_PARTICLE = "confeti-ipad.plist";
        INTRO_PNG = "gff-hd.png";
        INTRO_PNG2 = "gff2-hd.png";
        POWERUPS_PNG = "powerups-hd.png";
        POWERUPS_PLIST = "powerups-hd.plist";
    }
    
    void Config::readFullGame() {
        char fileName [1024];
        sprintf (fileName, SETTINGS_JSON.c_str(), cocos2d::CCFileUtils::getWriteablePath().c_str());
        Json::Value root;
        unsigned long bufferSize = 0;
        unsigned char * uc =  cocos2d::CCFileUtils::getFileData(fileName,"a+", &bufferSize);
        if(bufferSize > 0) {
            char * ca = (char *) uc;
            string buffer = string(ca);
            Json::Reader reader;
            reader.parse(buffer.c_str(), root);
        }
        else {
            string fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(INITSETTINGS_JSON.c_str());
            
            unsigned long bufferSizeI = 0;
            unsigned char * dataI =  cocos2d::CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
            char * ca = (char *) dataI;
            string buffer = string(ca);
            Json::Reader reader;
            reader.parse(buffer.c_str(), root);
            
            delete dataI;
        }
        delete uc;
        TOTAL_WORLDS = 6;
    }
    
    void Config::writeFullGame() {
        char fileName [1024];
        sprintf (fileName, SETTINGS_JSON.c_str(), cocos2d::CCFileUtils::getWriteablePath().c_str());
        Json::Value root;
        unsigned long bufferSize = 0;
        unsigned char * uc =  cocos2d::CCFileUtils::getFileData(fileName,"a+", &bufferSize);
        if(bufferSize > 0) {
            char * ca = (char *) uc;
            string buffer = string(ca);
            Json::Reader reader;
            reader.parse(buffer.c_str(), root);
        }
        else {
            string fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(INITSETTINGS_JSON.c_str());
            
            unsigned long bufferSizeI = 0;
            unsigned char * dataI =  cocos2d::CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
            char * ca = (char *) dataI;
            string buffer = string(ca);
            Json::Reader reader;
            reader.parse(buffer.c_str(), root);
            
            delete dataI;
        }
        delete uc;
        Json::StyledWriter writer;
        std::string outputString = writer.write(root);
        TOTAL_WORLDS = 6;
        ofstream file;
        file.open(fileName);
        file << outputString;
        file.close();
    }
    
    void Config::writeLevelsGame() {
        char fileName [1024];
        sprintf (fileName, SETTINGS_JSON.c_str(), cocos2d::CCFileUtils::getWriteablePath().c_str());
        Json::Value root;
        unsigned long bufferSize = 0;
        unsigned char * uc =  cocos2d::CCFileUtils::getFileData(fileName,"a+", &bufferSize);
        if(bufferSize > 0) {
            char * ca = (char *) uc;
            string buffer = string(ca);
            Json::Reader reader;
            reader.parse(buffer.c_str(), root);
        }
        else {
            string fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(INITSETTINGS_JSON.c_str());
            
            unsigned long bufferSizeI = 0;
            unsigned char * dataI =  cocos2d::CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
            char * ca = (char *) dataI;
            string buffer = string(ca);
            Json::Reader reader;
            reader.parse(buffer.c_str(), root);
            
            delete dataI;
        }
        delete uc;
        Json::StyledWriter writer;
        std::string outputString = writer.write(root);
        ofstream file;
        file.open(fileName);
        file << outputString;
        file.close();
    }
    
    void Config::setLanguage() {
        cocos2d::ccLanguageType lang = cocos2d::CCApplication::getCurrentLanguage();
        string fullPath;
        if (lang == cocos2d::kLanguageSpanish) {
            LANG = "es";
            fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(LANG_ES.c_str());
        }
        else if (lang == cocos2d::kLanguagePortugues) {
            LANG = "pt";
            fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(LANG_PT.c_str());
        }
        else if (lang == cocos2d::kLanguageGerman) {
            LANG = "de";
            fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(LANG_DE.c_str());
        }
        else if (lang == cocos2d::kLanguageFrench) {
            LANG = "fr";
            fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(LANG_FR.c_str());
        }
        else if (lang == cocos2d::kLanguageItalian) {
            LANG = "it";
            fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(LANG_IT.c_str());
        }
        else if (lang == cocos2d::kLanguageKorean) {
            LANG = "ko";
            fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(LANG_KO.c_str());
        }
        else if (lang == cocos2d::kLanguageChinese) {
            LANG = "zh";
            fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(LANG_ZH.c_str());
        }
        else {
            LANG = "en";
            fullPath = cocos2d::CCFileUtils::fullPathFromRelativePath(LANG_EN.c_str());
        }
        CCLOG(fullPath.c_str());
        Json::Value root;
        unsigned long bufferSizeI = 0;
        unsigned char * dataI =  cocos2d::CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
        char * ca = (char *) dataI;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), root);
        delete dataI;
        LANG_SOON = root["soon"].asString();
        LANG_AGAIN = root["again"].asString();
        LANG_BESTSCORE = root["bestScore"].asString();
        LANG_CONTINUE = root["continue"].asString();
        LANG_CREDITS = root["credits"].asString();
        LANG_DEVELOPERS = root["developers"].asString();
        LANG_FXOFF = root["fxOff"].asString();
        LANG_FXON = root["fxOn"].asString();
        LANG_HELP = root["help"].asString();
        LANG_LEVELDESCRIPTION = root["levelDescription"].asString();
        LANG_LEVELDESCRIPTION2 = root["levelDescription2"].asString();
        LANG_LEVELDESCRIPTION2PLURAL = root["levelDescription2Plural"].asString();
        LANG_LEVELDESCRIPTION3 = root["levelDescription3"].asString();
        LANG_GHOSTLEVELDESCRIPTION = root["ghostLevelDescription"].asString();
        LANG_MENU = root["menu"].asString();
        LANG_MORESKULLS = root["moreSkulls"].asString();
        LANG_MUSICOFF = root["musicOff"].asString();
        LANG_MUSICON = root["musicOn"].asString();
        LANG_NEXT = root["next"].asString();
        LANG_NO = root["no"].asString();
        LANG_PLAY = root["play"].asString();
        LANG_RESET = root["reset"].asString();
        LANG_SCORE = root["score"].asString();
        LANG_SETTINGS = root["settings"].asString();
        LANG_RESUME = root["resume"].asString();
        LANG_SURE = root["sure"].asString();
        LANG_YES = root["yes"].asString();
        LANG_COMIC_TEXT_1 = root["comictxt1"].asString();
        LANG_COMIC_TEXT_2 = root["comictxt2"].asString();
        LANG_COMIC_TEXT_3 = root["comictxt3"].asString();
        LANG_COMIC_TEXT_4 = root["comictxt4"].asString();
        LANG_COMIC_TEXT_5 = root["comictxt5"].asString();
        LANG_UNLOCK = root["unlock"].asString();
        LANG_STORE = root["store"].asString();
        LANG_HINT_1 = root["hint-1"].asString();
        LANG_HINT_2 = root["hint-2"].asString();
        LANG_HINT_3 = root["hint-3"].asString();
        LANG_HINT_4 = root["hint-4"].asString();
        LANG_HINT_5 = root["hint-5"].asString();
        LANG_HINT_6 = root["hint-6"].asString();
        LANG_HINT_7 = root["hint-7"].asString();
        LANG_HINT_8 = root["hint-8"].asString();
        LANG_HINT_9 = root["hint-9"].asString();
        LANG_HINT_10 = root["hint-10"].asString();
        LANG_HINT_11 = root["hint-11"].asString();
        LANG_HINT_12 = root["hint-12"].asString();
        LANG_HINT_13 = root["hint-13"].asString();
        LANG_HINT_14 = root["hint-14"].asString();
        LANG_HINT_15 = root["hint-15"].asString();
        LANG_HINT_16 = root["hint-16"].asString();
        LANG_HINT_17 = root["hint-17"].asString();
        LANG_RESTORE = root["restore"].asString();
    }
    
};