//
//  HelpScene.cpp
//  AticBoom
//
//  Created by Claudio Alvial on 1/6/12.
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

#include "HelpScene.h"

namespace aticboom {
    
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    HelpScene::HelpScene() : HelpScene::CCLayer() {
    }
    
    HelpScene::~HelpScene() {
    }
    
    void HelpScene::onEnter() {
        CCLayer::onEnter();
    }
    
    void HelpScene::onExit() {
        CCLayer::onExit();
        CCSpriteBatchNode* batch = (CCSpriteBatchNode*)this->getChildByTag(BATCH_HELP_TAG);
        this->removeChildByTag(BATCH_HELP_TAG, true);
        batch->release();
        cocos2d::CCDirector::sharedDirector()->purgeCachedData();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    }
    
    void HelpScene::keyBackClicked() {
        this->backToTitle();
    }
    
    CCScene* HelpScene::scene() {
        CCScene *scene = CCScene::node();
        HelpScene *layer = HelpScene::node();
        scene->addChild(layer, 0, 1);
        return scene;
    }
    
    bool HelpScene::init() {
        if ( !CCLayer::init() ) {
            return false;
        }
        this->setIsKeypadEnabled(true);
        CCDirector::sharedDirector()->resume();
        this->touchEnabled=false;
        this->currentPage = 0;
        CCSpriteBatchNode* batch = new CCSpriteBatchNode();
        batch->initWithFile(CCFileUtils::fullPathFromRelativePath(Config::sharedConfig()->HELPHIATORY_PNG.c_str()), 30);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->HELPHIATORY_PLIST.c_str());
        this->addChild(batch,0, BATCH_HELP_TAG);
        CCSprite* sTableBack = CCSprite::spriteWithSpriteFrameName(SCROLLTABLEBIG_PNG.c_str());
        sTableBack->setPosition(Geometry::getScreenCenter());
        this->addChild(sTableBack, 0);
        CCLabelBMFont* labelTouch = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_CONTINUE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        labelTouch->setScale(Config::sharedConfig()->FONT_SCALE);
        labelTouch->setColor(ccc3(50,50,50));
        labelTouch->setOpacity(0);
        labelTouch->setScale(0.7);
        labelTouch->setPosition(Geometry::getScreenBotomCenterAdjust(Config::sharedConfig()->HINT_TOUCH_XMARGIN, Config::sharedConfig()->HINT_TOUCH_YMARGIN));
        this->addChild(labelTouch, 2, 10);
        CCSprite* sHintA = CCSprite::spriteWithSpriteFrameName(HINT1_PNG.c_str());
        sHintA->setPosition(CCPoint(Config::sharedConfig()->SCREEN_WIDTH*2,Config::sharedConfig()->SCREEN_HEIGHT/2));
        sHintA->setOpacity(0);
        this->addChild(sHintA, 1, 1);
        CCSprite* sHintB = CCSprite::spriteWithSpriteFrameName(HINT2_PNG.c_str());
        sHintB->setPosition(CCPoint(Config::sharedConfig()->SCREEN_WIDTH*2,Config::sharedConfig()->SCREEN_HEIGHT/2));
        sHintB->setOpacity(0);
        this->addChild(sHintB, 1, 2);
        CCSprite* sHintC = CCSprite::spriteWithSpriteFrameName(HINT3_PNG.c_str());
        sHintC->setPosition(CCPoint(Config::sharedConfig()->SCREEN_WIDTH*2,Config::sharedConfig()->SCREEN_HEIGHT/2));
        sHintC->setOpacity(0);
        this->addChild(sHintC, 1, 3);
        CCSprite* sHintD = CCSprite::spriteWithSpriteFrameName(HINT4_PNG.c_str());
        sHintD->setPosition(CCPoint(Config::sharedConfig()->SCREEN_WIDTH*2,Config::sharedConfig()->SCREEN_HEIGHT/2));
        sHintD->setOpacity(0);
        this->addChild(sHintD, 1, 4);
        CCSprite* sHintE = CCSprite::spriteWithSpriteFrameName(HINT5_PNG.c_str());
        sHintE->setPosition(CCPoint(Config::sharedConfig()->SCREEN_WIDTH*2,Config::sharedConfig()->SCREEN_HEIGHT/2));
        sHintE->setOpacity(0);
        this->addChild(sHintE, 1, 5);
        CCFiniteTimeAction* MovePage = CCFadeIn::actionWithDuration(0.5);
        CCFiniteTimeAction* Page1Done = CCCallFuncN::actionWithTarget( this, callfuncN_selector(HelpScene::prepareNextPage));
        sHintA->runAction(CCSequence::actions(MovePage, Page1Done, NULL));
        CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
        //ipad fix
        if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
            Border* border = new Border();
            this->addChild(border, 999);
        }
        return true;
    }
    
    void HelpScene::prepareNextPage(CCNode* nada) {
        currentPage++;
        CCLabelBMFont* labelTouch = (CCLabelBMFont*)this->getChildByTag(10);
        labelTouch->setOpacity(255);
        touchEnabled = true;
    }
    
    void HelpScene::showNextPage(int thePage) {
        CCSprite* sPrevPage = (CCSprite*)this->getChildByTag(thePage);
        CCSprite* sNextPage = (CCSprite*)this->getChildByTag(thePage+1);
        CCLabelBMFont* labelTouch = (CCLabelBMFont*)this->getChildByTag(10);
        labelTouch->setOpacity(0);
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER1.c_str()));
        CCFiniteTimeAction* MovePageOut = CCFadeOut::actionWithDuration(0.5);
        sPrevPage->runAction(CCSequence::actions(MovePageOut, NULL));
        CCFiniteTimeAction* MovePageIn = CCFadeIn::actionWithDuration(0.5);
        CCFiniteTimeAction* PageInDone = CCCallFuncN::actionWithTarget( this, callfuncN_selector(HelpScene::prepareNextPage));
        sNextPage->runAction(CCSequence::actions(MovePageIn, PageInDone, NULL));
    }
    
    bool HelpScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
        if ( touchEnabled == true ) {
            touchEnabled = false;
            if (currentPage < 5)
                showNextPage(currentPage);
            else
                backToTitle();
        }
        return true;
    }
    
    void HelpScene::backToTitle() {
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, MenuScene::scene()));
    }
    
}
