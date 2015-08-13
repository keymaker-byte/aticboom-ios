//
//  ComicScene.cpp
//  AticBoom
//
//  Created by Claudio Alvial on 2/9/12.
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

#include "ComicScene.h"
namespace aticboom {
    
    using namespace cocos2d;
    using namespace CocosDenshion;

    ComicScene::ComicScene() : ComicScene::CCLayer()
    {
	
    }

    ComicScene::~ComicScene()
    {
	
    }

    void ComicScene::onEnter()
    {
        CCLayer::onEnter();
    }

    void ComicScene::onExit()
    {
        CCLayer::onExit();
        
        CCSpriteBatchNode* batch = (CCSpriteBatchNode*)this->getChildByTag(BATCH_COMIC_INTRO_TAG);
        this->removeChildByTag(BATCH_COMIC_INTRO_TAG, true);
        batch->release();
        
        CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
        
        if(cleanAfterExit) {
            cocos2d::CCDirector::sharedDirector()->purgeCachedData();
            CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
            CCTextureCache::sharedTextureCache()->removeUnusedTextures();
        }
        
    }

    CCScene* ComicScene::scene(int sequence)
    {
        CCScene *scene = CCScene::node();
        ComicScene *layer = ComicScene::node(sequence);
        scene->addChild(layer, 0, 1);
        return scene;
    }

    bool ComicScene::init()
    {
        if ( !CCLayer::init() )
        {
            return false;
        }
        
        this->setIsKeypadEnabled(true);
        
        CCDirector::sharedDirector()->resume();

        this->touchEnabled=true;
        this->currentPage = 0;
        this->cleanAfterExit = false;
    
        CCSpriteBatchNode* batch = new CCSpriteBatchNode();
        batch->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->COMIC_PNG.c_str()), 6);
        this->addChild(batch, 0, BATCH_COMIC_INTRO_TAG);
    
        CCSprite* gSettingBackground = CCSprite::spriteWithSpriteFrameName(COMIC_INTRO_BG.c_str());
        gSettingBackground->setPosition(Geometry::getScreenCenter());
        this->addChild(gSettingBackground, 0);
        
        CCLabelBMFont* labelTouch = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_CONTINUE.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        labelTouch->setColor(ccc3(50,50,50));
        labelTouch->setScale(0.7);
        labelTouch->setPosition( CCPoint(Geometry::getScreenBotomCenter(24)) );
        this->addChild(labelTouch, 2, 100);
        
        if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() && SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::fullPathFromRelativePath(MUSIC_LEVEL2.c_str()), true);
            
        }
    
        CCSprite* sPage1;
        CCSprite* sPage2;
        CCSprite* sPage3;
        CCLabelBMFont* sText1;
        CCLabelBMFont* sText2;
        CCLabelBMFont* sText3;
        
        if (sequence == 1) {
            sPage1 = CCSprite::spriteWithSpriteFrameName(COMIC_INTRO_1.c_str());
            sPage1->setPosition( CCPoint(Geometry::getScreenBotomCenter(Config::sharedConfig()->COMIC_ADJUST_PAGE_A)) );
            sPage1->setOpacity(0);
            this->addChild(sPage1, 1, 1);
            sText1 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_COMIC_TEXT_1.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
            sText1->setColor(ccc3(45,0,0));
            sText1->setPosition( CCPoint(Geometry::getScreenUpCenter(-Config::sharedConfig()->COMIC_ADJUST_TXT_A)) );
            this->addChild(sText1, 1, 2);
            
            sPage2 = CCSprite::spriteWithSpriteFrameName(COMIC_INTRO_2.c_str());
            sPage2->setPosition( CCPoint(Geometry::getScreenBotomCenter(Config::sharedConfig()->COMIC_ADJUST_PAGE_B)) );
            sPage2->setOpacity(0);
            this->addChild(sPage2, 1, 3);
            sText2 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_COMIC_TEXT_2.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
            sText2->setColor(ccc3(45,0,0));
            sText2->setPosition( CCPoint(Geometry::getScreenUpCenterAdjust(-Config::sharedConfig()->SCREEN_WIDTH,Config::sharedConfig()->COMIC_ADJUST_TXT_C)) );
            this->addChild(sText2, 1, 4);
            
            sPage3 = CCSprite::spriteWithSpriteFrameName(COMIC_INTRO_3.c_str());
            sPage3->setPosition( CCPoint(Geometry::getScreenBotomCenter(Config::sharedConfig()->COMIC_ADJUST_PAGE_C)) );
            sPage3->setOpacity(0);
            this->addChild(sPage3, 1, 5);
            sText3 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_COMIC_TEXT_3.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
            sText3->setColor(ccc3(45,0,0));
            sText3->setPosition( CCPoint(Geometry::getScreenUpCenterAdjust(Config::sharedConfig()->SCREEN_WIDTH,Config::sharedConfig()->COMIC_ADJUST_TXT_C)) );
            this->addChild(sText3, 1, 6);
            
            this->totalPages = 3;
            
        } else if (sequence == 2) {
            
            sPage1 = CCSprite::spriteWithSpriteFrameName(COMIC_END_1.c_str());
            sPage1->setPosition( CCPoint(Geometry::getScreenBotomCenter(Config::sharedConfig()->COMIC_ADJUST_PAGE_A)) );
            sPage1->setOpacity(0);
            this->addChild(sPage1, 1, 1);
            sText1 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_COMIC_TEXT_4.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
            sText1->setColor(ccc3(45,0,0));
            sText1->setPosition( CCPoint(Geometry::getScreenUpCenterAdjust(-Config::sharedConfig()->SCREEN_WIDTH,Config::sharedConfig()->COMIC_ADJUST_TXT_A)) );
            this->addChild(sText1, 1, 2);
            
            sPage2 = CCSprite::spriteWithSpriteFrameName(COMIC_END_2.c_str());
            sPage2->setPosition( CCPoint(Geometry::getScreenBotomCenter(Config::sharedConfig()->COMIC_ADJUST_PAGE_E)) );
            sPage2->setOpacity(0);
            this->addChild(sPage2, 1, 3);
            sText2 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_COMIC_TEXT_5.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
            sText2->setColor(ccc3(45,0,0));
            sText2->setPosition( CCPoint(Geometry::getScreenUpCenterAdjust(Config::sharedConfig()->SCREEN_WIDTH,Config::sharedConfig()->COMIC_ADJUST_TXT_E)) );
            this->addChild(sText2, 1, 4);
            
            this->totalPages = 2;
        
        }
        
        showCurrentPage();   
    
        CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
        
        //ipad fix
        if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
            Border* border = new Border();
            this->addChild(border, 999);
        }
    
        return true;
    }
    
    void ComicScene::showCurrentPage() {
        
        currentPage++;
        int textTag;
        int imageTag;
        int textMargin;
        
        if ( currentPage == 1 ) {
            imageTag = 1;
            textTag = 2;
            textMargin = Config::sharedConfig()->COMIC_MARGIN_TXT_A;
        } else if ( currentPage == 2 ) {
            imageTag = 3;
            textTag = 4;
            if (this->sequence == 1)
                textMargin = Config::sharedConfig()->COMIC_MARGIN_TXT_B;
            else if (this->sequence == 2)
                textMargin = Config::sharedConfig()->COMIC_MARGIN_TXT_E;
        } else if ( currentPage == 3) {
            imageTag = 5;
            textTag = 6;
            textMargin = Config::sharedConfig()->COMIC_MARGIN_TXT_C;
        }
        
        cleanPages();
        
        CCSprite* currentImage = (CCSprite*)this->getChildByTag(imageTag);
        CCLabelBMFont* currentText = (CCLabelBMFont*)this->getChildByTag(textTag);
        
        CCFiniteTimeAction* MoveText = CCMoveTo::actionWithDuration(2.0, Geometry::getScreenUpCenter(textMargin));
        CCActionInterval* wait = CCDelayTime::actionWithDuration(0.5);
        CCFiniteTimeAction* FadeImage = CCFadeIn::actionWithDuration(1.5);
        CCFiniteTimeAction* fancyMoveLeft = CCMoveBy::actionWithDuration(10, CCPoint(-5,0) );
        CCFiniteTimeAction* fancyMoveRight = CCMoveBy::actionWithDuration(10, CCPoint(5,0) );
        
        currentText->runAction(CCSequence::actions(MoveText, fancyMoveLeft, NULL));
        currentImage->runAction(CCSequence::actions(wait, FadeImage, fancyMoveRight, NULL));
        
    }
    
    void ComicScene::cleanPages() {
        
        if ( currentPage == 1 || currentPage > this->totalPages)
            return;
        
        int textTag;
        int imageTag;
        
        if ( currentPage == 2 ) {
            imageTag = 1;
            textTag = 2;
        } else if ( currentPage == 3 ) {
            imageTag = 3;
            textTag = 4;
        } 
        
        CCSprite* currentImage = (CCSprite*)this->getChildByTag(imageTag);
        CCLabelBMFont* currentText = (CCLabelBMFont*)this->getChildByTag(textTag);
        
        currentImage->stopAllActions();
        currentImage->setOpacity(0);
        currentText->stopAllActions();
        currentText->setOpacity(0);
        
    }
    
    void ComicScene::enableTouch(){
        this->touchEnabled = true;
    }
                              
    void ComicScene::actionStopper(CCObject* pSender) {
        CCSprite* sprite = (CCSprite*)pSender;
        sprite->stopAllActions();
    }
    
    void ComicScene::setupPlay()
    
    {
        touchEnabled = false;
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        
        if ( sequence == 1 ) {
            this->cleanAfterExit = true;
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, LoadingScene::scene(1, 1)));
        } 
        else {
            this->cleanAfterExit = true;
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, LoadingScene::scene(1, -1)));
        }        
    }
    
    
    bool ComicScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) 
    {
        if ( touchEnabled == true ) {
            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER1.c_str()));
            if (currentPage < this->totalPages)
                showCurrentPage();
            else if (currentPage >= this->totalPages)
                setupPlay();
       } 
        
        return true;
    }
}