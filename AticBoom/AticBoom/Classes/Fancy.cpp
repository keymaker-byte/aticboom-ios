//
//  Fancy.cpp
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

#include "Fancy.h"

namespace aticboom {
    
    using namespace cocos2d;
    
    Fancy::Fancy(Json::Value fancies, int world) : Fancy::GameObject(fancies, world){
        this->image = fancies["image"].asInt();
        this->world = world;
        this->tileWidth = HINT_TILES_WIDTH;
        this->tileHeight = HINT_TILES_HEIGHT;
        this->initSimpleSprite();
        this->setTilePosition();
        this->shown = false;
        this->floor = fancies["position"]["y"].asInt();
    };
    
    Fancy::~Fancy(){
        
    };
    
    void Fancy::initSimpleSprite(){
        char buffer[50];
        sprintf(buffer, "hint%i.png", this->image);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        pSprite->setOpacity(0);
        pSprite->setColor(ccc3(255, 255, 255));
        this->addChild(pSprite, 0, HINT_TAG);
        
        CCLabelBMFont* label;
        CCLabelBMFont* labelShadow;
        switch (this->image) {
            case 1:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_1.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_1.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 2:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_2.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_2.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 3:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_3.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_3.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 4:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_4.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_4.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 5:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_5.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_5.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 6:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_6.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_6.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 7:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_7.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_7.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 8:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_8.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_8.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 9:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_9.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_9.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 10:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_10.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_10.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 11:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_11.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_11.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 12:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_12.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_12.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 13:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_13.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_13.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 14:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_14.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_14.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 15:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_15.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_15.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 16:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_16.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_16.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            case 17:
                label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_17.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_HINT_17.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
            default:
                label = CCLabelBMFont::labelWithString("", Config::sharedConfig()->BMFONT_NAME.c_str());
                labelShadow = CCLabelBMFont::labelWithString("", Config::sharedConfig()->BMFONT_NAME.c_str());
                break;
        }
        label->setOpacity(0);
        labelShadow->setColor(ccc3(10, 10, 10));
        labelShadow->setOpacity(0);
        labelShadow->setPosition(CCPoint(labelShadow->getPosition().x + Config::sharedConfig()->SHADOW_TEXT, labelShadow->getPosition().y - Config::sharedConfig()->SHADOW_TEXT));
        this->addChild(label, 2, HINT_TAG_TEXT); 
        this->addChild(labelShadow, 1, HINT_TAG_SHADOW);
    };
    
    void Fancy::appear(){
        if(!this->shown) {
            CCSprite* pSprite = (CCSprite *)this->getChildByTag(HINT_TAG);  
            pSprite->runAction(CCFadeIn::actionWithDuration(0.5));
            CCLabelBMFont* label = (CCLabelBMFont *)this->getChildByTag(HINT_TAG_TEXT);
            label->runAction(CCFadeIn::actionWithDuration(0.5));
            CCLabelBMFont* labelShadow = (CCLabelBMFont *)this->getChildByTag(HINT_TAG_SHADOW);
            labelShadow->runAction(CCFadeIn::actionWithDuration(0.5));
        }
        this->shown = true;
    };
    
    void Fancy::dissapear(){
        if(this->shown) {
            CCSprite* pSprite = (CCSprite *)this->getChildByTag(HINT_TAG); 
            pSprite->runAction(CCFadeOut::actionWithDuration(0.5));
            CCLabelBMFont* label = (CCLabelBMFont *)this->getChildByTag(HINT_TAG_TEXT);
            label->runAction(CCFadeOut::actionWithDuration(0.5));
            CCLabelBMFont* labelShadow = (CCLabelBMFont *)this->getChildByTag(HINT_TAG_SHADOW);
            labelShadow->runAction(CCFadeOut::actionWithDuration(0.5));
        }
        this->shown = false;
    };
}
