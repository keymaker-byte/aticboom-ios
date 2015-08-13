//
//  Hud.cpp
//  AticBoom
//
//  Created by Juan Rodriguez on 1/5/12.
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

#include "Hud.h"



namespace aticboom {
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    Hud::Hud(Json::Value level) : cocos2d::CCNode() {
        ANIMATION_BUBBLELIQUID = new cocos2d::CCMutableArray<cocos2d::CCSpriteFrame* >*[30];
        this->autorelease();
        this->initAnimations();
        this->bubbleSize = 0;
        this->buildBubbles(level);
    };
    
    Hud::~Hud() {
        for (int i = 0; i < 30; i++) {
            this->ANIMATION_BUBBLELIQUID[i]->release();
        }
    };
    
    void Hud::initAnimations() {
        
        CCSprite* wood = CCSprite::spriteWithSpriteFrameName(HUD_WOODBUBBLE_PNG.c_str());
        wood->setPosition(CCPoint(wood->getPosition().x, - wood->getContentSize().height/4));
        this->addChild(wood, 2);
        
        CCSprite* woodback = CCSprite::spriteWithSpriteFrameName(HUD_WOODBACK_PNG.c_str());
        woodback->setPosition(CCPoint(wood->getPosition().x, wood->getPosition().y));
        this->addChild(woodback, 1);
        
        CCLabelBMFont *bublleNumberLabel = CCLabelBMFont::labelWithString("0", Config::sharedConfig()->BMFONT_NAME.c_str());
        bublleNumberLabel->setPosition(CCPoint(wood->getPosition().x, wood->getPosition().y));
        bublleNumberLabel->setScale(1.1);
        bublleNumberLabel->setOpacity(200);
        this->addChild(bublleNumberLabel, 3, HUD_BUBLENUMBER_TAG);
        
        CCSprite* preload = CCSprite::spriteWithSpriteFrameName(HUD_RELOAD_PNG.c_str());
        preload->setPosition( CCPoint(- Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->HUD_TEXT_MARGEN + HUD_TILES_ITEM * Config::sharedConfig()->TILE_WIDTH * 5+ Config::sharedConfig()->WOOD_OBJECT_MARGEN,0) );
        this->addChild(preload, 3, RELOAD_TAG); 
        
        CCSprite* ppause = CCSprite::spriteWithSpriteFrameName(HUD_PAUSE_PNG.c_str());
        ppause->setPosition( CCPoint(- Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->HUD_TEXT_MARGEN + HUD_TILES_ITEM * Config::sharedConfig()->TILE_WIDTH * 6+ Config::sharedConfig()->WOOD_OBJECT_MARGEN + Config::sharedConfig()->WOOD_OBJECT_MARGEN, 0) );
        this->addChild(ppause, 3, PAUSE_TAG);     

        int starSpace = 0;
        for(int i = 1; i <= 3; i++) {
            CCSprite* starSprite = CCSprite::spriteWithSpriteFrameName(HUD_STAR_PNG.c_str());
            starSprite->setPosition(CCPoint((- Config::sharedConfig()->SCREEN_WIDTH/2 + HUD_TILES_ITEM * Config::sharedConfig()->TILE_WIDTH / 2 + Config::sharedConfig()->WOOD_OBJECT_MARGEN) + starSpace, 0));
            starSprite->setOpacity(50);
            this->addChild(starSprite, 3, COIN_TAG + i);
            starSpace += Config::sharedConfig()->HUD_STAR_SEPARATOR;
        }
        
        char buffer [50];
        sprintf (buffer, HUD_BUBLEMETTER.c_str(), 1);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        pSprite->setColor(ccc3(100, 100, 180));
        this->addChild(pSprite, 1, BUBBLELIQUID_SPRITE_TAG);
        pSprite->setPosition(CCPoint(pSprite->getPosition().x, - pSprite->getContentSize().height/4));
        
        
        for(int i = 1; i <= 30; i++) {
            ANIMATION_BUBBLELIQUID[i-1] = new CCMutableArray<CCSpriteFrame*>();
            sprintf (buffer, HUD_BUBLEMETTER.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_BUBBLELIQUID[i-1]->addObject(frame);
        }
        
        pSprite->runAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_BUBBLELIQUID[0], 0.1), false));
        
    }
    
    void Hud::setStarNumber(int number) {
        if(number > 0) {
            CCSprite* starSprite = (CCSprite*) this->getChildByTag(COIN_TAG + number);
            starSprite->setOpacity(255);
        }
    }
    
    void Hud::buildBubbles(Json::Value level) {
        this->totalBubble = level["bubbleNumber"].asInt();
        this->bubbleSize = level["bubbleNumber"].asInt();
        CCLabelBMFont *bublleNumberLabel = (CCLabelBMFont*)this->getChildByTag(HUD_BUBLENUMBER_TAG);
        char buffer[50];
        sprintf(buffer, "%i", this->bubbleSize);
        bublleNumberLabel->setString(buffer);
    }
    
    void Hud::addBubble(){
        if(this->bubbleSize == this->totalBubble) {
            return;
        }
        
        this->bubbleSize++;
        
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(BUBBLELIQUID_SPRITE_TAG);
        int index = 29 - 29 * this->bubbleSize / this->totalBubble;
        pSprite->runAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_BUBBLELIQUID[index], 0.1), false));
        
        CCLabelBMFont *bublleNumberLabel = (CCLabelBMFont*)this->getChildByTag(HUD_BUBLENUMBER_TAG);
        char buffer[50];
        sprintf(buffer, "%i", this->bubbleSize);
        bublleNumberLabel->setString(buffer);
    }
    
    
    
    
    void Hud::killBubble() {
        this->bubbleSize--;
        
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(BUBBLELIQUID_SPRITE_TAG);
        int index = 29 - 29 * this->bubbleSize / this->totalBubble;
        pSprite->runAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_BUBBLELIQUID[index], 0.1), false));
        
        CCLabelBMFont *bublleNumberLabel = (CCLabelBMFont*)this->getChildByTag(HUD_BUBLENUMBER_TAG);
        char buffer[50];
        sprintf(buffer, "%i", this->bubbleSize);
        bublleNumberLabel->setString(buffer);
    }
    
}
