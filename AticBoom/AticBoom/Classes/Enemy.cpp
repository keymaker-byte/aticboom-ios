//
//  Enemy.cpp
//  AticBoom
//
//  Created by Claudio Alvial on 1/19/12.
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

#include "Enemy.h"

namespace aticboom {
    
    using namespace cocos2d;
    
    Enemy::Enemy(Json::Value enemy, int world) : Enemy::GameObject(enemy, world) {
        this->speed = enemy["speed"].asDouble();
        this->tileWidth = ENEMY_TILES_WIDTH;
        this->tileHeight = ENEMY_TILES_HEIGHT;
        this->state = ENEMY_STATE_RIGHT;
        this->initAnimations();
        this->setTilePosition();
    };
    
    Enemy::~Enemy() {
        this->ANIMATION_ENEMY_RUN->release();
    };
    
    void Enemy::initAnimations() {
        char buffer [50];
        CCSpriteBatchNode* batch = CCSpriteBatchNode::batchNodeWithFile(ENEMY_PNG.c_str(), 120);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(ENEMY_PLIST.c_str());
        this->addChild(batch);
        sprintf (buffer, ENEMY_FRAME_A.c_str(), 1);
        CCSprite* pSprite = CCSprite::spriteWithSpriteFrameName(buffer);
        this->addChild(pSprite, 2, ENEMY_SPRITE_TAG);
        ANIMATION_ENEMY_RUN = new CCMutableArray<CCSpriteFrame*>();
        for(int i = 1; i <= 30; i++) {
            sprintf (buffer, ENEMY_FRAME_A.c_str(), i);
            CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(buffer);
            ANIMATION_ENEMY_RUN->addObject(frame);
        }
        this->runAnimationAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(CCAnimation::animationWithFrames(ANIMATION_ENEMY_RUN, 0.03), false)));
    }
    
    void Enemy::runAnimationAction(CCAction* action) {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(ENEMY_SPRITE_TAG);
        pSprite->runAction(action);
    }
    
    void Enemy::runMovingAction(CCAction* action){
        this->runAction(action);
    }
    
    void Enemy::hide() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(ENEMY_SPRITE_TAG);
        pSprite->stopAllActions();
        this->stopAllActions();
        this->runAction(CCHide::action());
    }
    
    void Enemy::setFlipRight() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(ENEMY_SPRITE_TAG);
        pSprite->setFlipX(false);
    }
    
    void Enemy::setFlipLeft() {
        CCSprite* pSprite = (CCSprite*)this->getChildByTag(ENEMY_SPRITE_TAG);
        pSprite->setFlipX(true);
    }
    
    void Enemy::move()
    {
        CCFiniteTimeAction* actionMove;
        CCFiniteTimeAction* actionMoveDone;
        switch (this->state) {
            case ENEMY_STATE_RIGHT:
                if ( safeToMove(this->position[0], this->position[1]) ) {
                    actionMove = CCMoveTo::actionWithDuration( this->speed, Geometry::getTilePosition(this->position[0] + 1, this->position[1], this->tileWidth, this->tileHeight));
                    actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Enemy::moveFinished));
                    this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                }
                break;
            case ENEMY_STATE_LEFT:
                if ( safeToMove(this->position[0], this->position[1]) ) {
                    actionMove = CCMoveTo::actionWithDuration( this->speed, Geometry::getTilePosition(this->position[0] - 1, this->position[1], this->tileWidth, this->tileHeight));
                    actionMoveDone = CCCallFuncN::actionWithTarget(this, callfuncN_selector(Enemy::moveFinished));
                    this->runMovingAction( CCSequence::actions(actionMove, actionMoveDone, NULL) );
                }
                break;
        }
    }
    
    
    void Enemy::moveFinished(CCNode* enemy) {
        switch (this->state) {
            case ENEMY_STATE_RIGHT:
                this->position[0]++;
                break;
            case ENEMY_STATE_LEFT:
                this->position[0]--;
                break;
        }
        updateGridPosition();
    }
    
    bool Enemy::safeToMove(int enemyX, int enemyY) {
        Level* level = (Level *)this->getParent();
        GameObject* obj;
        bool safe = true;
        if (this->state == ENEMY_STATE_RIGHT)
            enemyX += 2;
        else if (this->state == ENEMY_STATE_LEFT)
            enemyX -= 2;
        if(enemyX >= 0 && enemyX < level->mesh->tileColumns) {
            for(int i = level->mesh->tiles[enemyX][enemyY].size() - 1; i >= 0; i--) {
                obj = level->mesh->tiles[enemyX][enemyY][i];
                
                if(dynamic_cast<Hole*>(obj)) {
                    switch (this->state) {
                        case ENEMY_STATE_RIGHT:
                            this->state = ENEMY_STATE_LEFT;
                            this->setFlipLeft();
                            break;
                        case ENEMY_STATE_LEFT:
                            this->state = ENEMY_STATE_RIGHT;
                            this->setFlipRight();
                            break;
                    }
                    this->move();
                    safe = false;
                }
            }
        }
        return safe;
    }
    
    void Enemy::updateGridPosition(){
        Level* level = (Level *)this->getParent();
        GameObject* obj;
        int leftTile = this->position[0]-ENEMY_TILES_RANGE;
        int rightTile = this->position[0]+ENEMY_TILES_RANGE;
        if (this->state == ENEMY_STATE_LEFT) {
            if ( (rightTile >= 0) && (rightTile < level->mesh->tileColumns) ) {
                for(int i = level->mesh->tiles[rightTile][this->position[1]].size() - 1; i >= 0; i--) {
                    obj = level->mesh->tiles[rightTile][this->position[1]][i];
                    if(dynamic_cast<Enemy*>(obj)) {
                        level->mesh->tiles[rightTile][this->position[1]].erase(level->mesh->tiles[rightTile][this->position[1]].begin() + i);
                    }
                }
            }
            if ( (leftTile >= 0) && (leftTile < level->mesh->tileColumns) ) {
                level->mesh->tiles[leftTile][this->position[1]].push_back(this);
            }
        } else if (this->state == ENEMY_STATE_RIGHT) {
            if ( (leftTile >= 0) && (leftTile < level->mesh->tileColumns) ) {
                for(int i = level->mesh->tiles[leftTile][this->position[1]].size() - 1; i >= 0; i--) {
                    obj = level->mesh->tiles[leftTile][this->position[1]][i];
                    if(dynamic_cast<Enemy*>(obj)) {
                        level->mesh->tiles[leftTile][this->position[1]].erase(level->mesh->tiles[leftTile][this->position[1]].begin() + i);
                    }
                }
            }
            if ( (rightTile >= 0) && (rightTile < level->mesh->tileColumns) ) {
                level->mesh->tiles[rightTile][this->position[1]].push_back(this);
            }
        }
    }
    
}