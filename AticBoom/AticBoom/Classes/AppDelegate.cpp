//
//  AticBoomAppDelegate.cpp
//  AticBoom
//
//  Created by Juan Rodriguez on 21/12/2011.
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

#include "AppDelegate.h"


USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::initInstance()
{
    return true;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());
    pDirector->enableRetinaDisplay(true);
    pDirector->setDeviceOrientation(kCCDeviceOrientationPortrait);
    pDirector->setAnimationInterval(1.0 / 60);
    pDirector->setProjection(CCDirectorProjection2D);
    CocosDenshion::SimpleAudioEngine* engine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    engine->preloadBackgroundMusic(CCFileUtils::fullPathFromRelativePath(MUSIC_MENU.c_str()));
    engine->preloadBackgroundMusic(CCFileUtils::fullPathFromRelativePath(MUSIC_LEVEL1.c_str()));
    engine->preloadBackgroundMusic(CCFileUtils::fullPathFromRelativePath(MUSIC_LEVEL2.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER1.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER2.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_BUBBLE.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_POP.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_UP.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_KEY.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_BOMB.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_FALL.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_STAR.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_FAN.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_SPLASH.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_LOGO.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_SCREEN.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_CELEBRATION1.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_CELEBRATION2.c_str()));
    engine->preloadEffect(CCFileUtils::fullPathFromRelativePath(SOUND_SCREEN.c_str()));
    //ipad fix
    if (CCDirector::sharedDirector()->getWinSizeInPixels().width > 640) {
        Config::sharedConfig()->iPadFix();
    }
    CCScene *mScene = IntroScene::scene();
    pDirector->runWithScene(mScene);
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene* scene = pDirector->getRunningScene();
    CCLayer* layer = (CCLayer*)scene->getChildByTag(1);
    if(dynamic_cast<GameScene*>(layer)) {
        GameScene* gameScene = (GameScene*) layer;
        if(!gameScene->paused){
            gameScene->pause();
        }
        else {
            pDirector->pause();
            SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        }
    }
    else {
        pDirector->pause();
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
}

void AppDelegate::applicationWillEnterForeground()
{
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene* scene = pDirector->getRunningScene();
    CCLayer* layer = (CCLayer*)scene->getChildByTag(1);
    if(dynamic_cast<GameScene*>(layer)) {
        GameScene* gameScene = (GameScene*) layer;
        Level* level = (Level *)gameScene->getChildByTag(LEVEL_TAG);
        if(level->state == LEVEL_STATE_START){
            pDirector->resume();
            SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        }
    }
    else {
        pDirector->resume();
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
}
