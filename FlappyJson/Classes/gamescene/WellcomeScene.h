//
//  WellcomeScene.h
//  FlappyJson
//
//  Created by Json on 14-7-16.
//
//

#ifndef __FlappyJson__WellcomeScene__
#define __FlappyJson__WellcomeScene__

#include <iostream>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
using namespace CocosDenshion;

class WellcomeScene:public CCLayer
{
private:
    CCSprite *_bird;
    CCSprite *_ground0;
    CCSprite *_ground1;
    float ground0_x;
    float ground1_x;
    
public:
 static CCScene * scene();
    virtual bool init();
    
    CREATE_FUNC(WellcomeScene);
    
    void AddBackGround();//添加背景
    void AddBird();//添加小鸟
    void AddGround();//添加地面
    void Update_ground(float delta);
    void AddMenu();//添加菜单
    
    //菜单事件
    void PlayGame();
    void RateMe();
    void Highlevel();
    
    
};
#endif /* defined(__FlappyJson__WellcomeScene__) */
