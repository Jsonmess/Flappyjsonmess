//
//  GameScene.h
//  FlappyJson
//
//  Created by Json on 14-7-18.
//
//

#ifndef __FlappyJson__GameScene__
#define __FlappyJson__GameScene__

#include <iostream>
#include "cocos2d.h"
#include "Box2D.h"
#include "SimpleAudioEngine.h"
#include "CCPhysicsSprite.h"
#include "Bird.h"
using namespace cocos2d;
using namespace CocosDenshion;
using namespace cocos2d::extension;

class GameScene:public CCLayer
{
private:
    b2World *_GameWorld;
    CCSprite *_ground0;
    CCSprite *_ground1;
    float ground0_x;
    float ground1_x;
    Bird *_bird;
    CCSprite * _Help;
public:
    virtual bool init();
     GameScene();
    ~GameScene();
    CREATE_FUNC(GameScene);
    static CCScene *scene();
    void AddBird();//添加小鸟
  void AddGround();//添加地面
    void  Update_ground(float delta);
    void AddBackground();//添加背景
    void InitWord();//初始化世界
//    void AddPipe();//添加柱子
    void AddHelp();
 void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void update(float dt) ;
};
#endif /* defined(__FlappyJson__GameScene__) */
