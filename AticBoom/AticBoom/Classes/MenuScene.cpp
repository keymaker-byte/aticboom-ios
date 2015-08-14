//
//  MenuScene.cpp
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

#include "MenuScene.h"

MenuScene::MenuScene() : MenuScene::CCLayer() {
}

MenuScene::~MenuScene() {
}

void MenuScene::onEnter() {
    CCLayer::onEnter();
}

void MenuScene::onExit() {
    CCLayer::onExit();
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*)this->getChildByTag(BATCH_MENU_TAG);
    this->removeChildByTag(BATCH_MENU_TAG, true);
    batch->release();
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

void MenuScene::keyBackClicked() {
    CCDirector::sharedDirector()->end();
}

CCScene* MenuScene::scene() {
    CCScene *scene = CCScene::node();
    MenuScene *layer = MenuScene::node();
    scene->addChild(layer, 0, 1);
    return scene;
}

bool MenuScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled(true);
    CCDirector::sharedDirector()->resume();
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()  && SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_MENU.c_str(), true);
    }
    CCSpriteBatchNode* batch = new CCSpriteBatchNode();
    batch->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->MENU_PNG.c_str()), 28);
    this->addChild(batch, 0, BATCH_MENU_TAG);
    CCSprite* seaSprite = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BG.c_str());
    seaSprite->setPosition(Geometry::getScreenCenter());
    this->addChild(seaSprite, 1);
    CCSprite* title = CCSprite::spriteWithSpriteFrameName(TITLE_PNG.c_str());
    title->setPosition(Geometry::getScreenUpCenter(-Config::sharedConfig()->MENU_WORLD_TITLE_MARGEN*2));
    title->runAction(CCSequence::actions(CCMoveBy::actionWithDuration(0.6, CCPointZero), CCMoveTo::actionWithDuration(0.5, Geometry::getScreenUpCenter(Config::sharedConfig()->MENU_WORLD_TITLE_MARGEN)), NULL));
    this->addChild(title, 5);
    for (int i = 0; i < 6; i++) {
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
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget( cloud, callfuncN_selector(MenuScene::reloopCloud));
        cloud->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
        this->addChild(cloud,2);
    }
    CCSprite* water = CCSprite::spriteWithSpriteFrameName(WORLD_WATER.c_str());
    water->setPosition(Geometry::getScreenBotomCenter(Config::sharedConfig()->MENU_WORLD_WATER_MARGEN));
    this->addChild(water, 1);
    CCParticleSystemPoint* shine = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->WORLD_BURNING_PARTICLE.c_str());
    shine->setPosition( Geometry::getScreenCenter() );
    this->addChild(shine, 1);
    CCParticleSystemPoint* waterpart1 = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->WATER_PARTICLE.c_str());
    waterpart1->setPosition(Geometry::getScreenBotomCenter(Config::sharedConfig()->MENU_KID_WATER_MARGIN));
    this->addChild(waterpart1, 5);
    CCNode* kidRote = new CCNode();
    CCNode* kidNode = new CCNode();
    CCSprite* kidSprite = CCSprite::spriteWithSpriteFrameName(KID_PNG.c_str());
    kidSprite->setPosition(Geometry::getScreenBotomLeft(Config::sharedConfig()->MENU_KID_MARGEN_LEFT, Config::sharedConfig()->MENU_KID_MARGEN_BOTTOM));
    CCFiniteTimeAction* actionA = CCMoveBy::actionWithDuration(2, CCPoint(0,Config::sharedConfig()->MENU_KID_MOVE_VERT));
    CCFiniteTimeAction* actionB = CCMoveBy::actionWithDuration(2, CCPoint(0,-2*Config::sharedConfig()->MENU_KID_MOVE_VERT));
    CCFiniteTimeAction* actionC = CCMoveBy::actionWithDuration(2, CCPoint(0,Config::sharedConfig()->MENU_KID_MOVE_VERT));
    CCFiniteTimeAction* secuenceA = CCSequence::actions(actionA, actionB, actionC, NULL);
    kidNode->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)secuenceA));
    CCFiniteTimeAction* actionD = CCMoveBy::actionWithDuration(1, CCPoint(-Config::sharedConfig()->MENU_KID_MOVE_HOR,0));
    CCFiniteTimeAction* actionE = CCMoveBy::actionWithDuration(2, CCPoint(2*Config::sharedConfig()->MENU_KID_MOVE_HOR,0));
    CCFiniteTimeAction* actionF = CCMoveBy::actionWithDuration(1, CCPoint(-Config::sharedConfig()->MENU_KID_MOVE_HOR,0));
    CCFiniteTimeAction* secuenceB = CCSequence::actions(actionD, actionE, actionF, NULL);
    kidSprite->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)secuenceB));
    CCFiniteTimeAction* actionG = CCRotateBy::actionWithDuration(2, -Config::sharedConfig()->MENU_KID_ROT);
    CCFiniteTimeAction* actionH = CCRotateBy::actionWithDuration(4, 2*Config::sharedConfig()->MENU_KID_ROT);
    CCFiniteTimeAction* actionI = CCRotateBy::actionWithDuration(2, -Config::sharedConfig()->MENU_KID_ROT);
    CCFiniteTimeAction* secuenceC = CCSequence::actions(actionG, actionH, actionI, NULL);
    kidRote->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)secuenceC));
    kidNode->addChild(kidSprite);
    kidRote->addChild(kidNode);
    this->addChild(kidRote, 5);
    CCParticleSystemPoint* waterpart2 = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->WATER_PARTICLE.c_str());
    waterpart2->setPosition(Geometry::getScreenBotomCenter(-Config::sharedConfig()->MENU_KID_WATER_MARGIN));
    this->addChild(waterpart2, 5);
    CCNode* anchorNode = new CCNode();
    anchorNode->setPosition(Geometry::getScreenUpCenter());
    CCSprite* shipeSprite = CCSprite::spriteWithSpriteFrameName(WORLD_ANCHOR.c_str());
    shipeSprite->setPosition(CCPoint(0, Config::sharedConfig()->MENU_MAIN_ANCHOR_MARGEN * 2));
    shipeSprite->runAction(CCSequence::actions(CCMoveBy::actionWithDuration(0.5, CCPointZero), CCMoveTo::actionWithDuration(0.3, CCPoint(0, -Config::sharedConfig()->MENU_MAIN_ANCHOR_MARGEN)), NULL));
    CCActionInterval* secuenceAnchor = (CCActionInterval*)CCSequence::actions(CCRotateBy::actionWithDuration(2, 1), CCRotateBy::actionWithDuration(1, -1), CCRotateBy::actionWithDuration(2, -1), CCRotateBy::actionWithDuration(1, 1), NULL);
    anchorNode->runAction(CCRepeatForever::actionWithAction(secuenceAnchor));
    anchorNode->addChild(shipeSprite, 3);
    this->addChild(anchorNode, 3);
    CCSprite* button1 = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON1.c_str());
    CCLabelBMFont* label1 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_PLAY.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    label1->setScale(Config::sharedConfig()->FONT_SCALE);
    label1->setColor(ccc3(50,50,50));
    label1->setPosition(CCPoint(Config::sharedConfig()->MENU_MAIN_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_MAIN_BUTTON_HEIGHT/2));
    CCSprite* PChar = (CCSprite*) label1->getChildByTag(0);
    PChar->setPosition(CCPoint( PChar->getPosition().x,PChar->getPosition().y+1));
    CCSprite* YChar = (CCSprite*) label1->getChildByTag(label1->getChildrenCount()-1);
    YChar->setPosition(CCPoint(YChar->getPosition().x,YChar->getPosition().y+1));
    button1->addChild(label1, 0, 1);
    button1->setPosition(Geometry::getScreenBotomCenter(Config::sharedConfig()->MENU_MAIN_BUTTON_MARGEN));
    this->addChild(button1, 4, BUTTON1_TAG);
    CCSprite* button2 = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
    CCLabelBMFont* label2 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_SETTINGS.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    label2->setScale(0.9);
    label2->setColor(ccc3(50,50,50));
    label2->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
    Geometry::curveText(label2);
    button2->addChild(label2, 0, 1);
    button2->setPosition(Geometry::getScreenBotomCenter(Config::sharedConfig()->MENU_SETTINGS_BUTTON_MARGEN));
    this->addChild(button2, 4, BUTTON2_TAG);
    CCSprite* button4 = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
    CCLabelBMFont* label4 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_CREDITS.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    label4->setScale(0.9);
    label4->setColor(ccc3(50,50,50));
    label4->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
    Geometry::curveText(label4);
    button4->addChild(label4, 0, 1);
    button4->setPosition(Geometry::getScreenBotomCenter(Config::sharedConfig()->MENU_HELP_BUTTON_MARGEN));
    this->addChild(button4, 4, BUTTON4_TAG);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    //ipad fix
    if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
        Border* border = new Border();
        this->addChild(border, 999);
    }
    return true;
}

void MenuScene::startAticGame(CCObject* pSender) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER1.c_str()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, WorldSelectScene::scene(1)));
}

void MenuScene::moveAnchor(CCNode* anchorSprite) {
    CCActionInterval* secuence = (CCActionInterval*)CCSequence::actions(CCRotateBy::actionWithDuration(1, 5), CCRotateBy::actionWithDuration(1, -5), CCRotateBy::actionWithDuration(1, -5), CCRotateBy::actionWithDuration(1, 5), NULL);
    anchorSprite->runAction(CCRepeatForever::actionWithAction(secuence));
}

void MenuScene::goToSettings(CCObject* pSender) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER1.c_str()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(0.5, SettingsScene::scene()));
}

void MenuScene::goToCredits(CCObject* pSender) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER1.c_str()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(0.5, CreditsScene::scene()));
}


void MenuScene::reloopCloud(CCNode* cloudObj) {
    CCSprite* cloud = (CCSprite*)cloudObj;
    int randSpeed = (rand()%40)+10;
    cloud->setPosition(Geometry::getCloudOrigin(0));
    CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(randSpeed,Geometry::getCloudEnd(cloud->getContentSize().width, cloud->getPosition().y));
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget( cloud, callfuncN_selector(MenuScene::reloopCloud));
    cloud->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
}

bool MenuScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint location = this->convertTouchToNodeSpace(pTouch);
    CCSprite* button1 = (CCSprite*)this->getChildByTag(BUTTON1_TAG);
    CCLabelBMFont* label1 = (CCLabelBMFont*)button1->getChildByTag(1);
    if(Geometry::nodeContainsTouch(button1, location)) {
        button1->setColor(ccc3(200,200,200));
        label1->setColor(ccc3(50,50,50));
        this->startAticGame(button1);
        return true;
    }
    CCSprite* button2 = (CCSprite*)this->getChildByTag(BUTTON2_TAG);
    CCLabelBMFont* label2 = (CCLabelBMFont*)button2->getChildByTag(1);
    if(Geometry::nodeContainsTouch(button2, location)) {
        button2->setColor(ccc3(200,200,200));
        label2->setColor(ccc3(50,50,50));
        this->goToSettings(button2);
        return true;
    }
    CCSprite* button4 = (CCSprite*)this->getChildByTag(BUTTON4_TAG);
    CCLabelBMFont* label4 = (CCLabelBMFont*)button4->getChildByTag(1);
    if(Geometry::nodeContainsTouch(button4, location)) {
        button4->setColor(ccc3(200,200,200));
        label4->setColor(ccc3(50,50,50));
        this->goToCredits(button4);
        return true;
    }
    return true;
}


