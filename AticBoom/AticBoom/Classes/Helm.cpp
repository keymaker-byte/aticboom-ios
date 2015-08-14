//
//  Helm.cpp
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

#include "Helm.h"

namespace aticboom {
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    Helm::Helm() : cocos2d::CCNode() {
        this->autorelease();
        this->initAnimations();
        
    };
    
    Helm::~Helm() {
    };
    
    void Helm::initAnimations() {
        CCSprite* black = CCSprite::spriteWithSpriteFrameName(BLACK_PNG.c_str());
        black->setScale(100);
        black->setPosition(Geometry::getScreenCenter());
        black->setOpacity(0);
        this->addChild(black, 1, 1);
        CCSprite* heml = CCSprite::spriteWithSpriteFrameName("heml.png");
        heml->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MARGEN - Config::sharedConfig()->HEML_OBJECT_MARGEN));
        heml->setOpacity(0);
        this->addChild(heml, 2, 2);
        CCLabelBMFont *vBestScore1 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_BESTSCORE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        vBestScore1->cocos2d::CCNode::setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN*4));
        vBestScore1->setOpacity(0);
        vBestScore1->setColor(ccc3(255,255,255));
        CCLabelBMFont *vBestScore2 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_BESTSCORE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        vBestScore2->cocos2d::CCNode::setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN*4));
        vBestScore2->setOpacity(0);
        vBestScore2->setColor(ccc3(255,255,255));
        CCLabelBMFont *vScore1 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_SCORE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        vScore1->cocos2d::CCNode::setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN*3));
        vScore1->setOpacity(0);
        vScore1->setColor(ccc3(255,255,255));
        CCLabelBMFont *vScore2 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_SCORE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        vScore2->cocos2d::CCNode::setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN*3));
        vScore2->setOpacity(0);
        vScore2->setColor(ccc3(255,255,255));
        CCSprite *vMainMenu1 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_MENU.c_str());
        vMainMenu1->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN*2) );
        vMainMenu1->setOpacity(0);
        CCSprite *vMainMenu2 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_MENU.c_str());
        vMainMenu2->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN*2) );
        vMainMenu2->setOpacity(0);
        CCSprite *vMainMenu3 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_MENU);
        vMainMenu3->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN) );
        vMainMenu3->setOpacity(0);
        CCSprite *vMainMenu4 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_MENU);
        vMainMenu4->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN) );
        vMainMenu4->setOpacity(0);
        CCSprite *vPlayAgain1 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_AGAIN);
        vPlayAgain1->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN) );
        vPlayAgain1->setOpacity(0);
        CCSprite *vPlayAgain2 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_AGAIN);
        vPlayAgain2->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN + Config::sharedConfig()->HEML_OBJECT_MARGEN) );
        vPlayAgain2->setOpacity(0);
        CCSprite *vPlayAgain3 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_AGAIN);
        vPlayAgain3->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN) );
        vPlayAgain3->setOpacity(0);
        CCSprite *vPlayNext1 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_NEXT);
        vPlayNext1->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN) );
        vPlayNext1->setOpacity(0);
        CCSprite *vPlayNext2 = Geometry::makeMenuItem(Config::sharedConfig()->LANG_NEXT);
        vPlayNext2->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN) );
        vPlayNext2->setOpacity(0);
        CCSprite *vResume = Geometry::makeMenuItem(Config::sharedConfig()->LANG_RESUME);
        vResume->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->HEML_MENU_MARGEN) );
        vResume->setOpacity(0);
        CCNode* vMenuWin = new CCNode();
        vMenuWin->addChild(vMainMenu1, 0, 1);
        vMenuWin->addChild(vPlayAgain1, 0, 2);
        vMenuWin->addChild(vPlayNext1, 0, 3);
        vMenuWin->addChild(vScore1, 0, 4);
        vMenuWin->addChild(vBestScore1, 0, 5);
        vMenuWin->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH, -Config::sharedConfig()->SCREEN_HEIGHT) );
        this->addChild(vMenuWin, 3, 3);
        CCNode* vMenuGold = new CCNode();
        vMenuGold->addChild(vMainMenu2, 0, 1);
        vMenuGold->addChild(vPlayAgain2, 0, 2);
        vMenuGold->addChild(vPlayNext2, 0, 3);
        vMenuGold->addChild(vScore2, 0, 4);
        vMenuGold->addChild(vBestScore2, 0, 5);
        vMenuGold->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH, -Config::sharedConfig()->SCREEN_HEIGHT) );
        this->addChild(vMenuGold, 3, 4);
        CCNode* vMenuLost = new CCNode();
        vMenuLost->addChild(vMainMenu3, 0, 1);
        vMenuLost->addChild(vPlayAgain3, 0, 2);
        vMenuLost->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH, -Config::sharedConfig()->SCREEN_HEIGHT) );
        this->addChild(vMenuLost, 3, 5);
        CCNode* vMenuPause = new CCNode();
        vMenuPause->addChild(vMainMenu4, 0, 1);
        vMenuPause->addChild(vResume, 0, 2);
        vMenuPause->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH, -Config::sharedConfig()->SCREEN_HEIGHT) );
        this->addChild(vMenuPause, 3, 6);
        CCSprite* graySkull = CCSprite::spriteWithSpriteFrameName("grayskull.png");
        graySkull->setPosition(CCPoint(heml->getContentSize().width/2, heml->getContentSize().height/2));
        graySkull->setOpacity(0);
        heml->addChild(graySkull, 4, 7);
        CCSprite* goldSkull = CCSprite::spriteWithSpriteFrameName("yellowskull.png");
        goldSkull->setPosition(CCPoint(heml->getContentSize().width/2, heml->getContentSize().height/2));
        goldSkull->setOpacity(0);
        heml->addChild(goldSkull, 4, 8);
        CCSprite* redSkull = CCSprite::spriteWithSpriteFrameName("redskull.png");
        redSkull->setPosition(CCPoint(heml->getContentSize().width/2, heml->getContentSize().height/2));
        redSkull->setOpacity(0);
        heml->addChild(redSkull, 4, 9);
    }
    
    void Helm::activateHeml(int type, int score, int bestScore){
        CCSprite* black = (CCSprite *) this->getChildByTag(1);
        CCSprite* heml = (CCSprite *) this->getChildByTag(2);
        CCNode* vMenu;
        CCSprite* skull;
        CCLabelBMFont* label2;
        char bufferBestScore[50];
        sprintf(bufferBestScore, Config::sharedConfig()->LANG_BESTSCORE.c_str(), bestScore);
        vType = type;
        switch (type) {
            case HEML_GRAY:
                vMenu = (CCNode *) this->getChildByTag(3);
                skull = (CCSprite *) heml->getChildByTag(7);
                label2 = (CCLabelBMFont *) vMenu->getChildByTag(5);
                label2->setString(bufferBestScore);
                break;
            case HEML_GOLD:
                vMenu = (CCNode *) this->getChildByTag(4);
                skull = (CCSprite *) heml->getChildByTag(8);
                label2 = (CCLabelBMFont *) vMenu->getChildByTag(5);
                label2->setString(bufferBestScore);
                break;
            case HEML_RED:
                vMenu = (CCNode *) this->getChildByTag(5);
                skull = (CCSprite *) heml->getChildByTag(9);
                break;
            case HEML_NEUTRAL:
                vMenu = (CCNode *) this->getChildByTag(6);
                skull = (CCSprite *) heml->getChildByTag(7);
                break;
        }
        vMenu->setPosition(CCPointZero);
        switch (type) {
            case HEML_GRAY:
            case HEML_GOLD: {
                CCSprite* item1 = (CCSprite*)vMenu->getChildByTag(1);
                item1->runAction(CCFadeIn::actionWithDuration(1));
                CCSprite* item2 = (CCSprite*)vMenu->getChildByTag(2);
                item2->runAction(CCFadeIn::actionWithDuration(1));
                CCSprite* item3 = (CCSprite*)vMenu->getChildByTag(3);
                item3->runAction(CCFadeIn::actionWithDuration(1));
                CCLabelBMFont* item4 = (CCLabelBMFont*)vMenu->getChildByTag(4);
                item4->runAction(CCFadeIn::actionWithDuration(1));
                CCLabelBMFont* item5 = (CCLabelBMFont*)vMenu->getChildByTag(5);
                item5->runAction(CCFadeIn::actionWithDuration(1));
                heml->runAction(CCSequence::actions(CCFadeIn::actionWithDuration(0.1) ,NULL));
                heml->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(10, 360)));
                black->runAction(CCFadeIn::actionWithDuration(1));
                skull->runAction(CCFadeIn::actionWithDuration(1));
                break;
            }
            case HEML_RED: {
                CCSprite* item4 = (CCSprite*)vMenu->getChildByTag(1);
                item4->runAction(CCFadeIn::actionWithDuration(1));
                CCSprite* item5 = (CCSprite*)vMenu->getChildByTag(2);
                item5->runAction(CCFadeIn::actionWithDuration(1));
                heml->runAction(CCSequence::actions(CCFadeIn::actionWithDuration(0.1) ,NULL));
                heml->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(10, 360)));
                black->runAction(CCFadeIn::actionWithDuration(1));
                skull->runAction(CCFadeIn::actionWithDuration(1));
                break;
            }
            case HEML_NEUTRAL: {
                CCSprite* item6 = (CCSprite*)vMenu->getChildByTag(1);
                item6->setOpacity(255);
                CCSprite* item7 = (CCSprite*)vMenu->getChildByTag(2);
                item7->setOpacity(255);
                heml->setOpacity(255);
                black->setOpacity(255);
                skull->setOpacity(255);
                break;
            }
            default:
                break;
        }
    }
    
    void Helm::inactivateHeml(){
        CCSprite* black = (CCSprite *) this->getChildByTag(1);
        CCSprite* heml = (CCSprite *) this->getChildByTag(2);
        CCNode* vMenuWin = (CCNode *) this->getChildByTag(3);
        CCNode* vMenuGold = (CCNode *) this->getChildByTag(4);
        CCNode* vMenuLost = (CCNode *) this->getChildByTag(5);
        CCNode* vMenuPause = (CCNode *) this->getChildByTag(6);
        heml->setOpacity(0);
        black->setOpacity(0);
        CCSprite* item1 = (CCSprite*)vMenuWin->getChildByTag(1);
        item1->setOpacity(0);
        CCSprite* item2 = (CCSprite*)vMenuWin->getChildByTag(2);
        item2->setOpacity(0);
        CCSprite* item3 = (CCSprite*)vMenuWin->getChildByTag(3);
        item3->setOpacity(0);
        vMenuWin->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH, -Config::sharedConfig()->SCREEN_HEIGHT) );
        CCSprite* item4 = (CCSprite*)vMenuGold->getChildByTag(1);
        item4->setOpacity(0);
        CCSprite* item5 = (CCSprite*)vMenuGold->getChildByTag(2);
        item5->setOpacity(0);
        CCSprite* item6 = (CCSprite*)vMenuGold->getChildByTag(3);
        item6->setOpacity(0);
        vMenuGold->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH, -Config::sharedConfig()->SCREEN_HEIGHT) );
        CCSprite* item7 = (CCSprite*)vMenuLost->getChildByTag(1);
        item7->setOpacity(0);
        CCSprite* item8 = (CCSprite*)vMenuLost->getChildByTag(2);
        item8->setOpacity(0);
        vMenuLost->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH, -Config::sharedConfig()->SCREEN_HEIGHT) );
        CCSprite* item9 = (CCSprite*)vMenuPause->getChildByTag(1);
        item9->setOpacity(0);
        CCSprite* item10 = (CCSprite*)vMenuPause->getChildByTag(2);
        item10->setOpacity(0);
        vMenuPause->setPosition( CCPoint(-Config::sharedConfig()->SCREEN_WIDTH, -Config::sharedConfig()->SCREEN_HEIGHT) );
    }
    
}

