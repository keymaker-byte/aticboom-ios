//
//  GameScene.cpp
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

#include "MenuScene.h"


GameScene::GameScene() : GameScene::CCLayer()
{
}

GameScene::~GameScene()
{
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
}

void GameScene::onExit()
{
    CCLayer::onExit();
    
    CCSpriteBatchNode* batchPlayer = (CCSpriteBatchNode*)this->getChildByTag(BATCH_PLAYERL_TAG);
    this->removeChildByTag(BATCH_PLAYERL_TAG, true);
    batchPlayer->release();
    
    CCSpriteBatchNode* batchWorld = (CCSpriteBatchNode*)this->getChildByTag(BATCH_WN_TAG);
    this->removeChildByTag(BATCH_WN_TAG, true);
    batchWorld->release();
    
    CCSpriteBatchNode* batchHud = (CCSpriteBatchNode*)this->getChildByTag(BATCH_HUD_TAG);
    this->removeChildByTag(BATCH_HUD_TAG, true);
    batchHud->release();
    
    CCSpriteBatchNode* batchHelp = (CCSpriteBatchNode*)this->getChildByTag(BATCH_HELP_TAG);
    this->removeChildByTag(BATCH_HELP_TAG, true);
    batchHelp->release();
    
    CCSpriteBatchNode* batchBlack = (CCSpriteBatchNode*)this->getChildByTag(BATCH_BLACK_TAG);
    this->removeChildByTag(BATCH_BLACK_TAG, true);
    batchBlack->release();
    
    CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    
    if(cleanAfterExit) {
        cocos2d::CCDirector::sharedDirector()->purgeCachedData();
        CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
        CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    }
}

void GameScene::keyBackClicked()
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    if (level->state == LEVEL_STATE_PLAYING) this->pause();
}


CCScene* GameScene::scene(int worldId, int levelId)
{
    CCScene *scene = CCScene::node();
	GameScene *layer = GameScene::node(worldId, levelId);
	scene->addChild(layer, 0, 1);
	return scene;
}

bool GameScene::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    this->setIsKeypadEnabled(true);
    
    CCDirector::sharedDirector()->resume();
    
    this->isNewGolden = false;
    this->cleanAfterExit = false;
    char buffer [50];
    
    CCSpriteBatchNode* batchPlayer = new CCSpriteBatchNode();
    batchPlayer->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->ANIMATIONS_PNG.c_str()), 406);
    this->addChild(batchPlayer, 0, BATCH_PLAYERL_TAG);
    
    bool night = Geometry::isNight(this->worldId);
    int fixedWorld = this->worldId;
    sprintf(buffer, Config::sharedConfig()->W_PNG.c_str(), night ? fixedWorld - 1 : fixedWorld);
    CCSpriteBatchNode* batchWorld = new CCSpriteBatchNode();
    batchWorld->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(buffer), 11);
    this->addChild(batchWorld, 0, BATCH_WN_TAG);
    
    CCSpriteBatchNode* batchHud = new CCSpriteBatchNode();
    batchHud->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->HUD_PNG.c_str()), 83);
    this->addChild(batchHud, 0, BATCH_HUD_TAG);
    
    CCSpriteBatchNode* batchHelp = new CCSpriteBatchNode();
    batchHelp->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->HELP_PNG.c_str()), 14);
    this->addChild(batchHelp, 0, BATCH_HELP_TAG);
    
    CCSpriteBatchNode* batchBlack = new CCSpriteBatchNode();
    batchBlack->initWithTexture(CCTextureCache::sharedTextureCache()->textureForKey(Config::sharedConfig()->BLACK_PNG.c_str()), 1);
    this->addChild(batchBlack, 0, BATCH_BLACK_TAG);
    
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    
    this->makeLevel();
    
    //ipad fix
    if(CCDirector::sharedDirector()->getWinSizeInPixels().width >= 768) {
        Border* border = new Border();
        this->addChild(border, 999);
    }
    
	return true;
}

void GameScene::makeLevel()
{    
    unsigned char *uc;
    unsigned long bufferSize = 0;
    char fileName [1024];
    sprintf (fileName, LEVEL_JSON.c_str(), this->worldId, this->levelId);
    string fullPath = CCFileUtils::fullPathFromRelativePath(fileName);
    uc =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSize);
    char * ca = (char *) uc;
    string buffer = string(ca);
    
    Json::Value root;
    Json::Reader reader;
    reader.parse(buffer.c_str(), root);
    
    delete uc;
    this->schedule(schedule_selector(GameScene::secondTimer), 1);
    
    Level* level = new Level(root["level"]);
    this->addChild(level, 1, LEVEL_TAG);
    
    this->scroll = 0;
    this->paused = true;
    this->isNewGolden = false;
    this->levelScore = 0;
    this->labelScore = 0;
    this->bestScore = 0;
    this->usedBubbles = 0;
    this->isBestScore = false;
    
    Hud* hudNode = new Hud(root["level"]);
    hudNode->setPosition(Geometry::getScreenUpCenter(Config::sharedConfig()->WOOD_MARGEN));
    this->addChild(hudNode, 10, HUD_TAG);
    
    Rope* ropeNode = new Rope(level->time);
    this->addChild(ropeNode, 10, ROPE_TAG);
    
    Helm* heml = new Helm();
    heml->setIsVisible(false);
    this->addChild(heml, -1, HEML_TAG);
    
    if(level->state == LEVEL_STATE_START) {
        CCSprite* black = CCSprite::spriteWithSpriteFrameName(BLACK_PNG.c_str());
        black->setScale(100);
        black->setPosition(Geometry::getScreenCenter());
        black->setOpacity(255);
        this->addChild(black, 12, HINT_BLACK_TAG);
        
        char frase[255];
        sprintf(frase,Config::sharedConfig()->LANG_LEVELDESCRIPTION.c_str(),this->worldId,this->levelId);
        
        CCLabelBMFont* labelTouch = CCLabelBMFont::labelWithString(frase, Config::sharedConfig()->BMFONT_NAME.c_str());
        labelTouch->setScale(Config::sharedConfig()->FONT_SCALE);
        labelTouch->setAnchorPoint(ccp(0.5f,0.5f));
        labelTouch->setColor(ccc3(255,255,255));
        labelTouch->setPosition(CCPoint(CCDirector::sharedDirector()->getWinSize().width/2,Geometry::getScreenCenter().y + Config::sharedConfig()->MENU_MAIN_PLAY_FONT*Config::sharedConfig()->FONT_SCALE));//getScreenBotomCenterAdjust(Config::sharedConfig()->HINT_TOUCH_XMARGIN, Config::sharedConfig()->HINT_TOUCH_YMARGIN));
        this->addChild(labelTouch, 12, HINT_TEXT_TAG);
        
        char frase2[255];
        if ( level->bubbleNumber == 1 )
            sprintf(frase2,Config::sharedConfig()->LANG_LEVELDESCRIPTION2.c_str(),level->bubbleNumber);
        else
            sprintf(frase2,Config::sharedConfig()->LANG_LEVELDESCRIPTION2PLURAL.c_str(),level->bubbleNumber);
        CCLabelBMFont* labelTouch2 = CCLabelBMFont::labelWithString(frase2, Config::sharedConfig()->BMFONT_NAME.c_str());
        labelTouch2->setScale(Config::sharedConfig()->FONT_SCALE);
        labelTouch2->setAnchorPoint(ccp(0.5f,0.5f));
        labelTouch2->setColor(ccc3(255,255,255));
        labelTouch2->setPosition(Geometry::getScreenCenter());//getScreenBotomCenterAdjust(Config::sharedConfig()->HINT_TOUCH_XMARGIN, Config::sharedConfig()->HINT_TOUCH_YMARGIN));
        this->addChild(labelTouch2, 12, HINT_TEXT_TAG2);
        
        CCLabelBMFont* labelTouch3 = CCLabelBMFont::labelWithString(Config::sharedConfig()->LANG_LEVELDESCRIPTION3.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
        labelTouch3->setScale(Config::sharedConfig()->FONT_SCALE);
        labelTouch3->setAnchorPoint(ccp(0.5f,0.5f));
        labelTouch3->setColor(ccc3(255,255,255));
        labelTouch3->setPosition(CCPoint(CCDirector::sharedDirector()->getWinSize().width/2,Geometry::getScreenCenter().y - Config::sharedConfig()->MENU_MAIN_PLAY_FONT*Config::sharedConfig()->FONT_SCALE));//getScreenBotomCenterAdjust(Config::sharedConfig()->HINT_TOUCH_XMARGIN, Config::sharedConfig()->HINT_TOUCH_YMARGIN));
        this->addChild(labelTouch3, 12, HINT_TEXT_TAG3);
        
        ropeNode->pauseRope();
    }
    else {
        Player* player = (Player *) level->getChildByTag(PLAYER_TAG);
        player->move();
    }
    
    this->drawInformation();

    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying() && SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(CCFileUtils::fullPathFromRelativePath(MUSIC_LEVEL1.c_str()), true);
    }
    
    this->pane();
}

void GameScene::destroyLevel()
{    
    this->unschedule(schedule_selector(GameScene::secondTimer));
    this->unschedule(schedule_selector(GameScene::reachScore));
    this->removeChildByTag(LEVEL_TAG, true);
    this->removeChildByTag(HUD_TAG, true);
    this->removeChildByTag(ROPE_TAG, true);
    this->removeChildByTag(HEML_TAG, true);
}

void GameScene::scrollUp()
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    level->state = LEVEL_STATE_SCROLLING;
    this->scroll++;
    
    CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration( 1 , CCPointMake(0, - FLOORS_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT * 4 * this->scroll + 3 * this->scroll));
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(GameScene::scrollUpFinished));
    level->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));
}

void GameScene::scrollUpFinished(CCNode* sender)
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    if(level->state == LEVEL_STATE_SCROLLING) {
        level->state = LEVEL_STATE_PLAYING;
    }
    
}

void GameScene::scrollDown()
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    level->state = LEVEL_STATE_SCROLLING;
    this->scroll--;
    
    CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration( 1 , CCPointMake(0, (- FLOORS_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT * 4 * this->scroll + 3 * this->scroll)));
    CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(GameScene::scrollDownFinished));
    level->runAction(CCSequence::actions(actionMove, actionMoveDone, NULL));
}

void GameScene::scrollDownFinished(CCNode* sender)
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    if(level->state == LEVEL_STATE_SCROLLING) {
        level->state = LEVEL_STATE_PLAYING;
    }
    
}

void GameScene::pane()
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    level->state = LEVEL_STATE_PANE;
    if(level->floorSize > 8) {
        CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration( 0 , CCPointMake(0, (- FLOORS_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT * 4 * 2 + 3 * 2)));
        CCFiniteTimeAction* actionMoveB = CCMoveTo::actionWithDuration( 8 , CCPointMake(0, 0));
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(GameScene::paneFinished));
        level->runAction(CCSequence::actions(actionMove, actionMoveB, actionMoveDone, NULL));
    }
    else if(level->floorSize > 4) {
        CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration( 0 , CCPointMake(0, (- FLOORS_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT * 4 * 1 + 3 * 1)));
        CCFiniteTimeAction* actionMoveB = CCMoveTo::actionWithDuration( 4 , CCPointMake(0, 0));
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(GameScene::paneFinished));
        level->runAction(CCSequence::actions(actionMove, actionMoveB, actionMoveDone, NULL));
    }
    else {
        this->paneFinished(this);
    }
}

void GameScene::paneFinished(CCNode* sender)
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    CCFiniteTimeAction* actionMove = CCMoveTo::actionWithDuration( 0 , CCPointMake(0, 0));
    level->stopAllActions();
    level->runAction(actionMove);
    level->state = LEVEL_STATE_START;
}

void GameScene::secondTimer(ccTime delta)
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    switch (level->state) {
        case LEVEL_STATE_PLAYING:
            level->time--;
            if(level->time <= 0) {
                this->funlose();
            }
            break;
        case LEVEL_STATE_SCROLLING:
        case LEVEL_STATE_DIE:
        case LEVEL_STATE_WIN:
        case LEVEL_STATE_START:
            break;
    }
    
}

void GameScene::winLevel(CCNode* nada)
{
    Level* level = (Level*)this->getChildByTag(LEVEL_TAG);
    Player* player = (Player *) level->getChildByTag(PLAYER_TAG);
    writeLevelJson(player->hasStar);
    writeLevelScore();
    labelScore = 0;
    Helm* hemlNode = (Helm*)this->getChildByTag(HEML_TAG);
    hemlNode->setIsVisible(true);
    this->reorderChild(hemlNode, 100);
    hemlNode->activateHeml((player->hasStar ? HEML_GOLD : HEML_GRAY), levelScore, bestScore);
    this->schedule(schedule_selector(GameScene::reachScore), 0.0001);
    this->paused = true;
    
    for (int i = 0; i < level->fancyCount; i++) {
        Fancy* fancy = (Fancy *) level->getChildByTag(FANCY_TAG + i);
        fancy->dissapear();
    }
}

void GameScene::reachScore(){
    Helm* heml = (Helm*)this->getChildByTag(HEML_TAG);
    CCNode* vMenu = NULL;
    
    switch (heml->vType) {
        case HEML_GRAY:{
            vMenu = (CCNode *) heml->getChildByTag(3);
            break;
        }
        case HEML_GOLD:{
            vMenu = (CCNode *) heml->getChildByTag(4);
            break;
        }
        case HEML_RED:
            vMenu = (CCNode *) heml->getChildByTag(3);
            break;
        default:
            break;
    }
    double sum = 1;
    sum = ((double)(levelScore * 1.0))/30;
    
    CCLabelBMFont* label = (CCLabelBMFont *) vMenu->getChildByTag(4);
    char buff[20];
    if (labelScore < levelScore) {
        labelScore += sum;
        sprintf(buff, Config::sharedConfig()->LANG_SCORE.c_str(), (int)labelScore);
        label->setString(buff);
    } else {
        if(labelScore > levelScore)
        {
            labelScore = levelScore;
            sprintf(buff, Config::sharedConfig()->LANG_SCORE.c_str(), (int)labelScore);
            label->setString(buff);
        }
        this->unschedule(schedule_selector(GameScene::reachScore));
        if(this->levelScore >= this->bestScore && this->isBestScore) {
            CCParticleSystemPoint* fireworks = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->CONFETI_PARTICLE.c_str());
            fireworks->setPosition( CCPoint(label->getPositionX(),label->getPositionY()) );
            this->addChild(fireworks, 500);
        }
    }
}

void GameScene::loseLevel(CCNode* nada)
{
    if(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MUSIC_VOLUME_LOW);
    }
    writeLevelScore();
    Helm* hemlNode = (Helm*)this->getChildByTag(HEML_TAG);
    hemlNode->setIsVisible(true);
    this->reorderChild(hemlNode, 100);
    hemlNode->activateHeml(HEML_RED);
    this->paused = true;
        
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    for (int i = 0; i < level->fancyCount; i++) {
        Fancy* fancy = (Fancy *) level->getChildByTag(FANCY_TAG + i);
        fancy->dissapear();
    }
}

void GameScene::funlose()
{
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    Player* player = (Player *) level->getChildByTag(PLAYER_TAG);
    player->explode();
    this->runAction(CCShaky3D::actionWithRange(4, true, ccg(15,10), 1));
}

void GameScene::pause()
{
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
    if(!this->paused) {
        this->paused = true;
        Level* level = (Level*)this->getChildByTag(LEVEL_TAG);
        Rope* rope = (Rope*)this->getChildByTag(ROPE_TAG);
        level->state = LEVEL_STATE_PAUSE;
        rope->pauseAudio(true);
        
        Helm* hemlNode = (Helm*)this->getChildByTag(HEML_TAG);
        hemlNode->setIsVisible(true);
        this->reorderChild(hemlNode, 100);
        hemlNode->activateHeml(HEML_NEUTRAL);
        
        CCDirector::sharedDirector()->pause();
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    }
    else {
        this->paused = false;
        Helm* hemlNode = (Helm*)this->getChildByTag(HEML_TAG);
        hemlNode->setIsVisible(false);
        this->reorderChild(hemlNode, -1);
        hemlNode->inactivateHeml();
        
        CCDirector::sharedDirector()->resume();
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        
        Level* level = (Level*)this->getChildByTag(LEVEL_TAG);
        level->state = LEVEL_STATE_PLAYING;
        
        Rope* rope = (Rope*)this->getChildByTag(ROPE_TAG);
        rope->pauseAudio(false);
    }
}

void GameScene::nextLevel() {
    
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
    if (this->levelId == LEVELS_PER_WORLD) {
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        
        if (worldId == 1) {
            this->cleanAfterExit = true;
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, LoadingScene::scene(2, 0)));
        }
        else {
            this->cleanAfterExit = true;
            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, LoadingScene::scene(this->worldId, -1)));
        }
    }
    else {
        this->destroyLevel();
        this->levelId++;
        this->makeLevel();
    }
}

void GameScene::playAgain(){
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
    
    this->destroyLevel();
    this->stopAllActions();
    this->setGrid(NULL);
    
    if(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MUSIC_VOLUME);
    }
    this->makeLevel();    
}

void GameScene::mainMenu(){
    if(this->paused) {
        CCDirector::sharedDirector()->resume();
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER3.c_str()));
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    if(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() > 0) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(MUSIC_VOLUME);
    }
    this->stopAllActions();
    this->setGrid(NULL);
    this->cleanAfterExit = true;
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, LoadingScene::scene(0, -2)));
}

void GameScene::worldSelectScreen(){
    GameScene *scene = (GameScene*)CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1);
    if(scene->paused) {
        CCDirector::sharedDirector()->resume();
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(1, LoadingScene::scene(scene->levelId, -1)));
}

void GameScene::writeLevelJson(bool starState)
{
    char fileName [1024];
    sprintf (fileName, LEVELS_JSON.c_str(), CCFileUtils::getWriteablePath().c_str());
    
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
        string fullPath = CCFileUtils::fullPathFromRelativePath(INITLEVELS_JSON.c_str());
        
        unsigned long bufferSizeI = 0;
        unsigned char * dataI =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
        char * ca = (char *) dataI;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), root);
        
        delete dataI;
    }
    
    delete uc;
    
    char currentLevel [5];
    char nextLevel [5];
    sprintf(currentLevel,"%d",levelId);
    sprintf(nextLevel,"%d",levelId+1);
    
    char currentWorld [5];
    char nextWorld [5];
    sprintf(currentWorld,"%d",worldId);
    sprintf(nextWorld,"%d",worldId+1);
    
    if(root[currentWorld][currentLevel] == 2) {
        starState = true;
        this->isNewGolden = false;
    }
    else {
        this->isNewGolden = true;
    }
    
    if (starState) {
        root[currentWorld][currentLevel] = 2;
    }
    else {
        root[currentWorld][currentLevel] = 1;
    }
    
    if (levelId != LEVELS_PER_WORLD ) {
        if(root[currentWorld][nextLevel] == 3) {
            root[currentWorld][nextLevel] = 0;
        }
    }
    
    this->isGoldenWorld = true;
    this->isCompletedWorld = true;
    for (int i = 1; i <= LEVELS_PER_WORLD; i++) {
        char levelNumber [5];
        sprintf(levelNumber,"%d",i);
        if(root[currentWorld][levelNumber].asInt() != 2) {
            this->isGoldenWorld = false;
        }
        if(root[currentWorld][levelNumber].asInt() == 3 || root[currentWorld][levelNumber].asInt() == 0) {
            this->isCompletedWorld = false;
        }
    }
    
    Json::StyledWriter writer;
    std::string outputString = writer.write(root);
    
    ofstream file;
    file.open(fileName);
    file << outputString;
    file.close();
}

void GameScene::writeLevelScore()
{
    char fileName [1024];
    sprintf (fileName, SCORE_JSON.c_str(), CCFileUtils::getWriteablePath().c_str());
    
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
        string fullPath = CCFileUtils::fullPathFromRelativePath(INITSCORE_JSON.c_str());
        
        unsigned long bufferSizeI = 0;
        unsigned char * dataI =  CCFileUtils::getFileData(fullPath.c_str(),"r", &bufferSizeI);
        char * ca = (char *) dataI;
        string buffer = string(ca);
        Json::Reader reader;
        reader.parse(buffer.c_str(), root);
        
        delete dataI;
    }
    
    delete uc;
    
    Level* level = (Level*)this->getChildByTag(LEVEL_TAG);
    Player* player = (Player *) level->getChildByTag(PLAYER_TAG);
    
    levelScore = 0;
    levelScore = level->bubbleNumber*50 + level->time*2 + player->starNumber*200;
    
    if(level->state == LEVEL_STATE_WIN) {
        char buff[5];
        char buff2[5];
        sprintf(buff, "%i", worldId);
        sprintf(buff2, "%i", levelId);
        if(root["score"]["STARS"][buff][buff2].asInt() < player->starNumber) {
            root["score"]["STARS"][buff][buff2] = player->starNumber;
        }
        
        if(this->isNewGolden) {
            root["score"]["GOLDENSKULL"] = root["score"]["GOLDENSKULL"].asInt() + 1;
            int totalGoldenSkulls = root["score"]["GOLDENSKULL"].asInt();
            if(root["achievements"]["ACHIVEMENT_YOHOHO"].asInt() == 0 && totalGoldenSkulls >= 1) {
                root["achievements"]["ACHIVEMENT_YOHOHO"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_YOHOHEHO"].asInt() == 0 && totalGoldenSkulls >= 4) {
                root["achievements"]["ACHIVEMENT_YOHOHEHO"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_ANCHORSAWEIGH"].asInt() == 0 && totalGoldenSkulls >= 16) {
                root["achievements"]["ACHIVEMENT_ANCHORSAWEIGH"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_SETTHESAILS"].asInt() == 0 && totalGoldenSkulls >= 32) {
                root["achievements"]["ACHIVEMENT_SETTHESAILS"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_APIRATESLIFEFORME"].asInt() == 0 && totalGoldenSkulls >= 48) {
                root["achievements"]["ACHIVEMENT_APIRATESLIFEFORME"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_BLIMEY"].asInt() == 0 && totalGoldenSkulls >= 64) {
                root["achievements"]["ACHIVEMENT_BLIMEY"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_BYTHEPOWERS"].asInt() == 0 && totalGoldenSkulls >= 80) {
                root["achievements"]["ACHIVEMENT_BYTHEPOWERS"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_BLOWMEDOWN"].asInt() == 0 && totalGoldenSkulls >= 96) {
                root["achievements"]["ACHIVEMENT_BLOWMEDOWN"] = 1;
            }
        }
        if(this->isCompletedWorld) {
            if(root["achievements"]["ACHIVEMENT_SURVIVEDGOLDENHIND"].asInt() == 0 && worldId == 1) {
                root["achievements"]["ACHIVEMENT_SURVIVEDGOLDENHIND"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_SURVIVEDGOLDENNIGHT"].asInt() == 0 && worldId == 2) {
                root["achievements"]["ACHIVEMENT_SURVIVEDGOLDENNIGHT"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_SURVIVEDQUEENANNE"].asInt() == 0 && worldId == 3) {
                root["achievements"]["ACHIVEMENT_SURVIVEDQUEENANNE"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_SURVIVEDQUEENANNENIGHT"].asInt() == 0 && worldId == 4) {
                root["achievements"]["ACHIVEMENT_SURVIVEDQUEENANNENIGHT"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_SURVIVEDADVENTUREGALLERY"].asInt() == 0 && worldId == 5) {
                root["achievements"]["ACHIVEMENT_SURVIVEDADVENTUREGALLERY"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_SURVIVEDADVENTURENIGHT"].asInt() == 0 && worldId == 6) {
                root["achievements"]["ACHIVEMENT_SURVIVEDADVENTURENIGHT"] = 1;
            }
        }
        if(this->isGoldenWorld) {
            if(root["achievements"]["ACHIVEMENT_GILDGOLDENHIND"].asInt() == 0 && worldId == 1) {
                root["achievements"]["ACHIVEMENT_GILDGOLDENHIND"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_GILDGOLDENNIGHT"].asInt() == 0 && worldId == 2) {
                root["achievements"]["ACHIVEMENT_GILDGOLDENNIGHT"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_GILDQUEENANNE"].asInt() == 0 && worldId == 3) {
                root["achievements"]["ACHIVEMENT_GILDQUEENANNE"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_GILDQUEENANNENIGHT"].asInt() == 0 && worldId == 4) {
                root["achievements"]["ACHIVEMENT_GILDQUEENANNENIGHT"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_GILDADVENTUREGALLERY"].asInt() == 0 && worldId == 5) {
                root["achievements"]["ACHIVEMENT_GILDADVENTUREGALLERY"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_GILDADVENTURENIGHT"].asInt() == 0 && worldId == 6) {
                root["achievements"]["ACHIVEMENT_GILDADVENTURENIGHT"] = 1;
            }
        }
        if(level->bubbleNumber > 0) {
            if(root["achievements"]["ACHIVEMENT_MOREBUBBLESFORTHECREW"].asInt() == 0 && level->bubbleNumber == 1) {
                root["achievements"]["ACHIVEMENT_MOREBUBBLESFORTHECREW"] = 1;
            }
            else if(root["achievements"]["ACHIVEMENT_ASAVINPIRATEVEWORTHTWO"].asInt() == 0 && level->bubbleNumber == 2) {
                root["achievements"]["ACHIVEMENT_ASAVINPIRATEVEWORTHTWO"] = 1;
            }
        }
        if(level->time >= 0) {
            if(root["achievements"]["ACHIVEMENT_TOERRISHUMANTOARRISPIRATE"].asInt() == 0 && level->time <= 2) {
                root["achievements"]["ACHIVEMENT_TOERRISHUMANTOARRISPIRATE"] = 1;
            }
        }
    }
    
    if(player->floorsUpNumber > 0) {
        root["score"]["FLOORS"] = root["score"]["FLOORS"].asInt() + player->floorsUpNumber;
        int totalFloors = root["score"]["FLOORS"].asInt();
        if(root["achievements"]["ACHIVEMENT_THEMPEGBEONFIRE"].asInt() == 0 && totalFloors >= 150) {
            root["achievements"]["ACHIVEMENT_THEMPEGBEONFIRE"] = 1;
        }
        else if(root["achievements"]["ACHIVEMENT_HIGHASAFLYNFLAG"].asInt() == 0 && totalFloors >= 300) {
            root["achievements"]["ACHIVEMENT_HIGHASAFLYNFLAG"] = 1;
        }
    }
    
    if(root["achievements"]["ACHIVEMENT_AHOY"].asInt() == 0 && player->floorsUpFollowOk) {
        root["achievements"]["ACHIVEMENT_AHOY"] = 1;
    }
    
    if(root["achievements"]["ACHIVEMENT_YARRGH"].asInt() == 0 && player->floorsDownFollowOk) {
        root["achievements"]["ACHIVEMENT_YARRGH"] = 1;
    }
    
    if(level->state == LEVEL_STATE_DIE) {
        if(root["achievements"]["ACHIVEMENT_CURSEDDOUBLOONS"].asInt() == 0 && player->hasStar) {
            root["achievements"]["ACHIVEMENT_CURSEDDOUBLOONS"] = 1;
        }
    }
    
    if(level->state == LEVEL_STATE_WIN) {
        if(root["score"]["BESTSCORE"] < levelScore)
        {
            root["score"]["BESTSCORE"] = levelScore; 
        }
        bestScore = 0;
        char buff[5];
        char buff2[5];
        sprintf(buff, "%i", level->world);
        sprintf(buff2, "%i", levelId);
        bestScore = root["score"]["WORLDS"][buff][buff2].asInt();    
        if(bestScore < levelScore)
        {
            isBestScore = true;
            bestScore = levelScore;
            root["score"]["WORLDS"][buff][buff2] = levelScore;
        } 
        else {
            isBestScore = false;
        }
        
        int bestWorldScore = root["score"]["HIGHSCORE"][buff].asInt(); 
        int worldScore = 0;
        for(int i = 1; i <= LEVELS_PER_WORLD; i++) {
            sprintf(buff2, "%i", i);
            worldScore += root["score"]["WORLDS"][buff][buff2].asInt(); 
        }
        if(bestWorldScore < worldScore) {
            root["score"]["HIGHSCORE"][buff] = worldScore;
        }
    }

    Json::StyledWriter writer;
    std::string outputString = writer.write(root);
    
    ofstream file;
    file.open(fileName);
    file << outputString;
    file.close();
}



void GameScene::drawInformation()
{
    Hud* hud = (Hud*)this->getChildByTag(HUD_TAG);
    Level* level = (Level*)this->getChildByTag(LEVEL_TAG);
    Player* player = (Player *) level->getChildByTag(PLAYER_TAG);
    hud->setStarNumber(player->starNumber);
}


bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    Level* level = (Level *)this->getChildByTag(LEVEL_TAG);
    Hud* hud = (Hud*)this->getChildByTag(HUD_TAG);
    CCPoint location = this->convertTouchToNodeSpace(pTouch);
    
    if(level->state == LEVEL_STATE_PANE) {
        this->paneFinished(this);
        return true;
    }
    
    if(level->state == LEVEL_STATE_START) {
        Rope* rope = (Rope*)this->getChildByTag(ROPE_TAG);
        this->removeChildByTag(HINT_TEXT_TAG, true);//
        this->removeChildByTag(HINT_TEXT_TAG2, true);
        this->removeChildByTag(HINT_TEXT_TAG3, true);
        this->removeChildByTag(HINT_BLACK_TAG, true);
        level->state = LEVEL_STATE_PLAYING;
        Player* player = (Player *) level->getChildByTag(PLAYER_TAG);
        player->move();
        rope->resumeRope();
        this->paused = false;
        
        for (int i = 0; i < level->fancyCount; i++) {
            Fancy* fancy = (Fancy *) level->getChildByTag(FANCY_TAG + i);
            fancy->appear();
        }
        
        return true;
    }
    
    if(level->state == LEVEL_STATE_PLAYING) {
        CCSprite* item1 = (CCSprite*)hud->getChildByTag(RELOAD_TAG);
        if(Geometry::nodeContainsTouch(item1, hud->convertToNodeSpace(location))) {
            this->playAgain();
            return true;
        }
        
        CCSprite* item2 = (CCSprite*)hud->getChildByTag(PAUSE_TAG);
        if(Geometry::nodeContainsTouch(item2, hud->convertToNodeSpace(location))) {
            this->pause();
            return true;
        }
    }
    if(level->state == LEVEL_STATE_PLAYING && hud->bubbleSize > 0) {
        CCFiniteTimeAction* actionMoveA;
        CCFiniteTimeAction* actionMoveB;
        Bubble* bubble = (Bubble *)level->getChildByTag(BUBBLE_TAG + this->usedBubbles);
        int row = Geometry::getTouchTileAtFloor(pTouch->locationInView().y);
        if(row >= 0 && row + (this->scroll * 4 * FLOORS_TILES_HEIGHT) < (level->floorSize - 1) * FLOORS_TILES_HEIGHT) {
            int col = Geometry::getTouchTileColumn(pTouch->locationInView().x, bubble->tileWidth);
            if(col >= 0 && col < (level->mesh->tileColumns - 1)) {
                if(row < 4 * FLOORS_TILES_HEIGHT) {
                    int bubleRow = row + (this->scroll * 4 * FLOORS_TILES_HEIGHT);
                    bool notbubbleposition = false;
                    for(int i = level->mesh->tiles[col][bubleRow].size() - 1; i >= 0; i--) {
                        GameObject* obj = level->mesh->tiles[col][bubleRow][i];
                        if(dynamic_cast<Wall*>(obj)) {
                            Wall* wall = (Wall*)obj;
                            if(wall->position[0] == col + 2 && col - 1 > 0) {
                                notbubbleposition = false;
                                col = col - 1;
                            }
                            else if(wall->position[0] == col - 1 && col + 2 < level->mesh->tileColumns) {
                                notbubbleposition = false;
                                col = col + 2;
                            }
                            else if(wall->position[0] == col - 2 && col + 1 < level->mesh->tileColumns) {
                                notbubbleposition = false;
                                col = col + 1;
                            }
                            else {
                                notbubbleposition = true;
                            }
                            
                            break;
                        }
                    }
                    if(!notbubbleposition) {
                        hud->killBubble();
                        bubble->position[0] = col;
                        bubble->position[1] = bubleRow;
                        CCPoint pos = Geometry::getTilePosition(bubble->position[0], bubble->position[1], bubble->tileWidth, bubble->tileHeight);
                        bubble->touchcoords = pos;
                        actionMoveA = CCMoveTo::actionWithDuration( 0, CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, Config::sharedConfig()->SCREEN_HEIGHT* (this->scroll+1)) );
                        actionMoveB = CCMoveTo::actionWithDuration( 0.25f, pos );
                        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_BUBBLE.c_str()));                    
                        bubble->runMovingAction( CCSequence::actions(actionMoveA, actionMoveB, NULL) ); 
                        level->mesh->tiles[bubble->position[0]][bubble->position[1]].push_back(bubble);
                        level->bubbleNumber--;
                        this->usedBubbles++;
                        this->drawInformation();
                    }
                }
            }
        }
    }
    
    else if(level->state == LEVEL_STATE_WIN) {
        Helm* heml = (Helm*)this->getChildByTag(HEML_TAG);
        CCNode* vMenuWin = (CCNode*)heml->getChildByTag(3);
        CCNode* vMenuGold = (CCNode*)heml->getChildByTag(4);
        
        CCSprite* item1 = (CCSprite*)vMenuWin->getChildByTag(1);
        CCLabelBMFont* label1 = (CCLabelBMFont*)item1->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item1, vMenuWin->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item1->setColor(ccc3(200,200,200));
            label1->setColor(ccc3(50,50,50));
            this->mainMenu();
            return true;
        }
        
        CCSprite* item2 = (CCSprite*)vMenuWin->getChildByTag(2);
        CCLabelBMFont* label2 = (CCLabelBMFont*)item2->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item2, vMenuWin->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item2->setColor(ccc3(200,200,200));
            label2->setColor(ccc3(50,50,50));
            this->playAgain();
            return true;
        }
        
        CCSprite* item3 = (CCSprite*)vMenuWin->getChildByTag(3);
        CCLabelBMFont* label3 = (CCLabelBMFont*)item3->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item3, vMenuWin->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item3->setColor(ccc3(200,200,200));
            label3->setColor(ccc3(50,50,50));
            this->nextLevel();
            return true;
        }
        
        CCSprite* item4 = (CCSprite*)vMenuGold->getChildByTag(1);
        CCLabelBMFont* label4 = (CCLabelBMFont*)item4->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item4, vMenuGold->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item4->setColor(ccc3(200,200,200));
            label4->setColor(ccc3(50,50,50));
            this->mainMenu();
            return true;
        }
        
        CCSprite* item5 = (CCSprite*)vMenuGold->getChildByTag(2);
        CCLabelBMFont* label5 = (CCLabelBMFont*)item5->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item5, vMenuGold->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item5->setColor(ccc3(200,200,200));
            label5->setColor(ccc3(50,50,50));
            this->playAgain();
            return true;
        }
        
        CCSprite* item6 = (CCSprite*)vMenuGold->getChildByTag(3);
        CCLabelBMFont* label6 = (CCLabelBMFont*)item6->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item6, vMenuGold->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item6->setColor(ccc3(200,200,200));
            label6->setColor(ccc3(50,50,50));
            this->nextLevel();
            return true;
        }
    }
    
    else if(level->state == LEVEL_STATE_DIE) {
        Helm* heml = (Helm*)this->getChildByTag(HEML_TAG);
        CCNode* vMenuLost = (CCNode*)heml->getChildByTag(5);
        
        CCSprite* item7 = (CCSprite*)vMenuLost->getChildByTag(1);
        CCLabelBMFont* label7 = (CCLabelBMFont*)item7->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item7, vMenuLost->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item7->setColor(ccc3(200,200,200));
            label7->setColor(ccc3(50,50,50));
            this->mainMenu();
            return true;
        }
        
        CCSprite* item8 = (CCSprite*)vMenuLost->getChildByTag(2);
        CCLabelBMFont* label8 = (CCLabelBMFont*)item8->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item8, vMenuLost->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item8->setColor(ccc3(200,200,200));
            label8->setColor(ccc3(50,50,50));
            this->playAgain();
            return true;
        }
    }
    
    else if(level->state == LEVEL_STATE_PAUSE) {
        Helm* heml = (Helm*)this->getChildByTag(HEML_TAG);
        CCNode* vMenuPause = (CCNode*)heml->getChildByTag(6);
        
        CCSprite* item9 = (CCSprite*)vMenuPause->getChildByTag(1);
        CCLabelBMFont* label9 = (CCLabelBMFont*)item9->getChildByTag(1);
        if(Geometry::nodeContainsTouch(item9, vMenuPause->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            item9->setColor(ccc3(200,200,200));
            label9->setColor(ccc3(50,50,50));
            this->mainMenu();
            return true;
        }
        
        CCSprite* item10 = (CCSprite*)vMenuPause->getChildByTag(2);
        if(Geometry::nodeContainsTouch(item10, vMenuPause->convertToNodeSpace(heml->convertToNodeSpace(location)))) {
            this->pause();
            return true;
        }
    }
    return true;
}

