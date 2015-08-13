//
//  AticBoomAppController.mm
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

#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#import "RootViewController.h"

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0 ];
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;
    [window addSubview: viewController.view];
    [window makeKeyAndVisible];
    [[UIApplication sharedApplication] setStatusBarHidden: YES];
    cocos2d::CCApplication::sharedApplication().run();
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene* scene = pDirector->getRunningScene();
    if(scene != NULL) {
        CCLayer* layer = (CCLayer*)scene->getChildByTag(1);
        if(dynamic_cast<GameScene*>(layer)) {
            GameScene* gameScene = (GameScene*) layer;
            if(!gameScene->paused) {
                gameScene->pause();
            }
        }
        else {
            pDirector->pause();
            SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
            SimpleAudioEngine::sharedEngine()->pauseAllEffects();
        }
    }
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene* scene = pDirector->getRunningScene();
    if(scene != NULL) {
        CCLayer* layer = (CCLayer*)scene->getChildByTag(1);
        if(!dynamic_cast<GameScene*>(layer)) {
            pDirector->resume();
            SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
        }
    }
    
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
	cocos2d::CCDirector::sharedDirector()->stopAnimation();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
	cocos2d::CCDirector::sharedDirector()->startAnimation();
}

- (void)applicationWillTerminate:(UIApplication *)application {
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
    [super dealloc];
}


@end

