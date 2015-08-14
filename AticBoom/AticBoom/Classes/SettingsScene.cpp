//
//  SettingsScene.cpp
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

#include "SettingsScene.h"

SettingsScene::SettingsScene() : SettingsScene::CCLayer() {
}

SettingsScene::~SettingsScene() {
}

void SettingsScene::onEnter() {
    CCLayer::onEnter();
}

void SettingsScene::onExit() {
    CCLayer::onExit();
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*)this->getChildByTag(BATCH_MENU_TAG);
    this->removeChildByTag(BATCH_MENU_TAG, true);
    batch->release();
    CCSpriteBatchNode* batchBlack = (CCSpriteBatchNode*)this->getChildByTag(BATCH_BLACK_TAG);
    this->removeChildByTag(BATCH_BLACK_TAG, true);
    batchBlack->release();
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

void SettingsScene::keyBackClicked() {
    this->backToTitle(NULL);
}

CCScene* SettingsScene::scene() {
    CCScene *scene = CCScene::node();
    SettingsScene *layer = SettingsScene::node();
    scene->addChild(layer, 0, 1);
    return scene;
}

bool SettingsScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled(true);
    CCDirector::sharedDirector()->resume();
    confirmationMode = false;
    CCSpriteBatchNode* batch = new CCSpriteBatchNode();
    batch->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->MENU_PNG.c_str()), 28);
    this->addChild(batch, 0, BATCH_MENU_TAG);
    CCSpriteBatchNode* batchBlack = new CCSpriteBatchNode();
    batchBlack->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->BLACK_PNG.c_str()), 1);
    this->addChild(batchBlack, 0, BATCH_BLACK_TAG);
    CCSprite* seaSprite = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BG.c_str());
    seaSprite->setPosition(Geometry::getScreenCenter());
    this->addChild(seaSprite, 1);
    CCParticleSystemPoint* shine = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->WORLD_BURNING_PARTICLE.c_str());
    shine->setPosition( Geometry::getScreenCenter() );
    this->addChild(shine, 1);
    CCLabelBMFont* lTitle = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_SETTINGS.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    lTitle->setColor(ccc3(255,255,255));
    lTitle->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->SETTING_MARGIN_TOP));
    this->addChild(lTitle,11);
    CCSprite* wood = CCSprite::spriteWithSpriteFrameName(WOOD_PNG.c_str());
    wood->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->WOOD_MARGEN));
    this->addChild(wood, 10, WOOD_TAG);
    CCSprite* pBackToMenu = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BACK.c_str());
    pBackToMenu->setPosition( CCPoint(Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN * 17, Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN) );
    wood->addChild(pBackToMenu, 11, BUTTON5_TAG);
    CCSprite *bMusic;
    if (SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        bMusic = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
        CCLabelBMFont* label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_MUSICON.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        label->setColor(ccc3(50,50,50));
        label->setScale(0.7);
        label->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
        bMusic->addChild(label, 0, 1);
        soundstate = 1;
    } else {
        bMusic = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
        CCLabelBMFont* label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_MUSICOFF.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        label->setColor(ccc3(50,50,50));
        label->setScale(0.7);
        label->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
        bMusic->addChild(label, 0, 1);
        soundstate = 0;
    }
    bMusic->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->SETTING_MENU_FIRST_ROW));
    this->addChild(bMusic, 3, MUSIC_TAG);
    CCSprite *bFx;
    if (SimpleAudioEngine::sharedEngine()->getEffectsVolume() > 0) {
        bFx = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
        CCLabelBMFont* label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_FXON.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        label->setColor(ccc3(50,50,50));
        label->setScale(0.7);
        label->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
        bFx->addChild(label, 0, 1);
        fxstate = 1;
    } else {
        bFx = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
        CCLabelBMFont* label = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_FXOFF.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        label->setColor(ccc3(50,50,50));
        label->setScale(0.7);
        label->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
        bFx->addChild(label, 0, 1);
        fxstate =0;
    }
    bFx->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->SETTING_MENU_SECOND_ROW));
    this->addChild(bFx, 3, FX_TAG);
    CCSprite *bDelete = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
    CCLabelBMFont* lDelete = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_RESET.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    lDelete->setColor(ccc3(50,50,50));
    lDelete->setScale(0.7);
    lDelete->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
    bDelete->addChild(lDelete, 0, 1);
    bDelete->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->SETTING_MENU_THIRD_ROW));
    this->addChild(bDelete, 3,DELETE_TAG);
    CCSprite* bBlack = CCSprite::spriteWithSpriteFrameName(BLACK_PNG.c_str());
    bBlack->setScale(100);
    bBlack->setOpacity(0);
    bBlack->setPosition(Geometry::getScreenCenter());
    this->addChild(bBlack,9,BG_CONFIRM_TAG);
    CCSprite* sMiniScroll = CCSprite::spriteWithSpriteFrameName(MINISCROLL_PNG.c_str());
    sMiniScroll->setPosition(Geometry::getScreenCenter());
    sMiniScroll->setOpacity(0);
    this->addChild(sMiniScroll,10,CONFIRM_WINDOW_TAG);
    CCSprite* bYesConfirm = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
    CCLabelBMFont* yesLabel = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_YES.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    yesLabel->setColor(ccc3(50,50,50));
    yesLabel->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
    bYesConfirm->addChild(yesLabel, 0, 1);
    bYesConfirm->setPosition(CCPoint(Config::sharedConfig()->MINI_SCROLL_WIDTH/2,Config::sharedConfig()->MINI_SCROLL_HEIGHT/2));
    yesLabel->setOpacity(0);
    bYesConfirm->setOpacity(0);
    bYesConfirm->setScale(0.6);
    sMiniScroll->addChild(bYesConfirm,1,1);
    CCSprite* bNoConfirm = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
    CCLabelBMFont* noLabel = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_NO.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    noLabel->setColor(ccc3(50,50,50));
    noLabel->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
    bNoConfirm->addChild(noLabel, 0, 1);
    bNoConfirm->setPosition(CCPoint(Config::sharedConfig()->MINI_SCROLL_WIDTH/2,Config::sharedConfig()->MINI_SCROLL_HEIGHT/3.8));
    noLabel->setOpacity(0);
    bNoConfirm->setOpacity(0);
    bNoConfirm->setScale(0.6);
    sMiniScroll->addChild(bNoConfirm,1,2);
    CCLabelBMFont* sureLabel = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_SURE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    sureLabel->setScale(0.6);
    sureLabel->setColor(ccc3(50,50,50));
    sureLabel->setOpacity(0);
    sureLabel->setPosition(CCPoint(Config::sharedConfig()->MINI_SCROLL_WIDTH/2,Config::sharedConfig()->MINI_SCROLL_HEIGHT/1.4));
    sMiniScroll->addChild(sureLabel,1,3);
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
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget( cloud, callfuncN_selector(SettingsScene::reloopCloud));
        cloud->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
        this->addChild(cloud,2);
    }
    CCLabelBMFont* storeLabel = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_STORE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    storeLabel->setColor(ccc3(50,50,50));
    storeLabel->setOpacity(0);
    storeLabel->setScale(0.7);
    storeLabel->setPosition(CCPoint(Config::sharedConfig()->MINI_SCROLL_WIDTH/2,Config::sharedConfig()->MINI_SCROLL_HEIGHT/2));
    sMiniScroll->addChild(storeLabel,1,4);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    //ipad fix
    if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
        Border* border = new Border();
        this->addChild(border, 999);
    }
    return true;
}

void SettingsScene::backToTitle(CCObject* pSender) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER2.c_str()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(0.5, MenuScene::scene()));
}

void SettingsScene::toggleMusic(CCObject* pSender) {
    CCSprite* menuItem = (CCSprite*)pSender;
    CCLabelBMFont* label1 = (CCLabelBMFont*)menuItem->getChildByTag(1);
    if(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
        label1->setString(Config::sharedConfig()->LANG_MUSICOFF.c_str());
        soundstate = 0;
    } else {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MUSIC_VOLUME);
        label1->setString(Config::sharedConfig()->LANG_MUSICON.c_str());
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MUSIC_MENU.c_str(), true);
        soundstate = 1;
    }
    saveSettings();
}

void SettingsScene::toggleFx(CCObject* pSender) {
    CCSprite* menuItem = (CCSprite*)pSender;
    CCLabelBMFont* label1 = (CCLabelBMFont*)menuItem->getChildByTag(1);
    if(SimpleAudioEngine::sharedEngine()->getEffectsVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
        label1->setString(Config::sharedConfig()->LANG_FXOFF.c_str());
        fxstate = 0;
    } else {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1);
        label1->setString(Config::sharedConfig()->LANG_FXON.c_str());
        fxstate = 1;
    }
    saveSettings();
}

void SettingsScene::showConfirmation() {
    confirmationMode = true;
    CCSprite* background = (CCSprite*) this->getChildByTag(BG_CONFIRM_TAG);
    CCSprite* confirmWindow = (CCSprite*) this->getChildByTag(CONFIRM_WINDOW_TAG);
    CCSprite* bYes = (CCSprite*) confirmWindow->getChildByTag(1);
    CCLabelBMFont* lYes = (CCLabelBMFont*) bYes->getChildByTag(1);
    CCSprite* bNo = (CCSprite*) confirmWindow->getChildByTag(2);
    CCLabelBMFont* lNo = (CCLabelBMFont*) bNo->getChildByTag(1);
    CCLabelBMFont* lSure = (CCLabelBMFont*) confirmWindow->getChildByTag(3);
    background->setOpacity(255);
    confirmWindow->setOpacity(255);
    lSure->setOpacity(255);
    bYes->setOpacity(255);
    lYes->setOpacity(255);
    bNo->setOpacity(255);
    lNo->setOpacity(255);
}

void SettingsScene::hideConfirmation() {
    CCSprite* background = (CCSprite*) this->getChildByTag(BG_CONFIRM_TAG);
    CCSprite* confirmWindow = (CCSprite*) this->getChildByTag(CONFIRM_WINDOW_TAG);
    CCSprite* bYes = (CCSprite*) confirmWindow->getChildByTag(1);
    CCLabelBMFont* lYes = (CCLabelBMFont*) bYes->getChildByTag(1);
    CCSprite* bNo = (CCSprite*) confirmWindow->getChildByTag(2);
    CCLabelBMFont* lNo = (CCLabelBMFont*) bNo->getChildByTag(1);
    CCLabelBMFont* lSure = (CCLabelBMFont*) confirmWindow->getChildByTag(3);
    background->setOpacity(0);
    confirmWindow->setOpacity(0);
    lSure->setOpacity(0);
    bYes->setOpacity(0);
    lYes->setOpacity(0);
    bNo->setOpacity(0);
    lNo->setOpacity(0);
    confirmationMode = false;
}

void SettingsScene::eraseData(CCObject* pSender) {
    {
        char fileName [1024];
        sprintf (fileName, LEVELS_JSON.c_str(), CCFileUtils::getWriteablePath().c_str());
        Json::Value root;
        string fullPath = CCFileUtils::fullPathFromRelativePath(INITLEVELS_JSON.c_str());
        unsigned long bufferSizeI = 0;
        unsigned char * dataI =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
        char * ca = (char *) dataI;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), root);
        delete dataI;
        Json::StyledWriter writer;
        std::string outputString = writer.write(root);
        ofstream file;
        file.open(fileName);
        file << outputString;
        file.close();
    }
    {
        char fileName [1024];
        sprintf (fileName, SCORE_JSON.c_str(), CCFileUtils::getWriteablePath().c_str());
        Json::Value root;
        string fullPath = CCFileUtils::fullPathFromRelativePath(INITSCORE_JSON.c_str());
        unsigned long bufferSizeI = 0;
        unsigned char * dataI =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
        char * ca = (char *) dataI;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), root);
        delete dataI;
        Json::StyledWriter writer;
        std::string outputString = writer.write(root);
        ofstream file;
        file.open(fileName);
        file << outputString;
        file.close();
    }
    hideConfirmation();
}

void SettingsScene::saveSettings() {
    char fileName [1024];
    sprintf (fileName, SETTINGS_JSON.c_str(), CCFileUtils::getWriteablePath().c_str());
    Json::Value root;
    unsigned long bufferSize = 0;
    unsigned char * uc =  CCFileUtils::getFileData(fileName,"a+", &bufferSize);
    if(bufferSize > 0) {
        char * ca = (char *) uc;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), root);
    }
    else {
        string fullPath = CCFileUtils::fullPathFromRelativePath(INITSETTINGS_JSON.c_str());
        unsigned long bufferSizeI = 0;
        unsigned char * dataI =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
        char * ca = (char *) dataI;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), root);
        delete dataI;
    }
    delete uc;
    root["settings"]["sound"] = soundstate;
    root["settings"]["fx"] = fxstate;
    Json::StyledWriter writer;
    std::string outputString = writer.write(root);
    ofstream file;
    file.open(fileName);
    file << outputString;
    file.close();
}


bool SettingsScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint location = this->convertTouchToNodeSpace(pTouch);
    if ( !confirmationMode ) {
        CCSprite* wood = (CCSprite*)this->getChildByTag(WOOD_TAG);
        CCSprite* pBackToMenu = (CCSprite*)wood->getChildByTag(BUTTON5_TAG);
        if(Geometry::nodeContainsTouch(pBackToMenu, wood->convertToNodeSpace(location))) {
            pBackToMenu->setColor(ccc3(200,200,200));
            this->backToTitle(pBackToMenu);
            return true;
        }
        CCSprite* button1 = (CCSprite*)this->getChildByTag(MUSIC_TAG);
        if(Geometry::nodeContainsTouch(button1, location)) {
            this->toggleMusic(button1);
            return true;
        }
        CCSprite* button2 = (CCSprite*)this->getChildByTag(FX_TAG);
        if(Geometry::nodeContainsTouch(button2, location)) {
            this->toggleFx(button2);
            return true;
        }
        CCSprite* button3 = (CCSprite*)this->getChildByTag(DELETE_TAG);
        if(Geometry::nodeContainsTouch(button3, location)) {
            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
            this->showConfirmation();
            return true;
        }
    } else {
        CCSprite* tinyScroll = (CCSprite*) this->getChildByTag(CONFIRM_WINDOW_TAG);
        CCSprite* button4 = (CCSprite*)this->getChildByTag(CONFIRM_WINDOW_TAG)->getChildByTag(1);
        if(Geometry::nodeContainsTouch(button4, tinyScroll->convertToNodeSpace(location))) {
            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
            this->eraseData(button4);
            return true;
        }
        CCSprite* button5 = (CCSprite*)this->getChildByTag(CONFIRM_WINDOW_TAG)->getChildByTag(2);
        if(Geometry::nodeContainsTouch(button5, tinyScroll->convertToNodeSpace(location))) {
            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
            this->hideConfirmation();
            return true;
        }
    }
    return false;
}

void SettingsScene::reloopCloud(CCNode* cloudObj) {
    CCSprite* cloud = (CCSprite*)cloudObj;
    int randSpeed = (rand()%40)+10;
    cloud->setPosition(Geometry::getCloudOrigin(0));
    CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(randSpeed,Geometry::getCloudEnd(cloud->getContentSize().width, cloud->getPosition().y));
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget( cloud, callfuncN_selector(MenuScene::reloopCloud));
    cloud->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
}


