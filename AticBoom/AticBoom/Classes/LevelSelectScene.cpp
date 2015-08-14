//
//  LevelSelectScene.cpp
//  AticBoom
//
//  Created by Claudio Alvial on 1/11/12.
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

#include "LevelSelectScene.h"

LevelSelectScene::LevelSelectScene() : LevelSelectScene::CCLayer() {
}

LevelSelectScene::~LevelSelectScene() {
}

void LevelSelectScene::onEnter() {
    CCLayer::onEnter();
}

void LevelSelectScene::onExit() {
    CCLayer::onExit();
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*)this->getChildByTag(BATCH_MENU_TAG);
    this->removeChildByTag(BATCH_MENU_TAG, true);
    batch->release();
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    if(cleanAfterExit) {
        cocos2d::CCDirector::sharedDirector()->purgeCachedData();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
}

void LevelSelectScene::keyBackClicked() {
    this->goToWorld(NULL);
}

CCScene* LevelSelectScene::scene(int worldId) {
    CCScene *scene = CCScene::node();
    LevelSelectScene *layer = LevelSelectScene::node(worldId);
    scene->addChild(layer, 0, 1);
    return scene;
}

bool LevelSelectScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled(true);
    CCDirector::sharedDirector()->resume();
    CCSpriteBatchNode* batch = new CCSpriteBatchNode();
    batch->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->MENU_PNG.c_str()), 28);
    this->addChild(batch, 0, BATCH_MENU_TAG);
    cleanAfterExit = false;
    CCSprite* seaSprite = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BG.c_str());
    seaSprite->setPosition(Geometry::getScreenCenter());
    this->addChild(seaSprite, 1);
    CCSprite* water = CCSprite::spriteWithSpriteFrameName(WORLD_WATER.c_str());
    water->setPosition(Geometry::getScreenBotomCenter(Config::sharedConfig()->MENU_WORLD_WATER_MARGEN));
    this->addChild(water, 1);
    CCParticleSystemPoint* shine = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->WORLD_BURNING_PARTICLE.c_str());
    shine->setPosition( Geometry::getScreenCenter() );
    this->addChild(shine, 1);
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
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget( cloud, callfuncN_selector(WorldSelectScene::reloopCloud));
        cloud->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
        this->addChild(cloud,2);
    }
    CCSprite* map = CCSprite::spriteWithSpriteFrameName(MAP_PNG.c_str());
    map->setPosition(Geometry::getScreenCenter());
    this->addChild(map, 3);
    string fullPath = CCFileUtils::fullPathFromRelativePath(WORLDS_JSON.c_str());
    unsigned long bufferSizeW = 0;
    unsigned char * dataW =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeW);
    char * ca = (char *) dataW;
    string buffer = string(ca);
    Json::Value rootW;
    Json::Reader reader;
    reader.parse(buffer.c_str(), rootW);
    delete dataW;
    int levels = rootW["worlds"][worldId - 1]["levels"].asInt();
    string worldName = rootW["worlds"][worldId - 1]["name"].asString();
    char fileName [1024];
    sprintf (fileName, LEVELS_JSON.c_str(), CCFileUtils::getWriteablePath().c_str());
    Json::Value rootL;
    unsigned long bufferSizeL = 0;
    unsigned char * dataL =  CCFileUtils::getFileData(fileName,"a+", &bufferSizeL);
    if(bufferSizeL > 0) {
        char * ca = (char *) dataL;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), rootL);
    }
    delete dataL;
    sprintf (fileName, SCORE_JSON.c_str(), CCFileUtils::getWriteablePath().c_str());
    Json::Value rootS;
    unsigned long bufferSizeS = 0;
    unsigned char * dataS =  CCFileUtils::getFileData(fileName,"a+", &bufferSizeS);
    if(bufferSizeS > 0) {
        char * ca = (char *) dataS;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), rootS);
    }
    delete dataS;
    char currentWorld [5];
    sprintf(currentWorld,"%d",worldId);
    for( int i = 0; i < levels; i++){
        states[i] = 3;
    }
    if(rootL != NULL) {
        for( int i = 0; i < rootL[currentWorld].size(); i++){
            char levelIndex [5];
            sprintf(levelIndex,"%d",i+1);
            states[i] = rootL[currentWorld][levelIndex].asInt();
            if(states[i] == 1 || states[i] == 2) {
                states[i] = 4 + rootS["score"]["STARS"][currentWorld][levelIndex].asInt();
            }
        }
    }
    if(states[1] == 3) {
        states[0] = 0;
    }
    int counter = 0;
    float xPos = 0.25;
    float yPos = 0.60;
    for ( int i = 0; i < 4; ++i ) {
        if (counter == levels) {
            break;
        }
        for ( int j = 0; j < 4; ++j) {
            CCSprite *pWorldIcon;
            if ( states[counter] == 0 ) {
                pWorldIcon = CCSprite::spriteWithSpriteFrameName(SQUARE_BUTTON_A.c_str());
            }else if ( states[counter] == 3 ) {
                pWorldIcon = CCSprite::spriteWithSpriteFrameName(SQUARE_BUTTON_E.c_str());
            } else if ( states[counter] == 4 ) {
                pWorldIcon = CCSprite::spriteWithSpriteFrameName(SQUARE_BUTTON_A.c_str());
            } else if ( states[counter] == 5 ) {
                pWorldIcon = CCSprite::spriteWithSpriteFrameName(SQUARE_BUTTON_B.c_str());
            } else if ( states[counter] == 6 ) {
                pWorldIcon = CCSprite::spriteWithSpriteFrameName(SQUARE_BUTTON_C.c_str());
            } else if ( states[counter] == 7 ) {
                pWorldIcon = CCSprite::spriteWithSpriteFrameName(SQUARE_BUTTON_D.c_str());
            }
            pWorldIcon->setTag(LEVELGROUP_TAG + counter+1);
            pWorldIcon->setPosition( ccp(Config::sharedConfig()->SCREEN_WIDTH*xPos + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, Config::sharedConfig()->SCREEN_HEIGHT*yPos) );
            this->addChild(pWorldIcon, 4);
            char levelIndex [2];
            sprintf(levelIndex,"%d",counter + 1);
            CCLabelBMFont* label = CCLabelBMFont::labelWithString(levelIndex, Config::sharedConfig()->BMFONT_NAME.c_str());
            label->setScale(0.8);
            label->setColor(ccc3(255,255,255));
            label->setPosition(pWorldIcon->getContentSize().width/2, pWorldIcon->getContentSize().height/2);
            pWorldIcon->addChild(label);
            counter++;
            if (counter == levels) {
                break;
            }
            xPos += 0.20;
        }
        xPos = (i == 0 ? 0.20 : (i == 1 ? 0.17 : (i == 2 ? 0.15 : 0.25)));
        yPos -= 0.13;
    }
    CCLabelBMFont* label = CCLabelBMFont::labelWithString(worldName.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    label->setScale(0.65);
    label->setColor(ccc3(50,50,50));
    label->setPosition(Geometry::getScreenBotomLeft(Config::sharedConfig()->LEVEL_W_MARGIN_MARGIN, Config::sharedConfig()->MENU_LEVEL_TEXT_MARGEN));
    this->addChild(label, 11);
    CCSprite* knife = CCSprite::spriteWithSpriteFrameName("dagger.png");
    knife->setPosition(Geometry::getScreenUpLeft(Config::sharedConfig()->KNIFE_MARGINX,Config::sharedConfig()->KNIFE_MARGINY));
    this->addChild(knife, 11);
    CCSprite* wood = CCSprite::spriteWithSpriteFrameName(WOOD_PNG.c_str());
    wood->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->WOOD_MARGEN));
    this->addChild(wood, 10, WOOD_TAG);
    CCSprite* pBackToMenu = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BACK.c_str());
    pBackToMenu->setPosition( CCPoint(Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN * 17, Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN) );
    wood->addChild(pBackToMenu, 11, BUTTON5_TAG);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    //ipad fix
    if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
        Border* border = new Border();
        this->addChild(border, 999);
    }
    return true;
}

void LevelSelectScene::goToLevel(CCObject* pSender) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
    CCSprite* pLevelIcon = (CCSprite*)pSender;
    levelId = pLevelIcon->getTag() - LEVELGROUP_TAG;
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    if ( (worldId == 1) && (levelId == 1) ) {
        cleanAfterExit = true;
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, LoadingScene::scene(1,0)));
    } else {
        cleanAfterExit = true;
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, LoadingScene::scene(worldId, levelId)));
    }
}

void LevelSelectScene::goToWorld(CCObject* pSender) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER2.c_str()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, WorldSelectScene::scene(worldId)));
}


bool LevelSelectScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint location = this->convertTouchToNodeSpace(pTouch);
    CCSprite* wood = (CCSprite*)this->getChildByTag(WOOD_TAG);
    CCSprite* pBackToMenu = (CCSprite*)wood->getChildByTag(BUTTON5_TAG);
    if(Geometry::nodeContainsTouch(pBackToMenu, wood->convertToNodeSpace(location))) {
        pBackToMenu->setColor(ccc3(200,200,200));
        this->goToWorld(pBackToMenu);
        return true;
    }
    for(int i = 0; i < LEVELS_PER_WORLD; i++) {
        CCSprite* levelButton = (CCSprite*)this->getChildByTag(LEVELGROUP_TAG + i + 1);
        if(this->states[i] != 3 && Geometry::nodeContainsTouch(levelButton, location)) {
            levelButton->setColor(ccc3(200,200,200));
            levelButton->runAction(CCScaleBy::actionWithDuration(2, 2));
            this->goToLevel(levelButton);
            return true;
        }
    }
    return false;
}
