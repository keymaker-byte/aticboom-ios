//
//  Player.cpp
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


#include "Player.h"

namespace aticboom {
    
    using namespace cocos2d;
    using namespace CocosDenshion;
    
    Player::Player(Json::Value player, int world) : Player::GameObject(player, world){
        this->speed = player["speed"].asDouble();
        this->tileWidth = PLAYER_TILES_WIDTH;
        this->tileHeight = PLAYER_TILES_HEIGHT;
        this->state = PLAYER_STATE_RIGHT;
        this->floor = player["position"]["y"].asInt();
        this->hasKey = false;
        this->hasStar = false;
        this->starNumber = 0;
        this->initAnimations();
        this->setTilePosition();
        
        this->floorsUpNumber = 0;
        this->floorsDownFollow = 0;
        this->floorsUpFollow = 0;
        this->floorsDownFollowOk = false;
        this->floorsUpFollowOk = false;
    };
    
    Player::~Player() {
        this->ANIMATION_PLAYER_RUN->release();
        this->ANIMATION_PLAYER_STAIR->release();
        this->ANIMATION_PLAYER_HOLE->release();
        this->ANIMATION_PLAYER_BUBBLE->release();
        this->ANIMATION_PLAYER_WIN->release();
        this->ANIMATION_PLAYER_THROW->release();
        ANIMATION_PLAYER_EXPLODE->release();
    };
    
    void Player::initAnimations() {
        char buffer [50];
        
        sprintf (buffer, PLAYER_FRAME_A.c_str(), 1);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        this->addChild(pSprite, 2, PLAYER_SPRITE_TAG);
        
        ANIMATION_PLAYER_RUN = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 15; i++) {
            sprintf (buffer, PLAYER_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_PLAYER_RUN->addObject(frame);
        }
        
        ANIMATION_PLAYER_STAIR = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 15; i++) {
            sprintf (buffer, PLAYER_FRAME_B.c_str() , i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_PLAYER_STAIR->addObject(frame);
        }
        
        ANIMATION_PLAYER_BUBBLE = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 15; i++) {
            sprintf (buffer, PLAYER_FRAME_D.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_PLAYER_BUBBLE->addObject(frame);
        }
        
        ANIMATION_PLAYER_HOLE = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 15; i++) {
            sprintf (buffer, PLAYER_FRAME_C.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_PLAYER_HOLE->addObject(frame);
        }
        
        ANIMATION_PLAYER_THROW = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 15; i++) {
            sprintf (buffer, PLAYER_FRAME_E.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_PLAYER_THROW->addObject(frame);
        }
        
        ANIMATION_PLAYER_WIN = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 15; i++) {
            sprintf (buffer, PLAYER_FRAME_F.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_PLAYER_WIN->addObject(frame);
        }
        
        ANIMATION_PLAYER_EXPLODE = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 20; i <= 20; i++) {
            sprintf (buffer, PLAYER_FRAME_G.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_PLAYER_EXPLODE->addObject(frame);
        }
        
        CCParticleSystemPoint* smoke = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->PLAYER_PARTICLE_SMOKE.c_str());
        smoke->setPosition( CCPoint(Config::sharedConfig()->TILE_WIDTH * PLAYER_TILES_WIDTH / 4, Config::sharedConfig()->TILE_HEIGHT * PLAYER_TILES_HEIGHT / 4 + Config::sharedConfig()->PLAYER_SMOKE_HEIGHT_MARGEN) );
        this->addChild(smoke, 1, PLAYER_SMOKE_TAG);
        
        this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
    } 
    
    void Player::runAnimationAction(CCAction* action) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(PLAYER_SPRITE_TAG);
        pSprite->runAction(action);
    }
    
    void Player::runMovingAction(CCAction* action){
        this->runAction(action);
    }
    
    void Player::hide() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(PLAYER_SPRITE_TAG);
        pSprite->stopAllActions();
        this->stopAllActions();
        this->runAction(CCHide::action());
    }
    
    void Player::setFlipRight() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(PLAYER_SPRITE_TAG);
        pSprite->setFlipX(false);
        
        CCParticleSystemPoint* smoke = (CCParticleSystemPoint*)this->getChildByTag(PLAYER_SMOKE_TAG);
        smoke->setPosition( CCPoint(Config::sharedConfig()->TILE_WIDTH * PLAYER_TILES_WIDTH / 4, Config::sharedConfig()->TILE_HEIGHT * PLAYER_TILES_HEIGHT / 4 + Config::sharedConfig()->PLAYER_SMOKE_HEIGHT_MARGEN) );
    }
    
    void Player::setFlipLeft() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(PLAYER_SPRITE_TAG);
        pSprite->setFlipX(true);
        
        CCParticleSystemPoint* smoke = (CCParticleSystemPoint*)this->getChildByTag(PLAYER_SMOKE_TAG);
        smoke->setPosition( CCPoint(-1 * Config::sharedConfig()->TILE_WIDTH * PLAYER_TILES_WIDTH / 4, Config::sharedConfig()->TILE_HEIGHT * PLAYER_TILES_HEIGHT / 4 + Config::sharedConfig()->PLAYER_SMOKE_HEIGHT_MARGEN) );
    }
    
    void Player::move()
    {
        Level* level = (Level *)this->getParent();
        Floor* currentFloor = (Floor *)level->getChildByTag(FLOOR_TAG + this->floor + 1);
        CCFiniteTimeAction* actionMove;
        CCFiniteTimeAction* actionMoveDone;
        switch (this->state) {
            case PLAYER_STATE_RIGHT:
                actionMove = CCMoveTo::actionWithDuration( this->speed * currentFloor->resRight, Geometry::getTilePosition(this->position[0] + 1, this->position[1], this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_RIGHT_STAIR:
                actionMove = CCMoveTo::actionWithDuration( this->speed * FLOORS_TILES_HEIGHT , Geometry::getTilePosition(this->position[0], this->position[1] + FLOORS_TILES_HEIGHT, this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_RIGHT_HOLE:
                actionMove = CCMoveTo::actionWithDuration( this->speed * FLOORS_TILES_HEIGHT / 4, Geometry::getTilePosition(this->position[0], this->position[1] - FLOORS_TILES_HEIGHT, this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_RIGHT_BUBBLE:
                actionMove = CCMoveTo::actionWithDuration( this->speed * FLOORS_TILES_HEIGHT , Geometry::getTilePosition(this->position[0], this->position[1] + FLOORS_TILES_HEIGHT, this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_RIGHT_BUBBLE_PLUS:
                actionMove = CCMoveTo::actionWithDuration( this->speed * FLOORS_TILES_HEIGHT , Geometry::getTilePosition(this->position[0], this->position[1] + FLOORS_TILES_HEIGHT*2, this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_LEFT:
                actionMove = CCMoveTo::actionWithDuration( this->speed * currentFloor->resLeft  , Geometry::getTilePosition(this->position[0] - 1, this->position[1], this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_LEFT_STAIR:
                actionMove = CCMoveTo::actionWithDuration( this->speed * FLOORS_TILES_HEIGHT, Geometry::getTilePosition(this->position[0], this->position[1] + FLOORS_TILES_HEIGHT, this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_LEFT_HOLE:
                actionMove = CCMoveTo::actionWithDuration( this->speed * FLOORS_TILES_HEIGHT / 4, Geometry::getTilePosition(this->position[0], this->position[1] - FLOORS_TILES_HEIGHT, this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_LEFT_BUBBLE:
                actionMove = CCMoveTo::actionWithDuration( this->speed * FLOORS_TILES_HEIGHT, Geometry::getTilePosition(this->position[0], this->position[1] + FLOORS_TILES_HEIGHT, this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
            case PLAYER_STATE_LEFT_BUBBLE_PLUS:
                actionMove = CCMoveTo::actionWithDuration( this->speed * FLOORS_TILES_HEIGHT, Geometry::getTilePosition(this->position[0], this->position[1] + FLOORS_TILES_HEIGHT*2, this->tileWidth, this->tileHeight));
                actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::moveFinished));
                this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                break;
        }
    }
    
    
    void Player::moveFinished(CCNode* player)
    {
        Level* level = (Level *)this->getParent();
        GameScene* gameScene = (GameScene *)level->getParent();
        switch (this->state) {
            case PLAYER_STATE_RIGHT:
                this->position[0]++;
                this->floorsUpFollow = 0;
                this->floorsDownFollow = 0;
                if(!this->checkColision()) {
                    if(this->position[0] >= level->mesh->tileColumns - 2) {
                        this->state = PLAYER_STATE_LEFT;
                        this->setFlipLeft();
                        this->move();
                    }
                    else {
                        this->move();
                    }
                }
                break;
            case PLAYER_STATE_RIGHT_BUBBLE:
                this->position[1] += FLOORS_TILES_HEIGHT;
                this->clearFloor(this->floor);
                this->floor++;
                this->floorsUpNumber++;
                this->floorsUpFollowOk = this->floorsUpFollowOk || ++this->floorsUpFollow >= 3;
                this->floorsDownFollow = 0;
                if(!this->checkColision()) {
                    this->state = PLAYER_STATE_RIGHT;
                    this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
                    this->setFlipRight();
                    this->move();
                    
                }
                break;
            case PLAYER_STATE_RIGHT_BUBBLE_PLUS:
                this->position[1] += FLOORS_TILES_HEIGHT*2;
                this->clearFloor(this->floor);
                this->floor+=2;
                this->floorsUpNumber+=2;
                this->floorsUpFollowOk = this->floorsUpFollowOk || (this->floorsUpFollow += 2) >= 3;
                this->floorsDownFollow = 0;
                if(!this->checkColision()) {
                    this->state = PLAYER_STATE_RIGHT;
                    this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
                    this->setFlipRight();
                    this->move();
                }
                break;
            case PLAYER_STATE_RIGHT_STAIR:
                this->position[1] += FLOORS_TILES_HEIGHT;
                this->clearFloor(this->floor);
                this->floor++;
                this->floorsUpNumber++;
                this->floorsUpFollowOk = this->floorsUpFollowOk || ++this->floorsUpFollow >= 3;
                this->floorsDownFollow = 0;
                this->setFlipLeft();
                if(!this->checkColision()) {
                    this->state = PLAYER_STATE_LEFT;
                    this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
                    this->move();
                }
                break;
            case PLAYER_STATE_RIGHT_HOLE:
                this->position[1] -= FLOORS_TILES_HEIGHT;
                this->clearFloor(this->floor);
                this->floor--;
                this->floorsUpFollow = 0;
                this->floorsDownFollowOk = this->floorsDownFollowOk || ++this->floorsDownFollow >= 2;
                if(!this->checkColision()) {
                    this->state = PLAYER_STATE_RIGHT;
                    this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
                    this->setFlipRight();
                    this->move();
                }
                break;
            case PLAYER_STATE_LEFT:
                this->position[0]--;
                this->floorsUpFollow = 0;
                this->floorsDownFollow = 0;
                if(!this->checkColision()) {
                    if(this->position[0] <= -2) {
                        this->state = PLAYER_STATE_RIGHT;
                        this->setFlipRight();
                        this->move();
                    }
                    else {
                        this->move();
                    }
                }
                break;
            case PLAYER_STATE_LEFT_BUBBLE:
                this->position[1] += FLOORS_TILES_HEIGHT;
                this->clearFloor(this->floor);
                this->floor++;
                this->floorsUpNumber++;
                this->floorsUpFollowOk = this->floorsUpFollowOk || ++this->floorsUpFollow >= 3;
                this->floorsDownFollow = 0;
                if(!this->checkColision()) {
                    this->state = PLAYER_STATE_LEFT;
                    this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
                    this->setFlipLeft();
                    this->move();
                }
                break;
            case PLAYER_STATE_LEFT_BUBBLE_PLUS:
                this->position[1] += FLOORS_TILES_HEIGHT*2;
                this->clearFloor(this->floor);
                this->floor+=2;
                this->floorsUpNumber+=2;
                this->floorsUpFollowOk = this->floorsUpFollowOk || (this->floorsUpFollow += 2) >= 3;
                this->floorsDownFollow = 0;
                if(!this->checkColision()) {
                    this->state = PLAYER_STATE_LEFT;
                    this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
                    this->setFlipLeft();
                    this->move();
                }
                break;
            case PLAYER_STATE_LEFT_STAIR:
                this->position[1] += FLOORS_TILES_HEIGHT;
                this->clearFloor(this->floor);
                this->floor++;
                this->floorsUpNumber++;
                this->floorsUpFollowOk = this->floorsUpFollowOk || ++this->floorsUpFollow >= 3;
                this->floorsDownFollow = 0;
                this->setFlipRight();
                if(!this->checkColision()) {
                    this->state = PLAYER_STATE_RIGHT;
                    this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
                    this->move();
                }
                break;
            case PLAYER_STATE_LEFT_HOLE:
                this->position[1] -= FLOORS_TILES_HEIGHT;
                this->clearFloor(this->floor);
                this->floor--;
                this->floorsUpFollow = 0;
                this->floorsDownFollowOk = this->floorsDownFollowOk || ++this->floorsDownFollow >= 2;
                if(!this->checkColision()) {
                    this->state = PLAYER_STATE_LEFT;
                    this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_RUN, 0.06), false)));
                    this->setFlipLeft();
                    this->move();
                }
                break;
        }
        
        if ( checkForFire() ) {
            gameScene->funlose();
        }
    }
    
    bool Player::checkForFire() {
        Level* level = (Level *)this->getParent();
        Floor* floor = (Floor *)level->getChildByTag(FLOOR_TAG+this->floor+1);
        
        if (floor->type == 1) {
            return true;
        } else {
            return false;
        }
    }
    
    void Player::clearFloor(int floorNumber) {
        Level* level = (Level *)this->getParent();        
        for (int i = 0; i < level->fancyCount; i++) {
            Fancy* fancy = (Fancy *) level->getChildByTag(FANCY_TAG + i);
            if(fancy->floor == floorNumber) {
                fancy->dissapear();
            }
        }
    }

    bool Player::checkColision() {
        Level* level = (Level *)this->getParent();
        GameScene* gameScene = (GameScene *)level->getParent();
        Hud* hud = (Hud *)gameScene->getChildByTag(HUD_TAG);
        Rope* rope = (Rope *)gameScene->getChildByTag(ROPE_TAG);
        bool upFloorClosed = false;
        int bubblePower = 1;
        if(this->floor < level->floorSize - 1) {
            Floor* upFloor = (Floor *)level->getChildByTag(FLOOR_TAG + this->floor + 2);
            if(upFloor->type == FLOOR_TYPE_CLOSE) {
                upFloorClosed = true;
            }
        }
        GameObject* obj;
        bool movingObject = false;
        Bubble * jumpedbubble = NULL;
        bool activateJumpedBubble = false;
        if(this->position[0] >= 0 && this->position[0] < level->mesh->tileColumns) {
            for(int i = level->mesh->tiles[this->position[0]][this->position[1]].size() - 1; i >= 0; i--) {
                obj = level->mesh->tiles[this->position[0]][this->position[1]][i];
                if(dynamic_cast<Key*>(obj)) {
                    Key* key = (Key *) obj;
                    level->mesh->tiles[this->position[0]][this->position[1]].erase(level->mesh->tiles[this->position[0]][this->position[1]].begin() + i);
                    key->grab();
                    Floor* upFloor = (Floor *)level->getChildByTag(FLOOR_TAG + key->floorIndex + 1);
                    upFloor->open();
                    upFloorClosed = false;
                    this->hasKey = true;
                    if(jumpedbubble != NULL) {
                        activateJumpedBubble = true;
                    }
                }
                if(dynamic_cast<Star*>(obj)) {
                    Star* star = (Star *) obj;
                    level->mesh->tiles[this->position[0]][this->position[1]].erase(level->mesh->tiles[this->position[0]][this->position[1]].begin() + i);
                    star->grab();
                    this->starNumber++;
                    if(this->starNumber == level->starSize) {
                        this->hasStar = true;
                    }
                    gameScene->drawInformation();
                }
                if(dynamic_cast<ExtraBubble*>(obj)) {
                    ExtraBubble* extraBubble = (ExtraBubble *) obj;
                    level->mesh->tiles[this->position[0]][this->position[1]].erase(level->mesh->tiles[this->position[0]][this->position[1]].begin() + i);
                    extraBubble->grab();
                    hud->addBubble();
                    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_BUBBLE.c_str())); 
                }
                if(dynamic_cast<ExtraRope*>(obj)) {
                    ExtraRope* extraRope = (ExtraRope *) obj;
                    level->mesh->tiles[this->position[0]][this->position[1]].erase(level->mesh->tiles[this->position[0]][this->position[1]].begin() + i);
                    extraRope->grab();
                    if(level->time + extraRope->extraTime >= level->totalTime - 1) {
                        level->time = level->totalTime - 1;
                    }
                    else {
                        level->time += extraRope->extraTime;
                    }
                    
                    rope->addRope(level->time);
                    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER1.c_str()));
                }
                if(dynamic_cast<Exit*>(obj)) {
                    level->state = LEVEL_STATE_WIN;
                    gameScene->paused = true;
                    this->setFlipLeft();
                    CCFiniteTimeAction* actionPlayerA = CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_THROW, 0.06), false);
                    CCFiniteTimeAction* actionDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::throwBomb));
                    this->runAnimationAction(CCSequence::actions(actionPlayerA, actionDone, NULL));
                    CCParticleSystemPoint* smoke = (CCParticleSystemPoint*)this->getChildByTag(PLAYER_SMOKE_TAG);
                    smoke->stopSystem();
                    movingObject =  true;
                }
                if (dynamic_cast<Button*>(obj))
                {
                    Button* button = (Button *) obj;
                    button->press();
                    Stair* stair = (Stair *)level->getChildByTag(STAIR_TAG + button->stairIndex);
                    stair->switchPosition();
                    SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_PAPER2.c_str()));
                }
                if(movingObject) {
                    continue;
                }
                
                if(dynamic_cast<Bubble*>(obj) || activateJumpedBubble) {
                        Bubble * bubble = activateJumpedBubble ? jumpedbubble : (Bubble *) obj;
                        level->mesh->tiles[this->position[0]][this->position[1]].erase(level->mesh->tiles[this->position[0]][this->position[1]].begin() + i);
                        switch (this->state) {
                            case PLAYER_STATE_RIGHT:
                            case PLAYER_STATE_RIGHT_BUBBLE:
                            case PLAYER_STATE_RIGHT_BUBBLE_PLUS:
                            case PLAYER_STATE_RIGHT_HOLE:
                            case PLAYER_STATE_LEFT_STAIR:
                                if ( checkForFans() ) {
                                    bubblePower = 2;
                                    this->state = PLAYER_STATE_RIGHT_BUBBLE_PLUS;
                                    if(this->floor == 2 || this->floor == 3|| this->floor == 6 || this->floor == 7) {
                                        gameScene->scrollUp();
                                    }
                                } else {
                                    this->state = PLAYER_STATE_RIGHT_BUBBLE;
                                    if(this->floor == 3 || this->floor == 7) {
                                        gameScene->scrollUp();
                                    }
                                }
                                this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_BUBBLE, 0.06), false)));
                                
                                break;
                            case PLAYER_STATE_LEFT:
                            case PLAYER_STATE_LEFT_BUBBLE:
                            case PLAYER_STATE_LEFT_BUBBLE_PLUS:
                            case PLAYER_STATE_LEFT_HOLE:
                            case PLAYER_STATE_RIGHT_STAIR:
                                if ( checkForFans() ) {
                                    bubblePower = 2;
                                    this->state = PLAYER_STATE_LEFT_BUBBLE_PLUS;
                                    if(this->floor == 2 || this->floor == 3|| this->floor == 6 || this->floor == 7) {
                                        gameScene->scrollUp();
                                    }
                                } else {
                                    this->state = PLAYER_STATE_LEFT_BUBBLE;
                                    if(this->floor == 3 || this->floor == 7) {
                                        gameScene->scrollUp();
                                    }
                                }
                                this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_BUBBLE, 0.06), false)));
                                break;
                        }
                        this->move();
                        
                        bubble->moveUp(this->speed,bubblePower);
                        movingObject =  true;
                }
                
                if(dynamic_cast<Stair*>(obj)) {
                    Stair* stair = (Stair*) obj;
                    if (stair->type == 0) {
                        switch (this->state) {
                            case PLAYER_STATE_RIGHT:
                            case PLAYER_STATE_RIGHT_BUBBLE:
                            case PLAYER_STATE_RIGHT_BUBBLE_PLUS:
                            case PLAYER_STATE_RIGHT_HOLE:
                            case PLAYER_STATE_LEFT_STAIR:
                                this->state = PLAYER_STATE_RIGHT_STAIR;
                                this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_STAIR, 0.06), false)));
                                if(this->floor == 3 || this->floor == 7) {
                                    gameScene->scrollUp();
                                }
                                stair->doorOpenLeft();
                                break;
                            case PLAYER_STATE_LEFT:
                            case PLAYER_STATE_LEFT_BUBBLE:
                            case PLAYER_STATE_LEFT_BUBBLE_PLUS:
                            case PLAYER_STATE_LEFT_HOLE:
                            case PLAYER_STATE_RIGHT_STAIR:
                                this->state = PLAYER_STATE_LEFT_STAIR;
                                this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_STAIR, 0.06), false)));
                                if(this->floor == 3 || this->floor == 7) {
                                    gameScene->scrollUp();
                                }
                                stair->doorOpenRight();
                                break;
                        }
                        this->move();
                        movingObject =  true;
                    }
                }
                if(dynamic_cast<Hole*>(obj)) {
                    switch (this->state) {
                        case PLAYER_STATE_RIGHT:
                        case PLAYER_STATE_RIGHT_BUBBLE:
                        case PLAYER_STATE_RIGHT_BUBBLE_PLUS:
                        case PLAYER_STATE_RIGHT_HOLE:
                        case PLAYER_STATE_LEFT_STAIR:
                            this->state = PLAYER_STATE_RIGHT_HOLE;
                            this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_HOLE, 0.06), false)));
                            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_FALL.c_str()));
                            if(this->floor == 4 || this->floor == 8) {
                                gameScene->scrollDown();
                            }
                            break;
                        case PLAYER_STATE_LEFT:
                        case PLAYER_STATE_LEFT_BUBBLE:
                        case PLAYER_STATE_LEFT_BUBBLE_PLUS:    
                        case PLAYER_STATE_LEFT_HOLE:
                        case PLAYER_STATE_RIGHT_STAIR:
                            this->state = PLAYER_STATE_LEFT_HOLE;
                            this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_HOLE, 0.06), false)));
                            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_FALL.c_str()));
                            if(this->floor == 4 || this->floor == 8) {
                                gameScene->scrollDown();
                            }
                            break;
                    }
                    this->move();
                    movingObject =  true;
                }
                
                if(dynamic_cast<Wall*>(obj)) {
                    switch (this->state) {
                        case PLAYER_STATE_RIGHT:
                            this->setFlipLeft();
                            this->state = PLAYER_STATE_LEFT;
                            break;
                        case PLAYER_STATE_RIGHT_BUBBLE:
                        case PLAYER_STATE_RIGHT_BUBBLE_PLUS:
                            this->state = PLAYER_STATE_RIGHT_HOLE;
                            this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_HOLE, 0.06), false)));
                            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_FALL.c_str()));
                            break;   
                        case PLAYER_STATE_LEFT:
                            this->setFlipRight();
                            this->state = PLAYER_STATE_RIGHT;
                            break;                            
                        case PLAYER_STATE_LEFT_BUBBLE:
                        case PLAYER_STATE_LEFT_BUBBLE_PLUS:
                            this->state = PLAYER_STATE_LEFT_HOLE;
                            this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_HOLE, 0.06), false)));
                            SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_FALL.c_str()));
                            break;
                            
                    }
                    this->move();
                    movingObject =  true;
                }

                if(dynamic_cast<Enemy*>(obj)) {
                    this->explode();
                    movingObject =  true;
                }
                
            }       
        }
        return movingObject;
    }
    
    bool Player::checkForFans()
    {
        Level* level = (Level *)this->getParent();
        GameObject* obj;
        
        if(this->position[0] >= 0 && this->position[0] < level->mesh->tileColumns) {
            for(int i = level->mesh->tiles[this->position[0]][this->position[1]].size() - 1; i >= 0; i--) {
                obj = level->mesh->tiles[this->position[0]][this->position[1]][i];
                if(dynamic_cast<Fan*>(obj)) {
                    return true;
                }
            }
            
        }
    
        return false;     
    }
    
    void Player::throwBomb(CCNode* player)
    {
        this->stopAllActions();
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(PLAYER_SPRITE_TAG);
        pSprite->stopAllActions();
        
        Level* level = (Level *)this->getParent();
        Exit* exit = (Exit *)level->getChildByTag(EXIT_TAG);
        GameScene* gameScene = (GameScene *)level->getParent();

        Rope* rope = (Rope *)gameScene->getChildByTag(ROPE_TAG);
        rope->stopRope();
        
        exit->finish();
        
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_SPLASH.c_str()));
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(this->hasStar ? SOUND_CELEBRATION1.c_str() : SOUND_CELEBRATION2.c_str()));
        
        CCFiniteTimeAction* actionPlayerA = CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_WIN, 0.06), false);
        CCFiniteTimeAction* actionDone = CCCallFuncN::actionWithTarget(gameScene, callfuncN_selector(GameScene::winLevel));
        CCFiniteTimeAction* actionForever = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::laughForever));
        this->runAnimationAction(CCSequence::actions(actionPlayerA, actionDone, actionForever, NULL));
        
        if(this->hasStar) {
            CCParticleSystemPoint* fireworks = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->PLAYER_PARTICLE_FIREWORKS.c_str());
            fireworks->setPosition( CCPoint(0, PLAYER_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT) );
            this->addChild(fireworks, 0);
        }
    }
    
    void Player::laughForever(CCNode* player)
    {
        this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_WIN, 0.06))));
    }
    
    void Player::explode()
    {
        this->stopAllActions();
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(PLAYER_SPRITE_TAG);
        pSprite->stopAllActions();
        
        CCParticleSystemPoint* smoke = (CCParticleSystemPoint*)this->getChildByTag(PLAYER_SMOKE_TAG);
        smoke->stopSystem();
        
        Level* level = (Level *)this->getParent();
        GameScene* gameScene = (GameScene *)level->getParent();
        level->state = LEVEL_STATE_DIE;
        level->reorderChild(this, 7);
        
        Rope* rope = (Rope *)gameScene->getChildByTag(ROPE_TAG);
        rope->explode();
        
        CCFiniteTimeAction* scaleA = CCScaleTo::actionWithDuration(0, 0.5);
        CCFiniteTimeAction* scaleB = CCScaleTo::actionWithDuration(0.6, 1);
        CCFiniteTimeAction* actionPlayerA = CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_PLAYER_EXPLODE, 0), false);
        CCFiniteTimeAction* actionMoveCenter = CCMoveTo::actionWithDuration( 0.6, Geometry::getScreenCenter(gameScene->scroll));
        CCFiniteTimeAction* actionMoveDown = CCMoveTo::actionWithDuration( 10, Geometry::getScreenCenterBotomOut(this->tileHeight, gameScene->scroll));
        CCFiniteTimeAction* actionDone = CCCallFuncN::actionWithTarget(gameScene, callfuncN_selector(GameScene::loseLevel));
        CCFiniteTimeAction* actionDoneB = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Player::fallDown));
        this->runAnimationAction(CCSequence::actions(actionPlayerA, scaleA, scaleB, actionDone, NULL));
        this->runMovingAction( CCSequence::actions(actionMoveCenter, actionDoneB, actionMoveDown, NULL));
        
        CCParticleSystemPoint* explotion = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->PLAYER_PARTICLE_EXPLODE.c_str());
        explotion->setPosition( CCPoint(0,0) );
        this->addChild(explotion, 0);
        CCParticleSystemPoint* explotionSmoke = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->PLAYER_PARTICLE_EXPLODESMOKE.c_str());
        explotionSmoke->setPosition( CCPoint(0,0) );
        this->addChild(explotionSmoke, 0);
        CCParticleSystemPoint* explotionShip = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->SHIP_PARTICLE_EXPLODE.c_str());
        explotionShip->setPosition(CCPoint(0,0));
        this->addChild(explotionShip, 0);
        
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_BOMB.c_str()));
        AticBoomObjC::shared()->vibrate();
    }
    
    void Player::fallDown(CCNode* player)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(CCFileUtils::fullPathFromRelativePath(SOUND_SCREEN.c_str()));
    }
    
}