//
//  Border.cpp
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

#include "Border.h"



namespace aticboom {
    using namespace cocos2d;
    
    Border::Border() : cocos2d::CCNode() {
        this->autorelease();
        this->initAnimations();
    };
    
    Border::~Border() {
        
    };
    
    void Border::initAnimations() {
        CCSprite* left = CCSprite::spriteWithFile("ipadembed_r1_c1.png");
        left->setPosition(CCPoint(left->getContentSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
        this->addChild(left, 1000);
        CCSprite* up = CCSprite::spriteWithFile("ipadembed_r1_c2.png");
        up->setPosition(CCPoint(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height - up->getContentSize().height/2));
        this->addChild(up, 1001);
        CCSprite* right = CCSprite::spriteWithFile("ipadembed_r1_c3.png");
        right->setPosition(CCPoint(CCDirector::sharedDirector()->getWinSize().width - right->getContentSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
        this->addChild(right, 1002);
        
    }
    
}
