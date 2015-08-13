//  CCScrollLayer.h
//  Museum
//
//  Created by GParvaneh on 29/12/2010.
//  Copyright 2010 All rights reserved.
//  Ported to C++ by Lior Tamam on 03/04/2011
#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Music.h"
#include "WorldSelectScene.h"
using namespace cocos2d;

class CCScrollLayer : public CCLayer 
{
protected:
	// Holds the current height and width of the screen
	int scrollHeight;
	int scrollWidth;
	
	// Holds the height and width of the screen when the class was inited
	int startHeight;
	int startWidth;
	
	
	
	// A count of the total screens available
	int totalScreens;
	
	// The initial point the user starts their swipe
	int startSwipe;	
    
	void moveToNextPage();
	void moveToPreviousPage();
    void makeSound();
	virtual void onExit();
	
	
public:
    
    virtual bool ccTouchBegan(CCTouch *touch, CCEvent *withEvent);
	virtual void ccTouchMoved(CCTouch *touch, CCEvent *withEvent);
	virtual void ccTouchEnded(CCTouch *touch, CCEvent *withEvent);
    
    // Holds the current page being displayed
	int currentScreen;
    
    void moveToPage(int page);
    void instantMoveToPage(int page);
	static CCScrollLayer* layerWithLayers(CCMutableArray<CCLayer*> *layers,int widthOffset);
	bool initWithLayers(CCMutableArray<CCLayer*> *layers,int widthOffset);
	LAYER_NODE_FUNC(CCScrollLayer);
};