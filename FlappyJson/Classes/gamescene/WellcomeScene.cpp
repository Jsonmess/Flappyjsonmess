//
//  WellcomeScene.cpp
//  FlappyJson
//
//  Created by Json on 14-7-16.
//
//

#include "WellcomeScene.h"
#include "GameScene.h"
#define  winsize CCDirector::sharedDirector()->getWinSize();
CCScene* WellcomeScene:: scene()
{

    CCScene *scene=CCScene ::create();
    WellcomeScene *wellcomenode=WellcomeScene::create();
    scene->addChild(wellcomenode);
    return scene;
}
bool WellcomeScene::init()
{
    if (!CCNode::init()) {
        return false;
    }
    //添加小鸟
    this->AddBird();
    //添加背景图
    this->AddBackGround();
   //添加地面
    this->AddGround();
    //添加菜单
    this->AddMenu();
    this->setTouchEnabled(true);
    return true;
    
}
void WellcomeScene::AddMenu()
{
    CCSize size=winsize;
 CCTexture2D *thetexture=CCTextureCache::sharedTextureCache()->addImage("menu.png");
   // CCSpriteBatchNode *sp_menus=CCSpriteBatchNode::createWithTexture(thetexture);
    
    CCSprite *sp_rate=CCSprite::createWithTexture(thetexture, CCRectMake(146, 300, 77, 48));
    sp_rate->setScaleX(1.4f);
    sp_rate->setScaleY(1.2f);
    //sp_rate->cocos2d::CCNode::setPosition(_bird->getPositionX(), _bird->getPositionY()-100.0f);
    //sp_menus->addChild(sp_rate);

    CCSprite *sp_play=CCSprite::createWithTexture(thetexture, CCRectMake(40, 379, 134, 79));
    sp_play->setScaleY(1.2f);
    sp_play->setScaleX(1.4f);
    //sp_play->setPosition(ccp(size.width/4, 1.7f*_ground0->getContentSize().height+(sp_play->getContentSize().height*1.2f*0.5f)));
    
    CCSprite *sp_highlevel=CCSprite::createWithTexture(thetexture,CCRectMake(205, 379, 134, 79));
    sp_highlevel->setScaleY(1.2f);
    sp_highlevel->setScaleX(1.4f);
   // sp_highlevel->setPosition(ccp(size.width*3/4, 1.7f*_ground0->getContentSize().height+(sp_play->getContentSize().height*1.2f*0.5f)));
//    this->addChild(sp_play);
//    this->addChild(sp_rate);
//    this->addChild(sp_highlevel);
    CCMenuItem *rate=CCMenuItemSprite::create(sp_rate, sp_rate, this, menu_selector(WellcomeScene::RateMe));
    CCMenuItem *play=CCMenuItemSprite::create(sp_play, sp_play, this, menu_selector(WellcomeScene::PlayGame));
    CCMenuItem *highlevel=CCMenuItemSprite::create(sp_highlevel, sp_highlevel, this, menu_selector(WellcomeScene::Highlevel));
    CCMenu *menu_rate=CCMenu::createWithItem(rate);
    CCMenu *menu_play=CCMenu::createWithItem(play);
     CCMenu *menu_highlevel=CCMenu::createWithItem(highlevel);
    menu_rate->setPosition(ccp(_bird->getPositionX()*0.95f, 3.7f*_ground0->getContentSize().height));
    menu_play->setPosition(ccp(size.width/5, 1.7f*_ground0->getContentSize().height+(sp_play->getContentSize().height*1.2f*0.5f)));
    menu_highlevel->setPosition(ccp(size.width*5/7, 1.7f*_ground0->getContentSize().height+(sp_play->getContentSize().height*1.2f*0.5f)));
    
    this->addChild(menu_highlevel,2);
    this->addChild(menu_play, 2);
    this->addChild(menu_rate,2);
}
//菜单事件
void WellcomeScene::RateMe()
{
    CCLog("rate");
}
void WellcomeScene::PlayGame()
{
    CCLog("play");
    SimpleAudioEngine ::sharedEngine()->playBackgroundMusic("sfx_swooshing.wav");
    CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}
void WellcomeScene::Highlevel()
{
    CCLog("showlevel");
}
//添加地面

void WellcomeScene::AddGround()
{
   // CCSize size= winsize;
    
    CCSprite *ground0=CCSprite::create("ground.png");
    _ground0=ground0;
    CCSprite *ground1=CCSprite::create("ground.png");
    _ground1=ground1;
    float thewith=ground0->getContentSize().width;
    ground0->setAnchorPoint(ccp(0, 0));
    ground1->setAnchorPoint(ccp(0, 0));
    ground0->setPosition(ccp(0, 0));
    ground1->setPosition(ccp(thewith, 0));

    ground0->setScaleY(1.7f);
    ground1->setScaleY(1.7f);
    this->addChild(ground0,0);
    this->addChild(ground1,0);
    
    this->schedule(schedule_selector(WellcomeScene::Update_ground));
 
}
//定时刷新

void WellcomeScene:: Update_ground(float delta)
{
    CCSize size=winsize;
    float width=_ground0->getContentSize().width;
    //滚动动画
    int speed=10;
    float ground0X=_ground0->getPosition().x;
    float ground1X=_ground1->getPosition().x;
    //同时移动
    ground0X-=speed;
    ground1X-=speed;
    //
    //CCLog("ground0X+width$  %f",(ground0X+width));
    if (ground0X<=-width) {
    
        ground1X=0;
        ground0X=size.width;
    
    
    }
    if (ground1X<=-width) {
    
        ground0X=0;
        ground1X= size.width;
    }
    
    _ground0->setPositionX(ground0X);
    _ground1->setPositionX(ground1X);
    //CCLog("ground0-----$  %d",(int)_ground0->getPositionX());
    //
    //CCLog("ground1-----$  %d",(int)_ground1->getPositionX());
    //CCLog("----------\n");
}
//添加小鸟
void WellcomeScene:: AddBird()
{
    CCSize size= CCDirector::sharedDirector()->getWinSize();
    CCTexture2D *thetexture=CCTextureCache::sharedTextureCache()->addImage("bird.png");
    
    
    CCArray *bird_fly=CCArray::createWithCapacity(3);
    for (int i=0; i<3; i++) {
        CCSpriteFrame *birdframe=CCSpriteFrame::createWithTexture(thetexture, CCRectMake(20+80*i, 1, 40, 50));
        bird_fly->addObject(birdframe);
        
        
    }
    
   
    //创建小鸟
    
    CCSprite *the_bird=CCSprite::createWithTexture(thetexture, CCRectMake(20, 1, 40, 50));
    _bird=the_bird;
    //CCSprite *the_bird=CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
    the_bird->setPosition(CCPoint(size.width*0.5f, size.height*0.5f-7.50f));
   the_bird->setScaleX(2.0f);
    the_bird->setScaleY(1.5f);

    //设置动画
    CCActionInterval *up=CCMoveTo::create(0.4f, ccp(the_bird->getPosition().x, the_bird->getPosition().y+15.0f));
    CCActionInterval *down=CCMoveTo::create(0.4f, ccp(the_bird->getPosition().x, the_bird->getPosition().y-30.0f));
    
    CCAnimation *animation=CCAnimation::createWithSpriteFrames(bird_fly,0.1f);
   
    CCAnimate *animate=CCAnimate::create(animation);
    CCSpawn *spawn=CCSpawn::create(up,down,animate,NULL);
    CCRepeatForever *forever=CCRepeatForever::create(spawn);
    the_bird->runAction(forever);
    this->addChild(the_bird,1);
    
    
}

//设置背景
void WellcomeScene:: AddBackGround()
{
    CCSize size= winsize;
    
    CCSprite *backgound=CCSprite::create("heiye.png");
    backgound->setPosition(CCPoint(size.width*0.5f, size.height*0.5f));
    backgound->setScaleX(size.width/backgound->getContentSize().width +0.1f);
    backgound->setScaleY(size.height/backgound->getContentSize().height +0.1f);
    this->addChild(backgound, 0, 0);
    CCSprite *logo=CCSprite::create("logo.png");
    logo->setPosition(ccp(_bird->getPosition().x, _bird->getPosition().y+140.0f));
    logo->setScale(1.4f);
    this->addChild(logo,0);
    
    CCLabelTTF *copyright=CCLabelTTF::create("(c) jsonmess 2014.7","FlappyBird/Abduction.ttf", 22.0f);
    copyright->setPosition(ccp(size.width*0.5f, size.height/8));
    
    copyright->setFontFillColor(ccWHITE);
    this->addChild(copyright,1);
}