//
//  IntroScene.cpp
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

#include "IntroScene.h"

IntroScene::IntroScene() : IntroScene::CCLayerColor()
{
	
}

IntroScene::~IntroScene()
{
	
}

void IntroScene::onEnter()
{
    CCLayer::onEnter();
}

void IntroScene::onExit()
{
    CCLayer::onExit();
    
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
}

CCScene* IntroScene::scene()
{
    CCScene *scene = CCScene::node();
	IntroScene *layer = IntroScene::node();
	scene->addChild(layer, 0, 1);
	return scene;
}

bool IntroScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4f(255, 255, 255, 255)) )
	{
		return false;
	}
    
    this->setIsKeypadEnabled(true);
    
    CCDirector::sharedDirector()->resume();
    
	CCSprite* gfflogo = CCSprite::spriteWithFile(Config::sharedConfig()->INTRO_PNG.c_str());
    gfflogo->setPosition(Geometry::getScreenCenter());
    gfflogo->setOpacity(0);
    this->addChild(gfflogo, 0);
    
    CCParticleSystemPoint* shine = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->WORLD_BURNING_PARTICLE.c_str());
    shine->setPosition( Geometry::getScreenCenter() );
	shine->setStartColor(ccc4FFromccc4B(ccc4f(255, 100, 100, 5)));
    this->addChild(shine, 1);
    
    //ipad fix
    if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
        Border* border = new Border();
        this->addChild(border, 999);
    }
    
    this->loadTextures();
    
    this->readSoundSettings();
    
    gfflogo->runAction(CCSequence::actions(CCMoveBy::actionWithDuration(0, CCPointZero),  CCFadeIn::actionWithDuration(1), CCMoveBy::actionWithDuration(3, CCPointZero), CCCallFuncN::actionWithTarget( gfflogo, callfuncN_selector(IntroScene::goToTitle)), NULL));
    
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_LOGO.c_str()));
    
	return true;
}

void IntroScene::goToTitle(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, MenuScene::scene()));
}

void IntroScene::loadTextures() {
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->MENU_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->MENU_PLIST.c_str());
    
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->BLACK_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->BLACK_PLIST.c_str());
    
    CCTextureCache::sharedTextureCache()->addImage(Config::sharedConfig()->LOADING_PNG.c_str());
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(Config::sharedConfig()->LOADING_PLIST.c_str());
}

void IntroScene::readSoundSettings()
{
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
    
    if (root["settings"]["sound"] == 1) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MUSIC_VOLUME);
    } else {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0);
    }
    
    if (root["settings"]["fx"] == 1) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(100);
    } else {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0);
    }
    
    Json::StyledWriter writer;
    std::string outputString = writer.write(root);
    
    ofstream file;
    file.open(fileName);
    file << outputString;
    file.close();
}

