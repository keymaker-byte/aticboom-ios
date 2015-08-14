//
//  WorldSelectScene.cpp
//  AticBoom
//
//  Created by Claudio Alvial on 1/9/12.
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

#include "WorldSelectScene.h"

WorldSelectScene::WorldSelectScene() : WorldSelectScene::CCLayer() {
}

WorldSelectScene::~WorldSelectScene() {
}

void WorldSelectScene::onEnter() {
    CCLayer::onEnter();
}

void WorldSelectScene::onExit() {
    CCLayer::onExit();
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*)this->getChildByTag(BATCH_MENU_TAG);
    this->removeChildByTag(BATCH_MENU_TAG, true);
    batch->release();
    CCSpriteBatchNode* batchBlack = (CCSpriteBatchNode*)this->getChildByTag(BATCH_BLACK_TAG);
    this->removeChildByTag(BATCH_BLACK_TAG, true);
    batchBlack->release();
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

void WorldSelectScene::keyBackClicked() {
    if (!confirmationMode) {
        this->goToMenu(NULL);
    }
    else if(confirmationMode){
        this->hideConfirmation();
    }
}

CCScene* WorldSelectScene::scene(int worldId) {
    CCScene *scene = CCScene::node();
    WorldSelectScene *layer = WorldSelectScene::node(worldId);
    scene->addChild(layer, 0, 1);
    return scene;
}

bool WorldSelectScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled(true);
    CCDirector::sharedDirector()->resume();
    enabled = new bool[Config::sharedConfig()->TOTAL_WORLDS];
    confirmationMode = false;
    movingTouch = false;
    touchMoved = 0;
    worldTouch = 0;
    previousTouch = CCPointZero;
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying()) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::fullPathFromRelativePath(MUSIC_MENU.c_str()), true);
    }
    CCSpriteBatchNode* batch = new CCSpriteBatchNode();
    batch->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->MENU_PNG.c_str()), 28);
    this->addChild(batch, 0, BATCH_MENU_TAG);
    CCSpriteBatchNode* batchBlack = new CCSpriteBatchNode();
    batchBlack->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->BLACK_PNG.c_str()), 1);
    this->addChild(batchBlack, 0, BATCH_BLACK_TAG);
    CCSprite* seaSprite = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BG.c_str());
    seaSprite->setPosition(Geometry::getScreenCenter());
    this->addChild(seaSprite, 1);
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
    CCSprite* water = CCSprite::spriteWithSpriteFrameName(WORLD_WATER.c_str());
    water->setPosition(Geometry::getScreenBotomCenter(Config::sharedConfig()->MENU_WORLD_WATER_MARGEN));
    this->addChild(water, 2);
    CCParticleSystemPoint* shine = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->WORLD_BURNING_PARTICLE.c_str());
    shine->setPosition( Geometry::getScreenCenter() );
    this->addChild(shine, 2);
    unsigned long bufferSize = 0;
    string fullPath = CCFileUtils::fullPathFromRelativePath(WORLDS_JSON.c_str());
    unsigned char * uc =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSize);
    char * ca = (char *) uc;
    string buffer = string(ca);
    char * json = new char [buffer.size()+1];
    strcpy (json, buffer.c_str());
    Json::Value root;
    Json::Reader reader;
    reader.parse(buffer.c_str(), root);
    delete uc;
    CCMutableArray<CCLayer*> layerArray;
    char fileName [1024];
    sprintf (fileName, SCORE_JSON.c_str(), CCFileUtils::getWriteablePath().c_str());
    Json::Value sroot;
    unsigned long sbufferSize = 0;
    unsigned char * suc =  CCFileUtils::getFileData(fileName,"a+", &sbufferSize);
    if(sbufferSize > 0) {
        char * sca = (char *) suc;
        string sbuffer = string(sca);
        Json::Reader sreader;
        sreader.parse(sbuffer.c_str(), sroot);
    }
    else {
        string fullPath = CCFileUtils::fullPathFromRelativePath(INITSCORE_JSON.c_str());
        unsigned long bufferSizeI = 0;
        unsigned char * dataI =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
        char * sca = (char *) dataI;
        string sbuffer = string(sca);
        Json::Reader sreader;
        sreader.parse(sbuffer.c_str(), sroot);
        delete dataI;
    }
    delete suc;
    this->totalStar = 0;
    for (int index = 1; index <= Config::sharedConfig()->TOTAL_WORLDS; ++index) {
        for (int idx = 1; idx <= LEVELS_PER_WORLD; ++idx){
            char buff[5];
            char buff2[5];
            sprintf(buff, "%i",index);
            sprintf(buff2, "%i",idx);
            this->totalStar += sroot["score"]["STARS"][buff][buff2].asInt();
        }
    }
    Json::Value levels = this->readLevelsJson();
    const Json::Value worlds =  root["worlds"];
    this->totalGold = 0;
    for ( int index = 0; index < worlds.size(); ++index ) {
        bool night = Geometry::isNight(index + 1);
        char buffer [50];
        int worldIdIcon = worlds[index]["world"].asInt();
        if(night) {
            worldIdIcon--;
        }
        sprintf (buffer, ICON_WORLD.c_str(), worldIdIcon);
        int worldstate;
        CCSprite* currentMedal;
        int check = checkAllLevels(levels, index+1);
        if ( check == 1 ) {
            currentMedal = CCSprite::spriteWithSpriteFrameName(LEVEL_BUTTON_B.c_str());
            currentMedal->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->MENU_WORLD_MEDAL_MARGEN));
            worldstate = 1;
        } else if ( check == 2 ) {
            currentMedal = CCSprite::spriteWithSpriteFrameName(LEVEL_BUTTON_C.c_str());
            currentMedal->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->MENU_WORLD_MEDAL_MARGEN));
            worldstate = 2;
        }
        else if(this->totalStar >= worlds[index]["golden"].asInt()){
            currentMedal = CCSprite::spriteWithSpriteFrameName(LEVEL_BUTTON_A.c_str());
            currentMedal->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->MENU_WORLD_MEDAL_MARGEN));
            worldstate = 1;
        }
        else {
            worldstate = 3;
        }
        CCSprite* board = CCSprite::spriteWithSpriteFrameName(WORLD_BOARD.c_str());
        board->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->MENU_WORLD_BUTTON_MARGEN) );
        CCLabelBMFont* label = CCLabelBMFont::labelWithString(worlds[index]["name"].asString().c_str(),Config::sharedConfig()->BMFONT_NAME.c_str());
        label->setScale(0.6);
        label->setColor(ccc3(255,255,255));
        label->setPosition(Geometry::getScreenBotomCenter(Config::sharedConfig()->MENU_WORLD_TEXT_MARGEN));
        label->setTag(2);
        CCSprite* pWorldIcon = CCSprite::spriteWithSpriteFrameName(buffer);
        pWorldIcon->setPosition( Geometry::getScreenUpCenter(Config::sharedConfig()->MENU_WORLD_BUTTON_MARGEN) );
        pWorldIcon->setTag(1);
        if ( (worldstate == 3) && (index+1 != 1) )
            enabled[index] = false;
        else
            enabled[index] = true;
        if(night) {
            pWorldIcon->setColor(ccc3(NIGHT_COLOR_CORRECTOR_R, NIGHT_COLOR_CORRECTOR_G, NIGHT_COLOR_CORRECTOR_B));
        }
        if (worldstate == 2) {
            pWorldIcon->setColor(ccc3(GOLD_COLOR_CORRECTOR_R, GOLD_COLOR_CORRECTOR_G, GOLD_COLOR_CORRECTOR_B));
        }
        CCLayer* aLayer = CCLayer::node();
        aLayer->addChild(board, 1);
        aLayer->addChild(label, 2);
        aLayer->addChild(pWorldIcon, 3);
        aLayer->setTag(index+1);
        layerArray.addObject(aLayer);
        if(worldstate == 3) {
            CCSprite* chains = CCSprite::spriteWithSpriteFrameName(CHAINS_PNG.c_str());
            chains->setPosition(board->getPosition());
            CCLabelBMFont* lRequired = CCLabelBMFont::labelWithString("", Config::sharedConfig()->BMFONT_NAME.c_str());
            lRequired->setColor(ccc3(255,255,255));
            lRequired->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->MENU_WORLD_MEDAL_MARGEN_B));
            char text [30];
            sprintf(text,"%d",worlds[index]["golden"].asInt());
            lRequired->setString(text);
            aLayer->addChild(lRequired,100);
            aLayer->addChild(chains, 100);
        }
        else {
            aLayer->addChild(currentMedal,2);
        }
    }
    CCScrollLayer* pScrollLayer = CCScrollLayer::layerWithLayers(&layerArray, Config::sharedConfig()->WORLD_DELTA);
    pScrollLayer->setPosition(ccp(0,0));
    pScrollLayer->setTag(WORLD_SELECT_TAG);
    this->addChild(pScrollLayer,4);
    CCSprite* wood = CCSprite::spriteWithSpriteFrameName(WOOD_PNG.c_str());
    wood->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->WOOD_MARGEN));
    this->addChild(wood, 10, WOOD_TAG);
    CCSprite* pBackToMenu = CCSprite::spriteWithSpriteFrameName(WORLD_SELECT_BACK.c_str());
    pBackToMenu->setPosition( CCPoint(Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN * 17, Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN) );
    wood->addChild(pBackToMenu, 11, BUTTON5_TAG);
    CCSprite* sGoldenSkull = CCSprite::spriteWithSpriteFrameName(DOUBLON_WORLD.c_str());
    sGoldenSkull->setScale(0.7);
    sGoldenSkull->setPosition( CCPoint(Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN * 8, Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN) );
    CCLabelBMFont* lSkullNumber = CCLabelBMFont::labelWithString("", Config::sharedConfig()->BMFONT_NAME.c_str());
    lSkullNumber->setPosition( CCPoint(Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN * 10.5, Config::sharedConfig()->MENU_WORLD_ARROW_MARGEN) );
    char text [30];
    sprintf(text,"%i", totalStar);
    lSkullNumber->setString(text);
    wood->addChild(lSkullNumber);
    wood->addChild(sGoldenSkull);
    CCSprite* bBlack = CCSprite::spriteWithSpriteFrameName(BLACK_PNG.c_str());
    bBlack->setScale(100);
    bBlack->setOpacity(0);
    bBlack->setPosition(Geometry::getScreenCenter());
    this->addChild(bBlack,13,BG_CONFIRM_TAG);
    CCSprite* sMiniScroll = CCSprite::spriteWithSpriteFrameName(MINISCROLL_PNG.c_str());
    sMiniScroll->setPosition(Geometry::getScreenCenter());
    sMiniScroll->setOpacity(0);
    this->addChild(sMiniScroll,13,CONFIRM_WINDOW_TAG);
    CCSprite* sOtherSkull = CCSprite::spriteWithSpriteFrameName(DOUBLON_WORLD.c_str());
    sOtherSkull->setScale(0.7);
    sOtherSkull->setPosition(CCPoint(Config::sharedConfig()->MINI_SCROLL_WIDTH/2,Config::sharedConfig()->MINI_SCROLL_HEIGHT/1.1));
    sOtherSkull->setOpacity(0);
    sMiniScroll->addChild(sOtherSkull,1,1);
    CCLabelBMFont* enoughLabel = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_MORESKULLS.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    enoughLabel->setColor(ccc3(50,50,50));
    enoughLabel->setOpacity(0);
    enoughLabel->setScale(0.7);
    enoughLabel->setPosition(CCPoint(Config::sharedConfig()->MINI_SCROLL_WIDTH/2,Config::sharedConfig()->MINI_SCROLL_HEIGHT/2));
    sMiniScroll->addChild(enoughLabel,1,2);
    CCLabelBMFont* storeLabel = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_STORE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
    storeLabel->setColor(ccc3(50,50,50));
    storeLabel->setOpacity(0);
    storeLabel->setScale(0.7);
    storeLabel->setPosition(CCPoint(Config::sharedConfig()->MINI_SCROLL_WIDTH/2,Config::sharedConfig()->MINI_SCROLL_HEIGHT/2));
    sMiniScroll->addChild(storeLabel,1,3);
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    //ipad fix
    if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
        Border* border = new Border();
        this->addChild(border, 999);
    }
    pScrollLayer->moveToPage(worldId);
    return true;
}

void WorldSelectScene::showConfirmation() {
    confirmationMode = true;
    CCSprite* background = (CCSprite*) this->getChildByTag(BG_CONFIRM_TAG);
    CCSprite* confirmWindow = (CCSprite*) this->getChildByTag(CONFIRM_WINDOW_TAG);
    CCSprite* skull = (CCSprite*) confirmWindow->getChildByTag(1);
    CCLabelBMFont* text = (CCLabelBMFont*) confirmWindow->getChildByTag(2);
    background->setOpacity(255);
    confirmWindow->setOpacity(255);
    skull->setOpacity(255);
    text->setOpacity(255);
}

void WorldSelectScene::hideConfirmation() {
    CCSprite* background = (CCSprite*) this->getChildByTag(BG_CONFIRM_TAG);
    CCSprite* confirmWindow = (CCSprite*) this->getChildByTag(CONFIRM_WINDOW_TAG);
    CCSprite* skull = (CCSprite*) confirmWindow->getChildByTag(1);
    CCLabelBMFont* text = (CCLabelBMFont*) confirmWindow->getChildByTag(2);
    background->setOpacity(0);
    confirmWindow->setOpacity(0);
    skull->setOpacity(0);
    text->setOpacity(0);
    confirmationMode = false;
}

void WorldSelectScene::makeVisible() {
    this->getChildByTag(WORLD_SELECT_TAG)->setIsVisible(true);
}

void WorldSelectScene::goToMenu(CCObject* pSender) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER2.c_str()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(0.5, MenuScene::scene()));
}

void WorldSelectScene::goToLevels(int worldId) {
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(0.5, LevelSelectScene::scene(worldId)));
    
}

void WorldSelectScene::reloopCloud(CCNode* cloudObj) {
    CCSprite* cloud = (CCSprite*)cloudObj;
    int randSpeed = (rand()%40)+10;
    cloud->setPosition(Geometry::getCloudOrigin(0));
    CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration(randSpeed,Geometry::getCloudEnd(cloud->getContentSize().width, cloud->getPosition().y));
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget( cloud, callfuncN_selector(MenuScene::reloopCloud));
    cloud->runAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
}

Json::Value WorldSelectScene::readLevelsJson() {
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
    return rootL;
}

int WorldSelectScene::checkAllLevels(Json::Value rootL, int worldId) {
    char currentWorld [5];
    sprintf(currentWorld,"%d",worldId);
    int states[LEVELS_PER_WORLD];
    for( int i = 0; i < LEVELS_PER_WORLD; i++){
        states[i] = 3;
    }
    if(rootL != NULL) {
        for( int i = 0; i < rootL[currentWorld].size(); i++){
            char levelIndex [5];
            sprintf(levelIndex,"%d",i+1);
            states[i] = rootL[currentWorld][levelIndex].asInt();
        }
    }
    if((worldId == 1) && states[0] == 3) {
        states[0] = 0;
    }
    bool allGold = true;
    bool allClose = true;
    bool oneOpen = false;
    for( int i = 0; i < LEVELS_PER_WORLD; i++){
        if (states[i] == 0) {
            oneOpen = true;
            allGold = false;
            allClose = false;
            break;
        }
        if(states[i] == 1) {
            allClose = false;
            allGold = false;
        }
        if(states[i] == 2) {
            allClose = false;
            this->totalGold++;
        }
        if(states[i] == 3) {
            allGold = false;
        }
    }
    if(allGold) {
        return 2;
    }
    if(oneOpen) {
        return 0;
    }
    if(allClose) {
        return 3;
    }
    return 1;
}


bool WorldSelectScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    CCPoint location = this->convertTouchToNodeSpace(pTouch);
    if (!confirmationMode) {
        CCScrollLayer* pScrollLayer = (CCScrollLayer*)this->getChildByTag(WORLD_SELECT_TAG);
        for(int i = 0; i < Config::sharedConfig()->TOTAL_WORLDS; i++) {
            CCLayer* aLayer = (CCLayer*)pScrollLayer->getChildByTag(i + 1);
            CCSprite* world = (CCSprite*)aLayer->getChildByTag(1);
            CCLabelBMFont* label = (CCLabelBMFont*)aLayer->getChildByTag(2);
            if(Geometry::nodeContainsTouch(world, aLayer->convertToNodeSpace(location)) || Geometry::nodeContainsTouch(label, aLayer->convertToNodeSpace(location))) {
                pScrollLayer->ccTouchBegan(pTouch, pEvent);
                this->worldTouch = i;
                this->movingTouch = true;
                this->touchMoved = 0;
                this->previousTouch = location;
                return true;
            }
        }
        CCSprite* wood = (CCSprite*)this->getChildByTag(WOOD_TAG);
        CCSprite* pBackToMenu = (CCSprite*)wood->getChildByTag(BUTTON5_TAG);
        if(Geometry::nodeContainsTouch(pBackToMenu, wood->convertToNodeSpace(location))) {
            pBackToMenu->setColor(ccc3(200,200,200));
            this->goToMenu(pBackToMenu);
            return false;
        }
    }
    if(confirmationMode){
        this->hideConfirmation();
        return false;
    }
    return false;
}

void WorldSelectScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    if(this->movingTouch) {
        CCScrollLayer* pScrollLayer = (CCScrollLayer*)this->getChildByTag(WORLD_SELECT_TAG);
        pScrollLayer->ccTouchEnded(pTouch, pEvent);
        if(this->touchMoved >= -16 && this->touchMoved <= 16) {
            if(this->enabled[this->worldTouch]) {
                CCLayer* aLayer = (CCLayer*)pScrollLayer->getChildByTag(this->worldTouch + 1);
                CCSprite* world = (CCSprite*)aLayer->getChildByTag(1);
                world->runAction(CCScaleBy::actionWithDuration(2, 2));
                this->goToLevels(this->worldTouch+1);
            } else {
                this->showConfirmation();
            }
        }
    }
}

void WorldSelectScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {
    if(this->movingTouch) {
        CCScrollLayer* pScrollLayer = (CCScrollLayer*)this->getChildByTag(WORLD_SELECT_TAG);
        pScrollLayer->ccTouchMoved(pTouch, pEvent);
        CCPoint location = this->convertTouchToNodeSpace(pTouch);
        this->touchMoved += location.x - this->previousTouch.x;
        this->previousTouch = location;
    }
}

