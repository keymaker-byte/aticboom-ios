//
//  Config.h
//  AticBoom
//
//  Created by Juan Rodriguez on 22/12/2011.
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

#ifndef AticBoom_Config_h
#define AticBoom_Config_h

#include "cocos2d.h"
#include "json.h"
#include <fstream>

using namespace std;

namespace aticboom {

    class Config {
    public:
        
        static Config* sharedConfig();
        
        void iPadFix();

        void writeFullGame();
        void writeLevelsGame();
        
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        int SCREEN_WIDTH_MARGEN;
        int SCREEN_HEIGHT_MARGEN;
        int TILE_HEIGHT;
        int TILE_WIDTH;
        
        int PLAYER_SMOKE_HEIGHT_MARGEN;
        int FLOOR_HEIGHT_MARGEN;
        int ROPE_WIDTH_MARGEN;
        int HUD_TEXT_MARGEN;
        int HUD_BUBBLE_SEPARATOR;
        int HUD_STAR_SEPARATOR;
        int MENU_MAIN_BUTTON_MARGEN;
        int MENU_MAIN_BUTTON_WIDTH;
        int MENU_MAIN_BUTTON_HEIGHT;
        int MENU_MAIN_PLAY_FONT;
        int MENU_MAIN_ANCHOR_MARGEN;
        int MENU_KID_MARGEN_LEFT;
        int MENU_KID_MARGEN_BOTTOM;
        int MENU_KID_WATER_MARGIN;
        int MENU_KID_MOVE_VERT;
        int MENU_KID_MOVE_HOR;
        int MENU_KID_ROT;
        int MENU_BUTTON_FONT;
        int MENU_BUTTON_FONT2;
        int MENU_FONT_SMALL;
        int MENU_BUTTON_WIDTH;
        int MENU_BUTTON_HEIGHT;
        int MINI_SCROLL_WIDTH;
        int MINI_SCROLL_HEIGHT;
        int MENU_SETTINGS_BUTTON_MARGEN;
        int MENU_CREDITS_TEXT_MARGEN;
        int COMIC_ADJUST_PAGE_A;
        int COMIC_ADJUST_TXT_A;
        int COMIC_ADJUST_PAGE_B;
        int COMIC_ADJUST_TXT_B;
        int COMIC_ADJUST_PAGE_C;
        int COMIC_ADJUST_TXT_C;
        int COMIC_ADJUST_PAGE_E;
        int COMIC_ADJUST_TXT_E;
        int COMIC_MARGIN_TXT_A;
        int COMIC_MARGIN_TXT_B;
        int COMIC_MARGIN_TXT_C;
        int COMIC_MARGIN_TXT_D;
        int COMIC_MARGIN_TXT_E;
        
        int MENU_HELP_BUTTON_MARGEN;
        int MENU_ABOUT_BUTTON_MARGEN;
        int MENU_OF_BUTTON_MARGEN_A;
        int MENU_OF_BUTTON_MARGEN_B;
        int MENU_WORLD_BUTTON_MARGEN;
        int MENU_WORLD_AD_MARGEN_A;
        int MENU_WORLD_AD_MARGEN_B;
        int MENU_WORLD_BUTTON_FONT;
        int MENU_START_WORLD_FONT;
        int MENU_WORLD_TEXT_MARGEN;
        int MENU_WORLD_WATER_MARGEN;
        int MENU_WORLD_ARROW_MARGEN;
        int MENU_WORLD_MEDAL_MARGEN;
        int MENU_WORLD_MEDAL_MARGEN_B;
        int MENU_LEVEL_TEXT_MARGEN;
        int MENU_LEVEL_TEXT_FONT;
        int MENU_WORLD_TITLE_MARGEN;
        int WOOD_MARGEN;
        int WOOD_OBJECT_MARGEN;
        int HEML_MARGEN;
        int HEML_MENU_MARGEN;
        int HEML_OBJECT_MARGEN;
        int SETTING_MENU_FIRST_ROW;
        int SETTING_MENU_SECOND_ROW;
        int SETTING_MENU_THIRD_ROW;
        int SETTING_MENU_FOUR_ROW;
        int SETTING_MARGIN_TOP;
        int SETTING_MARGIN_BOTTOM;
        int SETTING_MENU_OF_ROW;
        int SETTING_MENU_LEFT_ITEM;
        int SETTING_MENU_LEFT_ITEM2;
        int SETTING_MENU_RIGHT_ITEM;
        int SETTING_MENU_RIGHT_ITEM2;
        int SETTING_MENU_SAVE_MARGIN;
        int CLOUD_WIDTH;
        int CLOUD_POS1;
        int CLOUD_POS2;
        int CLOUD_POS3;
        int CLOUD_POS4;
        int CLOUD_POS5;
        int CLOUD_RAN1;
        int CLOUD_RAN2;
        int WORLD_DELTA;
        int HINT_TOUCH_XMARGIN;
        int HINT_TOUCH_YMARGIN;
        int LEVEL_W_MARGIN_MARGIN;
        int KNIFE_MARGINX;
        int KNIFE_MARGINY;
        float FONT_SCALE;
        int SHADOW_TEXT;
        
        string BUBLE_PARTICLE_EXPLODE;
        string FLOOR_PARTICLE_FIRE;
        string FLOOR_PARTICLE_WIND;
        string FLOOR_PARTICLE_WINDLEVEL;
        string PLAYER_PARTICLE_SMOKE;
        string PLAYER_PARTICLE_EXPLODE;
        string PLAYER_PARTICLE_EXPLODESMOKE;
        string PLAYER_PARTICLE_FIREWORKS;
        string SHIP_PARTICLE_EXPLODE;
        string ROPE_PARTICLE_FIRE;
        string PARTICLE_SHINE;
        string WORLD_BURNING_PARTICLE; 
        string FAN_PARTICLE_PLIST;
        string WATER_PARTICLE;
        string MENU_PNG;
        string MENU_PLIST;
        string ANIMATIONS_PNG;
        string ANIMATIONS_PLIST;
        string COMIC_PNG;
        string COMIC_PLIST;
        string BLACK_PNG;
        string BLACK_PLIST;
        string HELP_PLIST;
        string HELP_PNG;
        string HELPHIATORY_PLIST;
        string HELPHIATORY_PNG;
        string LOADING_PNG;
        string LOADING_PLIST;
        string W_PNG;
        string W_PLIST;
        string HUD_PNG;
        string HUD_PLIST;
        string BMFONT_NAME;
        string CONFETI_PARTICLE;
        
        string LANG;
        string LANG_AGAIN;
        string LANG_BESTSCORE;
        string LANG_CONTINUE;
        string LANG_CREDITS;
        string LANG_DEVELOPERS;
        string LANG_LEVELDESCRIPTION;
        string LANG_LEVELDESCRIPTION2;
        string LANG_LEVELDESCRIPTION2PLURAL;
        string LANG_LEVELDESCRIPTION3;
        string LANG_GHOSTLEVELDESCRIPTION;
        string LANG_PLAY;
        string LANG_SETTINGS;
        string LANG_HELP;
        string LANG_MENU;
        string LANG_MUSICON;
        string LANG_MUSICOFF;
        string LANG_NEXT;
        string LANG_FXON;
        string LANG_FXOFF;
        string LANG_RESET;
        string LANG_YES;
        string LANG_NO;
        string LANG_SURE;
        string LANG_MORESKULLS;
        string LANG_RESUME;
        string LANG_SCORE;
        string LANG_SOON;
        string LANG_COMIC_TEXT_1;
        string LANG_COMIC_TEXT_2;
        string LANG_COMIC_TEXT_3;
        string LANG_COMIC_TEXT_4;
        string LANG_COMIC_TEXT_5;
        string LANG_UNLOCK;
        string LANG_STORE;
        string LANG_HINT_1;
        string LANG_HINT_2;
        string LANG_HINT_3;
        string LANG_HINT_4;
        string LANG_HINT_5;
        string LANG_HINT_6;
        string LANG_HINT_7;
        string LANG_HINT_8;
        string LANG_HINT_9;
        string LANG_HINT_10;
        string LANG_HINT_11;
        string LANG_HINT_12;
        string LANG_HINT_13;
        string LANG_HINT_14;
        string LANG_HINT_15;
        string LANG_HINT_16;
        string LANG_HINT_17;
        string LANG_RESTORE;
        
        string INTRO_PNG;
        string INTRO_PNG2;
        
        string POWERUPS_PNG;
        string POWERUPS_PLIST;
        
        int TOTAL_WORLDS;
        
    private:
        Config();
        void setLanguage();
        void readFullGame();
        
    };
    
    
    static const int FLOORS_TILES_HEIGHT = 7;
    static const int FLOORS_TILES_WIDTH = 20;
    static const int FLOOR_TYPE_OPEN = 0;
    static const int FLOOR_TYPE_CLOSE = 1;
    static const int FLOOR_DARK_LIMIT = 10;
    static const int DARK_COLOR_CORRECTOR = 30;
    static const int DARK_COLOR_CORRECTOR_B = 60;
    static const int NIGHT_COLOR_CORRECTOR_R = 95;
    static const int NIGHT_COLOR_CORRECTOR_G = 140;
    static const int NIGHT_COLOR_CORRECTOR_B = 240;
    static const int GOLD_COLOR_CORRECTOR_R = 255;
    static const int GOLD_COLOR_CORRECTOR_G = 235;
    static const int GOLD_COLOR_CORRECTOR_B = 50;
    static const int GHOST_COLOR_CORRECTOR_R = 80;
    static const int GHOST_COLOR_CORRECTOR_G = 200;
    static const int GHOST_COLOR_CORRECTOR_B = 80;
    static const float MUSIC_VOLUME = 0.5;
    static const float MUSIC_VOLUME_LOW = 0.1;
    static const int STAIR_TILES_HEIGHT = 10;
    static const int STAIR_TILES_WIDTH = 4;
    static const int BUTTON_TILES_WIDTH = 4;
    static const int BUTTON_TILES_HEIGHT = 2;
    static const int HOLE_TILES_HEIGHT = 1;
    static const int HOLE_TILES_WIDTH = 4;
    static const int HINT_TILES_HEIGHT = 6;
    static const int HINT_TILES_WIDTH = 1;
    static const int STAR_TILES_HEIGHT = 2;
    static const int STAR_TILES_WIDTH = 4;
    static const int KEY_TILES_HEIGHT = 2;
    static const int KEY_TILES_WIDTH = 4;
    static const int DOOR_TILES_HEIGHT = 8;
    static const int DOOR_TILES_WIDTH = 2;
    static const int EXIT_TILES_HEIGHT = 4;
    static const int EXIT_TILES_WIDTH = 5;
    static const int ARROW_TILES_HEIGHT = 4;
    static const int ARROW_TILES_WIDTH = 4;
    static const int PLAYER_TILES_HEIGHT = 4;
    static const int PLAYER_TILES_WIDTH = 4;
    static const int PLAYER_STATE_RIGHT = 1;
    static const int PLAYER_STATE_RIGHT_STAIR = 2;
    static const int PLAYER_STATE_RIGHT_BUBBLE = 3;
    static const int PLAYER_STATE_RIGHT_HOLE = 4;
    static const int PLAYER_STATE_LEFT = 5;
    static const int PLAYER_STATE_LEFT_STAIR = 6;
    static const int PLAYER_STATE_LEFT_BUBBLE = 7;
    static const int PLAYER_STATE_LEFT_HOLE = 8;
    static const int PLAYER_STATE_LEFT_BUBBLE_PLUS = 9;
    static const int PLAYER_STATE_RIGHT_BUBBLE_PLUS =10;
    static const int BUBBLE_TILES_HEIGHT = 4;
    static const int BUBBLE_TILES_WIDTH = 4;
    static const int BUBBLE_STATE_NORMAL = 1;
    static const int BUBBLE_STATE_MOVING = 2;
    static const int BUBBLE_STATE_USED = 3;
    static const int LEVEL_STATE_PLAYING = 1;
    static const int LEVEL_STATE_DIE = 2;
    static const int LEVEL_STATE_WIN = 3;
    static const int LEVEL_STATE_SCROLLING = 4;
    static const int LEVEL_STATE_PAUSE = 4;
    static const int LEVEL_STATE_START= 5;
    static const int LEVEL_STATE_PANE = 7;
    static const int TEXT_TILES_HEIGHT = 8;
    static const int TEXT_TILES_WIDTH = 16;
    static const int STAIR_TYPE_LEFT = 1;
    static const int STAIR_TYPE_RIGHT = 2;
    static const int FANCY_TILES_HEIGHT = 8;
    static const int FANCY_TILES_WIDTH = 20;
    static const int ENEMY_TILES_HEIGHT = 4;
    static const int ENEMY_TILES_WIDTH = 4; 
    static const int ENEMY_TILES_RANGE = 2;
    static const int ENEMY_STATE_RIGHT = 1; 
    static const int ENEMY_STATE_LEFT = 2; 
    static const int FAN_TILES_WIDTH = 4;
    static const int FAN_TILES_HEIGHT = 2;
    static const int FAN_TILES_RANGE = 1;
    static const int WALL_TILES_WIDTH = 4;
    static const int WALL_TILES_HEIGHT = 4;
    static const int WALL_TILES_RANGE = 2;
    static const int ROPE_TILES_HEIGHT = 30;
    static const int ROPE_TILES_WIDTH = 2;
    static const int ROPE_TILES_BOMB = 2;
    static const int HUD_TILES_ITEM = 2;
    static const int FIRE_TILES_HEIGHT = 1;
    static const int FIRE_TILES_WIDTH = 1;
    static const int HEML_GRAY = 1;
    static const int HEML_GOLD = 2;
    static const int HEML_RED = 3;
    static const int HEML_NEUTRAL = 4;
    static const int BUBBLE_SPRITE_TAG = 1;
    static const int EXIT_SPRITE_TAG = 2;
    static const int HOLE_SPRITE_TAG = 3;
    static const int KEY_SPRITE_TAG = 4;
    static const int PLAYER_SPRITE_TAG = 5;
    static const int PLAYER_SMOKE_TAG = 6;
    static const int STAIR_SPRITE_TAG = 7;
    static const int STAR_SPRITE_TAG = 8;
    static const int STAR_SHINE_TAG = 9;
    static const int KEY_SHINE_TAG = 10;
    static const int BUBBLE_VAPOUR_TAG = 11;
    static const int LEVEL_TAG = 12;
    static const int ROPE_TAG = 13;
    static const int PLAYER_TAG = 14;
    static const int BUBBLE_EXPLOTION_TAG = 17;
    static const int EXIT_TAG = 18;
    static const int ROPE_FIRE_TAG = 19;
    static const int ROPE_ROPE_TAG = 20;
    static const int HUD_BUBBLE_TAG = 21;
    static const int HUD_STAR_TAG = 22;
    static const int FLOOR_FIRE_TAG = 23;
    static const int ROPE_BURN_TAG = 24;
    static const int MENU_P_TAG = 25;
    static const int MENU_V_TAG = 26;
    static const int ENEMY_SPRITE_TAG = 27;
    static const int ENEMY_SMOKE_TAG = 28;
    static const int FAN_SPRITE_TAG = 29;
    static const int FAN_SHINE_TAG = 30;
    static const int HUD_TAG = 31;
    static const int HUD_TEXT_BUBBLE_TAG = 32;
    static const int HUD_TEXT_STAR_TAG = 33;
    static const int WORLD_SELECT_TAG = 34;
    static const int WALL_TAG = 35;
    static const int PAUSE1_TAG = 36;
    static const int PAUSE2_TAG = 37;
    static const int PAUSE3_TAG = 38;
    static const int FLOOR_WIND_TAG = 39;
    static const int HEML_WIN_TAG = 40;
    static const int HEML_GOLD_TAG = 41;
    static const int HEML_LOSE_TAG = 42;
    static const int HEML_PAUSE_TAG = 43;
    static const int HEML_TAG = 44;
    static const int BATCH_MENU_TAG = 45;
    static const int BATCH_WORLD_TAG = 46;
    static const int BATCH_LEVEL_TAG = 47;
    static const int BATCH_PLAYERL_TAG = 48;
    static const int BATCH_WN_TAG = 49;
    static const int BATCH_HUD_TAG = 50;
    static const int BATCH_SETTINGS_TAG = 51;
    static const int BATCH_CREDITS_TAG = 52;
    static const int BATCH_COMIC_INTRO_TAG = 53;
    static const int BATCH_COMIC_END_TAG = 54;
    static const int BUTTON1_TAG = 55;
    static const int BUTTON2_TAG = 56;
    static const int BUTTON3_TAG = 57;
    static const int BUTTON4_TAG = 58;
    static const int BUTTON5_TAG = 59;
    static const int WOOD_TAG = 60;
    static const int LOADING_TAG = 61;
    static const int MUSIC_TAG = 62;
    static const int FX_TAG = 63;
    static const int PAUSE_TAG = 64;
    static const int RELOAD_TAG = 65;
    static const int DELETE_TAG = 66;
    static const int BATCH_HELP_TAG = 67;
    static const int HINT_TAG = 68;
    static const int HINT_TEXT_TAG = 69;
    static const int HINT_TEXT_TAG2 = 70;
    static const int HINT_TEXT_TAG3 = 71;
    static const int HINT_BLACK_TAG = 72;
    static const int CONFIRM_WINDOW_TAG = 73;
    static const int BATCH_LOADING_TAG = 74;
    static const int BG_CONFIRM_TAG = 75;
    static const int OF_BUTTON_TAG = 76;
    static const int IPAD_TAG = 77;
    static const int WALL_SPRITE_TAG = 78;
    static const int EXTRA_BUBBLE_SPRITE_TAG = 79;
    static const int BUBBLELIQUID_SPRITE_TAG = 80;
    static const int HUD_BUBLENUMBER_TAG = 81;
    static const int INAPPBUTTON_TAG = 82;
    static const int BATCH_BLACK_TAG = 83;
    static const int HINT_TAG_TEXT = 84;
    static const int HINT_TAG_SHADOW = 85;
    static const int MENU_MAINMENU_TAG = 86;
    static const int RESTORE_TAG = 87;
    static const int STAIRDOOR_TAG = 88;
    static const int STAIRDOORPARENT_TAG = 89;
    
    static const int BUBBLE_TAG = 500;
    static const int FLOOR_TAG = 600;
    static const int COIN_TAG = 700;
    static const int WORLD_TAG = 800;
    static const int DISABLEDWORLD_TAG = 900;
    static const int LEVELGROUP_TAG = 1000;
    static const int STAIR_TAG = 1100;
    static const int FIRE_TAG = 1200;
    static const int FANCY_TAG = 1300;
    
    static const int LEVELS_PER_WORLD = 16;
    
    static const string BUBLE_FRAME_A = "Burbuja000%02d.png";
    static const string BUBLE_FRAME_B = "Burbujaexplode000%02d.png";
    static const string EXIT_FRAME_A = "door000%02d.png";
    static const string KEY_FRAME_A = "key000%02d.png";
    static const string KEY_FRAME_B = "keyexplode000%02d.png";
    static const string PLAYER_FRAME_A = "Correr000%02d.png";
    static const string PLAYER_FRAME_B = "escalar_normal000%02d.png";
    static const string PLAYER_FRAME_C = "Callendo_normal000%02d.png";
    static const string PLAYER_FRAME_D = "Pj_subiendo000%02d.png";
    static const string PLAYER_FRAME_E = "tirar_bomba000%02d.png";
    static const string PLAYER_FRAME_F = "victoria000%02d.png";
    static const string PLAYER_FRAME_G = "pj_explota000%02d.png";
    static const string STAR_FRAME_A = "star000%02d.png";
    static const string STAR_FRAME_B = "starexplode000%02d.png";
    static const string ROPE_FRAME_A = "cuerda000%02d.png";
    static const string ENEMY_FRAME_A = "Correr000%02d.png";
    static const string ROPE_BURN_FRAME = "cuerdaquemada.png";
    static const string LEVELS_JSON = "%slevels.json";
    static const string SETTINGS_JSON = "%ssettings.json";
    static const string INITLEVELS_JSON = "initlevels.json";
    static const string INITSETTINGS_JSON = "initsettings.json";
    static const string WORLDS_JSON = "worlds.json"; 
    static const string LEVEL_JSON = "w%d-level%02d.json";
    static const string FLOOR_PNG = "floor%d.png";
    static const string TITLE_PNG = "title.png";
    static const string KID_PNG = "kid.png";
    static const string BLACK_PNG = "black.png";
    static const string MAP_PNG = "maptable.png";
    static const string HUD_STAR_PNG = "starhud.png";
    static const string HUD_PAUSE_PNG = "buttonpause.png";
    static const string HUD_RELOAD_PNG = "buttonreload.png"; 
    static const string FAN_FRAME_A = "key000%02d.png";
    static const string FAN_PNG = "key.png";
    static const string ENEMY_PNG = "character.png";
    static const string ENEMY_PLIST = "character.plist";
    static const string WORLD_BUTTON1 = "button1.png"; 
    static const string WORLD_BUTTON2 = "button2.png"; 
    static const string WORLD_WATER = "water.png"; 
    static const string WORLD_BOARD = "worldboard.png";
    static const string WORLD_ANCHOR = "anchor.png"; 
    static const string LEVEL_BUTTON_A = "level-white.png";
    static const string LEVEL_BUTTON_B = "level-open.png";
    static const string LEVEL_BUTTON_C = "level-gold.png";
    static const string LEVEL_BUTTON_D = "level-close.png";
    static const string SQUARE_BUTTON_A = "level_current.png";
    static const string SQUARE_BUTTON_B = "level_1star.png";
    static const string SQUARE_BUTTON_C = "level_2star.png";
    static const string SQUARE_BUTTON_D = "level_3star.png";
    static const string SQUARE_BUTTON_E = "level_closed.png";
    static const string DOUBLON_WORLD = "doublon.png";
    static const string CLOUD_A = "cloud1.png";
    static const string CLOUD_B = "cloud2.png";
    static const string CLOUD_C = "cloud3.png";
    static const string WOOD_PNG = "wood.png"; 
    static const string SCROLL_PNG = "scroll.png";
    static const string SCROLL2_PNG = "scroll2.png";
    static const string ICON_WORLD = "world%d.png";
    static const string LOADING_SCREEN = "loading.png"; 
    static const string WORLD_SELECT_BG = "mainback.png";  
    static const string WORLD_SELECT_BACK = "buttonback.png";
    static const string WORLD_SELECT_AD_1 = "moregames.png";
    static const string WORLD_SELECT_AD_2 = "morelevels.png";
    static const string STAIR_PNG = "stair.png";  
    static const string FLOOR_BACK_PNG = "floor5back.png";
    static const string FLOOR_SUPER_PNG = "mast.png";
    static const string FLOOR_SUPER_BACK_PNG = "mastback.png";
    static const string HOLE_PNG = "hole.png"; 
    static const string WALL_PNG = "wall.png"; 
    static const string CHAINS_PNG = "chains.png"; 
    static const string TABLE_PNG = "table.png";
    static const string ARROW_PNG = "arrow.png";
    static const string MINISCROLL_PNG = "miniscroll.png";
    static const string SETTINGS_OF_PNG = "ofbutton.png";
    static const string GFF_PNG = "gff.png";
    static const string INITSCORE_JSON = "initscore.json";
    static const string SCORE_JSON = "%sscore.json";
    static const string GFF_LOGO_PNG = "gff-logo.png";
    static const string COMIC_INTRO_BG = "comicback.png";
    static const string COMIC_INTRO_1 = "fig-1.png";
    static const string COMIC_INTRO_2 = "fig-2.png";
    static const string COMIC_INTRO_3 = "fig-3.png";
    static const string COMIC_INTRO_TXT_1 = "text-1.png";
    static const string COMIC_INTRO_TXT_2 = "text-2.png";
    static const string COMIC_INTRO_TXT_3 = "text-3.png";
    static const string COMIC_END_BG = "comicback.png";
    static const string COMIC_END_1 = "fig-4.png";
    static const string COMIC_END_2 = "fig-5.png";
    static const string COMIC_END_TXT_1 = "text-4.png";
    static const string COMIC_END_TXT_2 = "text-5.png";
    static const string HINT1_PNG = "help-1.png";
    static const string HINT2_PNG = "help-2.png";
    static const string HINT3_PNG = "help-3.png";
    static const string HINT4_PNG = "help-4.png";
    static const string HINT5_PNG = "help-5.png";
    static const string HUD_MINI_BUBBLE = "bubblehud.png";
    static const string HUD_BUBLEMETTER = "bubblemetter000%02d.png";
    static const string HUD_WOODBACK_PNG = "woodback.png";
    static const string HUD_WOODBUBBLE_PNG = "woodbubble.png";
    static const string INAPP_PNG = "inapp.png";
    static const string SCROLLTABLE_PNG = "scrolltable2.png";
    static const string SCROLLTABLEBIG_PNG = "scrolltable.png";
    static const string MAPTABLE_PNG = "maptable.png";

    static const string LANG_EN = "lang-en.json";    
    static const string LANG_ES = "lang-es.json";
    static const string LANG_PT = "lang-pt.json";
    static const string LANG_DE = "lang-de.json";
    static const string LANG_FR = "lang-fr.json";
    static const string LANG_IT = "lang-it.json";
    static const string LANG_KO = "lang-ko.json";
    static const string LANG_ZH = "lang-zh.json";
}
    
    
#endif