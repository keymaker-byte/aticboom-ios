//
//  LoadingScene.cpp
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

#include "LoadingScene.h"

LoadingScene::LoadingScene() : LoadingScene::CCLayer() {
}

LoadingScene::~LoadingScene() {
}

void LoadingScene::onEnter() {
    CCLayer::onEnter();
}

void LoadingScene::onExit() {
    CCLayer::onExit();
    CCSpriteBatchNode* batch = (CCSpriteBatchNode*)this->getChildByTag(BATCH_LOADING_TAG);
    this->removeChildByTag(BATCH_LOADING_TAG, true);
    batch->release();
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

CCScene* LoadingScene::scene(int worldId, int levelId) {
    CCScene *scene = CCScene::node();
    LoadingScene *layer = LoadingScene::node(worldId, levelId);
    scene->addChild(layer, 0, 1);
    return scene;
}

bool LoadingScene::init() {
    if ( !CCLayer::init() ) {
        return false;
    }
    this->setIsKeypadEnabled(true);
    CCDirector::sharedDirector()->resume();
    CCSpriteBatchNode* batch = new CCSpriteBatchNode();
    batch->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->LOADING_PNG.c_str()), 1);
    this->addChild(batch, 0, BATCH_LOADING_TAG);
    CCSprite* gfflogo = CCSprite::spriteWithSpriteFrameName(LOADING_SCREEN.c_str());
    gfflogo->setPosition(Geometry::getScreenCenter());
    this->addChild(gfflogo, 0, 333);
    //ipad fix
    if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
        Border* border = new Border();
        this->addChild(border, 999);
    }
    gfflogo->runAction(CCSequence::actions(CCMoveBy::actionWithDuration(2, CCPointZero), CCCallFuncN::actionWithTarget( gfflogo, callfuncN_selector(LoadingScene::goToGame)), NULL));
    return true;
}

void LoadingScene::goToGame(CCNode* pSender) {
    cocos2d::CCDirector::sharedDirector()->purgeCachedData();
    CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
    LoadingScene* ls = (LoadingScene*)pSender->getParent();
    if(ls->levelId == 0) {
        this->loadComicTextures();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, ComicScene::scene(ls->worldId)));
    }
    else if(ls->levelId == -1) {
        this->loadMenuTextures();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, WorldSelectScene::scene(ls->worldId)));
    }
    else if(ls->levelId == -2) {
        this->loadMenuTextures();
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, MenuScene::scene()));
    }
    else {
        this->loadGameTextures(ls->worldId);
        CCScene *sc = GameScene::scene(ls->worldId, ls->levelId);
        CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, sc));
    }
}

void LoadingScene::loadGameTextures(int worldId) {
    char buffer [50];
    bool night = Geometry::isNight(worldId);
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->ANIMATIONS_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->ANIMATIONS_PLIST.c_str());
    sprintf(buffer, Config::sharedConfig()->W_PNG.c_str(), night ? worldId - 1 : worldId);
    CCTextureCache::sharedTextureCache()->addImage(buffer);
    sprintf(buffer, Config::sharedConfig()->W_PLIST.c_str(),  night ? worldId - 1 : worldId);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(buffer);
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->HUD_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->HUD_PLIST.c_str());
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->HELP_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->HELP_PLIST.c_str());
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->BLACK_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->BLACK_PLIST.c_str());
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->LOADING_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->LOADING_PLIST.c_str());
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->POWERUPS_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->POWERUPS_PLIST.c_str());
}

void LoadingScene::loadMenuTextures() {
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->MENU_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->MENU_PLIST.c_str());
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->BLACK_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->BLACK_PLIST.c_str());
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->LOADING_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->LOADING_PLIST.c_str());
}

void LoadingScene::loadComicTextures() {
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->COMIC_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->COMIC_PLIST.c_str());
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->LOADING_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->LOADING_PLIST.c_str());
}

