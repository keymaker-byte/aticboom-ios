//
//  Geometry.h
//  AticBoom
//
//  Created by Juan Rodriguez on 24/12/2011.
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

#ifndef AticBoom_Geometry_h
#define AticBoom_Geometry_h

#include <vector>
#include <string>
#include "json.h"
#include <math.h>
#include "cocos2d.h"
#include "Config.h"

namespace aticboom {
    
    class Geometry  {
        
    public:
        static cocos2d::CCPoint getTilePosition(int tileX, int tileY, int tilesWidth, int tilesHeight) {
            int floor = Geometry::getCurrentFloor(tileY);
            return cocos2d::CCPointMake( Config::sharedConfig()->TILE_WIDTH *  (tileX + tilesWidth / 2) + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, Config::sharedConfig()->TILE_HEIGHT * (tileY + (tilesHeight / 2)) + Config::sharedConfig()->FLOOR_HEIGHT_MARGEN - (floor));
        }
        
        static cocos2d::CCPoint getFloorPosition(int index) {
            return cocos2d::CCPointMake(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, (Config::sharedConfig()->TILE_HEIGHT * FLOORS_TILES_HEIGHT / 2) * (2 * index + 1) - (index));
        }
        
        static int getTouchTileRow(int y) {
            y = Config::sharedConfig()->SCREEN_HEIGHT - y;
            return y / Config::sharedConfig()->TILE_HEIGHT;
        }
        
        static int getTouchTileAtFloor(int y) {
            y = Config::sharedConfig()->SCREEN_HEIGHT + Config::sharedConfig()->SCREEN_HEIGHT_MARGEN - y;
            y = y + (2 * ((y / (FLOORS_TILES_HEIGHT * Config::sharedConfig()->TILE_HEIGHT))) + 1);
            return ((y / Config::sharedConfig()->TILE_HEIGHT) / FLOORS_TILES_HEIGHT) * FLOORS_TILES_HEIGHT;
        }
        
        static int getTouchTileColumn(int x, int tilesWidth) {
            x = x - Config::sharedConfig()->SCREEN_WIDTH_MARGEN;
            if(x < Config::sharedConfig()->TILE_WIDTH + Config::sharedConfig()->TILE_WIDTH/4) {
                return 0;
            }
            if(x / Config::sharedConfig()->TILE_WIDTH == 1) {
                return 1;
            }
            return x / Config::sharedConfig()->TILE_WIDTH - tilesWidth/2;
        }
        
        static int getCurrentFloor(int y){
            return y / FLOORS_TILES_HEIGHT;
        }
        
        static cocos2d::CCPoint getScreenCenter() {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, Config::sharedConfig()->SCREEN_HEIGHT/2);
        }
        
        static cocos2d::CCPoint getScreenCenter(int scrolls) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, Config::sharedConfig()->SCREEN_HEIGHT/2 + Config::sharedConfig()->SCREEN_HEIGHT * scrolls);
        }
        
        static cocos2d::CCPoint getScreenCenterLeft(int left) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN - left, Config::sharedConfig()->SCREEN_HEIGHT/2 );
        }
        
        static cocos2d::CCPoint getScreenCenterRight(int right) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN + right, Config::sharedConfig()->SCREEN_HEIGHT/2 );
        }
        
        static cocos2d::CCPoint getScreenCenterAdjust(int left, int top) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN - left, Config::sharedConfig()->SCREEN_HEIGHT/2 - top );
        }
        
        static cocos2d::CCPoint getScreenBotomCenter() {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, 0);
        }
        
        static cocos2d::CCPoint getScreenBotomCenter(int positionUp) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, positionUp);
        }
        
        static cocos2d::CCPoint getScreenBotomCenterAdjust(int positionRight, int positionUp) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN + positionRight, positionUp);
        }
        
        static cocos2d::CCPoint getScreenBotomLeft(int marginLeft, int marginBottom) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH_MARGEN + marginLeft, marginBottom);
        }
        
        static cocos2d::CCPoint getScreenBotomRight(int marginRight, int marginBottom) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH_MARGEN + Config::sharedConfig()->SCREEN_WIDTH - marginRight, marginBottom);
        }
        
        static cocos2d::CCPoint getScreenUpCenter() {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, Config::sharedConfig()->SCREEN_HEIGHT - Config::sharedConfig()->TILE_HEIGHT);
        }
        
        static cocos2d::CCPoint getScreenUpCenter(int positionDown) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, Config::sharedConfig()->SCREEN_HEIGHT - Config::sharedConfig()->TILE_HEIGHT - positionDown);
        }
        
        static cocos2d::CCPoint getScreenUpCenterAdjust(int left, int top) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN - left, Config::sharedConfig()->SCREEN_HEIGHT - Config::sharedConfig()->TILE_HEIGHT - top);
        }
        
        static cocos2d::CCPoint getScreenCenterBotomOut(int tilesHeight) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, - tilesHeight * Config::sharedConfig()->TILE_HEIGHT * 2);
        }
        
        static cocos2d::CCPoint getScreenCenterBotomOut(int tilesHeight, int scrolls) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH/2 + Config::sharedConfig()->SCREEN_WIDTH_MARGEN, - tilesHeight * Config::sharedConfig()->TILE_HEIGHT * 2 + Config::sharedConfig()->SCREEN_HEIGHT * scrolls );
        }
        
        static cocos2d::CCPoint getScreenUpLeft(int marginLeft, int marginUp) {
            return cocos2d::CCPoint(Config::sharedConfig()->SCREEN_WIDTH_MARGEN + marginLeft, Config::sharedConfig()->SCREEN_HEIGHT - marginUp);
        }
        
        static cocos2d::CCPoint getCloudOrigin(int margin) {
            int randHeight = (rand()%Config::sharedConfig()->SCREEN_HEIGHT) + 1;
            if(margin == -1) {
                margin = (rand()%(Config::sharedConfig()->SCREEN_WIDTH + Config::sharedConfig()->SCREEN_WIDTH_MARGEN)) + 1;
            }
            else {
                margin = ((-Config::sharedConfig()->CLOUD_WIDTH/2) - Config::sharedConfig()->SCREEN_WIDTH_MARGEN);
            }
            return cocos2d::CCPoint(margin, randHeight);
        }
        
        static cocos2d::CCPoint getCloudEnd(int cloudY, int cloudx) {
            return cocos2d::CCPoint(cloudY + Config::sharedConfig()->SCREEN_WIDTH_MARGEN+Config::sharedConfig()->SCREEN_WIDTH, cloudx);
        }
        
        static cocos2d::CCSprite* makeMenuItem(string buttonLabel) {
            using namespace cocos2d;
            CCSprite* sprite = CCSprite::spriteWithSpriteFrameName(WORLD_BUTTON2.c_str());
            CCLabelBMFont* label = CCLabelBMFont::labelWithString(buttonLabel.c_str(), Config::sharedConfig()->BMFONT_NAME.c_str());
            label->setColor(ccc3(50,50,50));
            label->setPosition(CCPoint(Config::sharedConfig()->MENU_BUTTON_WIDTH/2, Config::sharedConfig()->MENU_BUTTON_HEIGHT/2));
            Geometry::curveText(label);
            sprite->addChild(label, 0, 1);
            return sprite;
        }
        
        static bool nodeContainsTouch(cocos2d::CCNode* node, cocos2d::CCPoint touch) {
            using namespace cocos2d;
            if(CCRect::CCRectContainsPoint(CCRectMake(node->getPosition().x - node->getContentSize().width /2, node->getPosition().y - node->getContentSize().height / 2, node->getContentSize().width, node->getContentSize().height), touch)) {
                return true;
            }
            return false;
        }
        
        static void curveText(cocos2d::CCLabelBMFont* label){
            using namespace cocos2d;
            for(int i = 0; i< label->getChildrenCount(); i++){
                CCSprite* PChar = (CCSprite*) label->getChildByTag(i);
                if(Config::sharedConfig()->SCREEN_WIDTH >= 640){
                    PChar->setPosition(CCPoint( PChar->getPosition().x,PChar->getPosition().y+(pow(label->getChildrenCount()/2,1.5)-pow(i,1.5))*label->getScale()));
                }else{
                    PChar->setPosition(CCPoint( PChar->getPosition().x,PChar->getPosition().y+(pow(label->getChildrenCount()/2,1.5)-pow(i,1.5))*label->getScale()/2));
                }
            }
        }
        
        static bool isNight(int worldId) {
            if((worldId - 1) % 2 != 0) {
                return true;
            }
            return false;
        }
    };
    
}

#endif
