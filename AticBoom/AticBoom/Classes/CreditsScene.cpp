//
//  CreditsScene.cpp
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

#include <iostream>
#include <sstream>
#include <string>
#include "CreditsScene.h"

CreditsScene::CreditsScene() : CreditsScene::CCLayer() {
}

CreditsScene::~CreditsScene() {
}

void CreditsScene::onEnter() {
    CCLayer::onEnter();
}

void CreditsScene::onExit() {
    CCLayer::onExit();
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*)this->getChildByTag(BATCH_MENU_TAG);
    this->removeChildByTag(BATCH_MENU_TAG, true);
    batch->release();
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

void CreditsScene::keyBackClicked() {
    this->backToTitle(NULL);
}

CCScene* CreditsScene::scene() {
    CCScene *scene = CCScene::node();
    CreditsScene *layer = CreditsScene::node();
    scene->addChild(layer, 0, 1);
    return scene;
}

bool CreditsScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled(true);
    CCDirector::sharedDirector()->resume();
    CCSpriteBatchNode* batch = new CCSpriteBatchNode();
    batch->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->MENU_PNG.c_str()), 28);
    this->addChild(batch, 0, BATCH_MENU_TAG);
    CCSprite* seaSprite = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BG.c_str());
    seaSprite->setPosition(Geometry::getScreenCenter());
    this->addChild(seaSprite, 1);
    CCParticleSystemPoint* shine = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->WORLD_BURNING_PARTICLE.c_str());
    shine->setPosition( Geometry::getScreenCenter() );
    this->addChild(shine, 1);
    CCLabelBMFont* lTitle = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_CREDITS.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    lTitle->setScale(Config::sharedConfig()->FONT_SCALE);
    lTitle->setColor(ccc3(255,255,255));
    lTitle->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->SETTING_MARGIN_TOP));
    this->addChild(lTitle,11);
    CCSprite* wood = CCSprite::spriteWithSpriteFrameName(WOOD_PNG.c_str());
    wood->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->WOOD_MARGEN));
    this->addChild(wood, 10, WOOD_TAG);
    CCSprite* pBackToMenu = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BACK.c_str());
    pBackToMenu->setPosition( CCPoint(Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN * 17, Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN) );
    wood->addChild(pBackToMenu, 11, BUTTON5_TAG);
    CCNode* textNode = CCNode::node();
    stringstream ss(Config::sharedConfig()->LANG_DEVELOPERS);
    string s;
    int i = 0;
    while (getline(ss,s,'\n')) {
        CCLabelBMFont* lCredits = CCLabelBMFont::labelWithString(std::string(s).c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        lCredits->setScale(0.7);
        lCredits->setColor(ccc3(rand()%100,rand()%100,rand()%100));
        lCredits->setPosition(Geometry::getScreenUpCenter().x, Geometry::getScreenUpCenter().y-Config::sharedConfig()->TILE_HEIGHT*(3+i*1.4));
        i++;
        lCredits->setOpacity(0);
        lCredits->setScale(1);
        lCredits->runAction( CCSequence::actions(CCMoveBy::actionWithDuration(i * 1, CCPointZero), CCFadeIn::actionWithDuration(0.5), CCScaleTo::actionWithDuration(0.5, 0.7), NULL));
        textNode->addChild(lCredits,3);
    }
    this->addChild(textNode, 3);
    for (int i = 0; i < 20; i++) {
        int cloudType = (rand()%3) + 1;
        CCSprite* cloud;
        switch (cloudType) {
            case 1:
                cloud = CCSprite::spriteWithSpriteFrameName(CLOUD_A.c_str());
                break;
            case 2:
                cloud = CCSprite::spriteWithSpriteFrameName(CLOUD_B.c_str());
                break;
            case 3:
                cloud = CCSprite::spriteWithSpriteFrameName(CLOUD_C.c_str());
                break;
            default:
                cloud = CCSprite::spriteWithSpriteFrameName(CLOUD_A.c_str());
                break;
        }
        if((rand()%1) + 1) {
            cloud->setFlipX(true);
        }
        int randSpeed = (rand()%40)+10;
        cloud->setPosition(Geometry::getCloudOrigin(-1));
        CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(randSpeed,Geometry::getCloudEnd(cloud->getContentSize().width, cloud->getPosition().y));
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget( cloud, callfuncN_selector(CreditsScene::reloopCloud));
        cloud->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
        this->addChild(cloud,2);
    }
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    //ipad fix
    if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
        Border* border = new Border();
        this->addChild(border, 999);
    }
    return true;
}

void CreditsScene::backToTitle(CCObject* pSender) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER2.c_str()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(0.5, MenuScene::scene()));
}


bool CreditsScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint location = this->convertTouchToNodeSpace(pTouch);
    CCSprite* wood = (CCSprite*)this->getChildByTag(WOOD_TAG);
    CCSprite* pBackToMenu = (CCSprite*)wood->getChildByTag(BUTTON5_TAG);
    if(Geometry::nodeContainsTouch(pBackToMenu, wood->convertToNodeSpace(location))) {
        pBackToMenu->setColor(ccc3(200,200,200));
        this->backToTitle(pBackToMenu);
        return true;
    }
    return false;
}

void CreditsScene::reloopCloud(CCNode* cloudObj) {
    CCSprite* cloud = (CCSprite*)cloudObj;
    int randSpeed = (rand()%40)+10;
    cloud->setPosition(Geometry::getCloudOrigin(0));
    CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(randSpeed,Geometry::getCloudEnd(cloud->getContentSize().width, cloud->getPosition().y));
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget( cloud, callfuncN_selector(MenuScene::reloopCloud));
    cloud->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
}
