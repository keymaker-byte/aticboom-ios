//
//  Level.cpp
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

#include "Level.h"

namespace aticboom {
    Level::Level(Json::Value level) : cocos2d::CCNode(){
        
        this->name = level["name"].asString();
        this->world = level["world"].asInt();
        this->floorSize = level["floorSize"].asInt();
        this->levelHint = level["levelHint"].asInt();
        this->autorelease();
        
        int darkfloors[FLOOR_DARK_LIMIT];
        
        const Json::Value floors = level["floors"];
        for ( int index = 0; index < floors.size(); ++index ) {
            Floor* floor = new Floor(floors[index], this->world);
            if (floor->dark == 1)
                darkfloors[index] = 1;
            else 
                darkfloors[index] = 0;

            this->addChild(floor, floor->image < 5 ? 0 : -1, FLOOR_TAG + index+1);//ultimo piso mas atras por el efecto de viento
            
            if(index > 0 && (index + 1) % 4 == 0 && index < floors.size() - 1) {
                CCSprite* arrow = CCSprite::spriteWithSpriteFrameName(ARROW_PNG.c_str());
                arrow->setPosition(Geometry::getTilePosition(0, (index) * FLOORS_TILES_HEIGHT, ARROW_TILES_WIDTH, ARROW_TILES_HEIGHT));
                arrow->runAction(CCRepeatForever::actionWithAction(CCBlink::actionWithDuration(1, 2)));
                this->addChild(arrow, 4);
            }
            
            if(floor->type == FLOOR_TYPE_CLOSE) {
                CCParticleSystemPoint* fire = (CCParticleSystemPoint*)CCParticleSystemPoint::particleWithFile(Config::sharedConfig()->FLOOR_PARTICLE_FIRE.c_str());
                fire->setPosition( CCPoint(floor->getPosition().x, floor->getPosition().y - Config::sharedConfig()->TILE_HEIGHT * FLOORS_TILES_HEIGHT / 2 + Config::sharedConfig()->FLOOR_HEIGHT_MARGEN) );
                fire->setPositionType(kCCPositionTypeRelative);
                this->addChild(fire, 4, FIRE_TAG + index);
            }
        }
        this->mesh = new Mesh(this->floorSize);
        
        this->fancyCount = 0;
        const Json::Value fancies = level["fancies"];
        for ( int index = 0; index < fancies.size(); ++index ) {
            Fancy* fancy = new Fancy(fancies[index], this->world);
            this->addChild(fancy, 2, FANCY_TAG + index);
            this->fancyCount++;
        }
        const Json::Value keys = level["keys"];
        for ( int index = 0; index < keys.size(); ++index ) {
            Key* key = new Key(keys[index], this->world);
            int floorNumber = key->position[1] / FLOORS_TILES_HEIGHT;
            if ( darkfloors[floorNumber] == 1 )
                key->makeDark(); 
            this->addChild(key, 2);
            this->mesh->tiles[key->position[0]][key->position[1]].push_back(key);
        }
        const Json::Value holes = level["holes"];
        for ( int index = 0; index < holes.size(); ++index ) {
            Hole* hole = new Hole(holes[index], this->world);
            int floorNumber = hole->position[1] / FLOORS_TILES_HEIGHT;
            if ( darkfloors[floorNumber] == 1 )
                hole->makeDark();
            this->addChild(hole, 1);
            this->mesh->tiles[hole->position[0]][hole->position[1]].push_back(hole);
        }
        const Json::Value stairs = level["stairs"];
        for ( int index = 0; index < stairs.size(); ++index ) {
            Stair* stair = new Stair(stairs[index], this->world);
            int floorNumber = stair->position[1] / FLOORS_TILES_HEIGHT;
            if ( darkfloors[floorNumber] == 1 )
                stair->makeDark(); 
            this->addChild(stair, 1, STAIR_TAG + index);
            this->mesh->tiles[stair->position[0]][stair->position[1]].push_back(stair);
        }
        this->starSize = 0;
        const Json::Value stars = level["stars"];
        for ( int index = 0; index < stars.size(); ++index ) {
            Star* star = new Star(stars[index], this->world);
            int floorNumber = star->position[1] / FLOORS_TILES_HEIGHT;
            if ( darkfloors[floorNumber] == 1 )
                star->makeDark();            
            this->addChild(star, 2);
            this->mesh->tiles[star->position[0]][star->position[1]].push_back(star);
            this->starSize++;
        }
        this->extraBubblesSize = 0;
        const Json::Value extraBubbles = level["extraBubbles"];
        for ( int index = 0; index < extraBubbles.size(); ++index ) {
            ExtraBubble* extraBubble = new ExtraBubble(extraBubbles[index], this->world);
            int floorNumber = extraBubble->position[1] / FLOORS_TILES_HEIGHT;
            if ( darkfloors[floorNumber] == 1 )
                extraBubble->makeDark(); 
            this->addChild(extraBubble, 2);
            this->mesh->tiles[extraBubble->position[0]][extraBubble->position[1]].push_back(extraBubble);
            this->extraBubblesSize++;
        }
        const Json::Value extraRopes = level["extraRopes"];
        for ( int index = 0; index < extraRopes.size(); ++index ) {
            ExtraRope* extraRope = new ExtraRope(extraRopes[index], this->world);
            int floorNumber = extraRope->position[1] / Config::sharedConfig()->FLOOR_HEIGHT_MARGEN;
            if ( darkfloors[floorNumber] == 1 )
                extraRope->makeDark(); 
            this->addChild(extraRope, 2);
            this->mesh->tiles[extraRope->position[0]][extraRope->position[1]].push_back(extraRope);
        }
        const Json::Value exitJson = level["exit"];
        Exit* exit = new Exit(exitJson, this->world);
        this->addChild(exit, 4, EXIT_TAG);
        this->mesh->tiles[exit->position[0]][exit->position[1]].push_back(exit);
        const Json::Value playerJson = level["player"];
        Player* player = new Player(playerJson, this->world);
        this->addChild(player, 5, PLAYER_TAG);        
        
        const Json::Value texts = level["texts"];
        for ( int index = 0; index < texts.size(); ++index ) {
            Text* text = new Text(texts[index]);
            this->addChild(text, 4);
        }
        
        const Json::Value enemies = level["enemies"];
        for ( int index = 0; index < enemies.size(); ++index ) {
            Enemy* enemy = new Enemy(enemies[index], this->world);
            this->addChild(enemy, 2);
            enemy->move();
            this->mesh->tiles[enemy->position[0]][enemy->position[1]].push_back(enemy);
            for ( int i = 1; i <= ENEMY_TILES_RANGE ; i++) {
                if ( enemy->position[0]+i < this->mesh->tileColumns )
                    this->mesh->tiles[enemy->position[0]+i][enemy->position[1]].push_back(enemy);
                if ( enemy->position[0]-i >= 0)
                    this->mesh->tiles[enemy->position[0]-i][enemy->position[1]].push_back(enemy);
            }
        }
        const Json::Value fans = level["fans"];
        for ( int index = 0; index < fans.size(); index++ ) {
            Fan* fan = new Fan(fans[index], this->world);
            this->addChild(fan, 2);
            this->mesh->tiles[fan->position[0]][fan->position[1]].push_back(fan); 
            for ( int i = 1; i <= FAN_TILES_RANGE ; i++) {
                if ( fan->position[0]+i < this->mesh->tileColumns )
                    this->mesh->tiles[fan->position[0]+i][fan->position[1]].push_back(fan);
                if ( fan->position[0]-i >= 0)
                    this->mesh->tiles[fan->position[0]-i][fan->position[1]].push_back(fan);
            }
        }
        const Json::Value walls = level["walls"];
        for ( int index = 0; index < walls.size(); index++ ) {
            Wall* wall = new Wall(walls[index], this->world);
            int floorNumber = wall->position[1] / FLOORS_TILES_HEIGHT;
            if ( darkfloors[floorNumber] == 1 )
                wall->makeDark(); 
            this->addChild(wall, 2);
            this->mesh->tiles[wall->position[0]][wall->position[1]].push_back(wall);
            for ( int i = 1; i <= WALL_TILES_RANGE ; i++) {
                if ( wall->position[0]+i < this->mesh->tileColumns )
                    this->mesh->tiles[wall->position[0]+i][wall->position[1]].push_back(wall);
                if ( wall->position[0]-i >= 0)
                    this->mesh->tiles[wall->position[0]-i][wall->position[1]].push_back(wall);
            }
        }
        this->bubbleNumber = level["bubbleNumber"].asInt();
        const Json::Value bubbleValue = level["bubble"];
        for(int i = 0; i < this->bubbleNumber+this->extraBubblesSize; i++) {
            Bubble* bubble = new Bubble(bubbleValue, level["world"].asInt());
            bubble->setPosition(CCPoint(-Config::sharedConfig()->SCREEN_WIDTH-Config::sharedConfig()->SCREEN_WIDTH_MARGEN,Config::sharedConfig()->SCREEN_HEIGHT)); //lejos!
            this->addChild(bubble,5,BUBBLE_TAG+i);
        }
        const Json::Value buttons = level["buttons"];
        for (int index = 0; index < buttons.size(); ++index)
        {
            Button* button = new Button(buttons[index], this->world);
            int floorNumber = button->position[1] / Config::sharedConfig()->FLOOR_HEIGHT_MARGEN;
            if (darkfloors[floorNumber] == 1)
                button->makeDark();
            this->addChild(button, 2);
            this->mesh->tiles[button->position[0]][button->position[1]].push_back(button);
        }
        
        this->time = level["time"].asInt();
        this->totalTime = this->time;
        this->state = LEVEL_STATE_START;
    };
    
    
    
    Level::~Level() {
        delete this->mesh;
    };
    
    void Level::addChild(CCNode *child, int zOrder, int tag) {
        CCNode::addChild(child, zOrder, tag);
    }
    
    void Level::addChild(CCNode *child, int zOrder) {
        CCNode::addChild(child, zOrder);
    }
    
    void Level::addChild(CCNode *child) {
        CCNode::addChild(child);
    }
}