//
//  Mesh.cpp
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


#include "Mesh.h"

namespace aticboom {
    
    using namespace cocos2d;
    
    Mesh::Mesh(int floorsNumber) {
        this->tileRows = Config::sharedConfig()->TILE_HEIGHT * floorsNumber * FLOORS_TILES_HEIGHT;
        this->tileColumns = Config::sharedConfig()->SCREEN_WIDTH / Config::sharedConfig()->TILE_WIDTH;
        for (int i = 0; i < this->tileColumns; i++) {
            vector<vector<GameObject* > > aux;
            for (int j = 0; j < this->tileRows; j++) {
                vector<GameObject* > aux2;
                aux.push_back(aux2);
            }
            this->tiles.push_back(aux);
        }
    };
    
    Mesh::~Mesh() {
    };
    
}
