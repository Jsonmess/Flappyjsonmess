//
//  GameScene.cpp
//  FlappyJson
//
//  Created by Json on 14-7-18.
//
//

#include "GameScene.h"
#define  winsize CCDirector::sharedDirector()->getWinSize()
#define PTM_PATIO 32
GameScene::GameScene()
{
    
}

CCScene * GameScene::scene()
{
    CCScene *scene=CCScene::create();
    
    GameScene *layer=GameScene::create();
    
    scene->addChild(layer);
    return scene;
    
}
bool GameScene::init()
{
    if (!CCLayer::create()) {
        return false;
    }
    this->setTouchEnabled(true);
    this->InitWord();
    this->AddBackground();//添加背景
    this->AddBird(); //添加小鸟
    this->AddGround();//添加地面
    this->AddHelp();//添加提示
    scheduleUpdate(); //物理世界推演
    
    return true;
}

void GameScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    
    _Help->setVisible(false);
    
    CCLog("dian ji l ");
////    
    b2Body *thebody= _bird->GetBirdBody();

  //_bird->Get_bird()->setRotation(-M_PI_4);
    thebody->SetLinearVelocity(b2Vec2(0, 10.0f));
    CCLog("x--%f----y------%f-----angle----%f",thebody->GetPosition().x,thebody->GetPosition().y,thebody->GetAngle());
//    
}
void GameScene::AddHelp()
{
 CCSize size= winsize;
    CCSprite *Help=CCSprite::create("ready.png");
    Help->setPosition(ccp(size.width *0.5f ,size.height*0.5f));
    Help->setScaleY(1.8f);
    Help->setScaleX(2.0f);
    this->addChild(Help);
    _Help=Help;
}
void GameScene::AddGround()
{
    CCSize size=winsize;
    
   CCSprite *ground0=CCSprite::create("ground.png");
    _ground0=ground0;
    CCSprite *ground1=CCSprite::create("ground.png");
    _ground1=ground1;
    float thewith=ground0->getContentSize().width;
    ground0->setAnchorPoint(ccp(0, 0));
    ground1->setAnchorPoint(ccp(0, 0));
    ground0->setPosition(ccp(0, 0));
    ground1->setPosition(ccp(thewith, 0));
//
    ground0->setScaleY(1.7f);
    ground1->setScaleY(1.7f);
  
    
    
    
    //创建地面刚体
   /*
    其实只需要创建在地面上的一条横线即可
    */
    
    b2BodyDef ground_def;
    ground_def.type=b2_staticBody;
    ground_def.position.Set(size.width*0.5f/PTM_PATIO, _ground0->getPositionY()*1.7f/PTM_PATIO);
    b2Body *ground_body=_GameWorld->CreateBody(&ground_def);
    b2EdgeShape shap;
    shap.Set(b2Vec2(0,_ground0->getContentSize().height/PTM_PATIO), b2Vec2(size.width/PTM_PATIO, _ground0->getContentSize().height/PTM_PATIO));
    
    ground_body->CreateFixture(&shap, 0);

   
    
    ///-------------------------///
    this->addChild(ground0,2);
    this->addChild(ground1,2);
    
    this->schedule(schedule_selector(GameScene::Update_ground));
}
//定时刷新

void GameScene:: Update_ground(float delta)
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
void GameScene::AddBird()
{

        CCTexture2D *texture=  CCTextureCache::sharedTextureCache()->addImage("bird.png");

    Bird *thebird=new Bird();
    thebird->initWithTexture(texture, CCRectMake(0, 0, 32, 32));


   thebird->setPosition(CCPoint(winsize.width*1/4, winsize.height*0.5f));


    //设置b2body
    //创建小鸟刚体
    b2BodyDef bird_def;
    bird_def.type=b2_dynamicBody;
    bird_def.position.Set(thebird->getPositionX()/PTM_PATIO, thebird->getPositionY()/PTM_PATIO);
    bird_def.angle=0.0f;
    bird_def.linearDamping=0.4f;
    bird_def.userData=thebird;
    b2Body *bird_body=_GameWorld->CreateBody(&bird_def);
    b2PolygonShape birdshap;
    birdshap.SetAsBox(16.0f/PTM_PATIO, 16.0f/PTM_PATIO);
    
    b2FixtureDef fixture;
    fixture.shape=&birdshap;
    fixture.density=80.0f;
    bird_body->CreateFixture(&fixture);
    
    thebird->SetBirdBody(bird_body);
    
  
  _bird=thebird;
   this->addChild(thebird);
    
}


//初始化世界
void GameScene::InitWord()
{
     CCSize size= winsize;
    b2Vec2 gravity;
    gravity=b2Vec2(0, -10);
    b2World *GameWorld=new b2World(gravity);
    GameWorld->SetAllowSleeping(true);
    GameWorld->SetContinuousPhysics(true);
    _GameWorld=GameWorld;
    
    //创建以屏幕为范围的刚体
    b2BodyDef bodydef;
    bodydef.position.Set(0, 0);
    b2Body*screen=GameWorld->CreateBody(&bodydef);
    b2EdgeShape edgeshap;
    //下
    edgeshap.Set( b2Vec2(size.width/PTM_PATIO,0),b2Vec2(0,0));
    screen->CreateFixture(&edgeshap, 0);
    //上
    edgeshap.Set(b2Vec2(0,size.height/PTM_PATIO), b2Vec2(size.width/PTM_PATIO,size.height/PTM_PATIO));
    screen->CreateFixture(&edgeshap, 0);
    //左
    edgeshap.Set(b2Vec2(0,size.height/PTM_PATIO), b2Vec2(0,0));
    screen->CreateFixture(&edgeshap, 0);
    //右
    edgeshap.Set(b2Vec2(size.width/PTM_PATIO,size.height/PTM_PATIO), b2Vec2(size.width/PTM_PATIO,0));
    screen->CreateFixture(&edgeshap, 0);
    
}
void GameScene::AddBackground()
{
    CCSprite *backgound;
    int i=(CCRANDOM_0_1()>0.5 ? 0:1);
    CCSize size= winsize;
    switch (i) {
        case 0:
             backgound=CCSprite::create("background.png");
            break;
        case 1:
            backgound=CCSprite::create("heiye.png");
            break;
        default:
            break;
    }
    backgound->setPosition(CCPoint(size.width*0.5f, size.height*0.5f));
    backgound->setScaleX(size.width/backgound->getContentSize().width +0.1f);
    backgound->setScaleY(size.height/backgound->getContentSize().height +0.1f);
    this->addChild(backgound, 0, 0);
}

#pragma mark----更新刚体所对应的精灵的位置渲染
void GameScene::update(float dt)
{
    _GameWorld->Step(dt, 8, 3);
    //遍历查找有userdata的物体。取出并强制转化成精灵
    for (b2Body *b=_GameWorld->GetBodyList(); b; b=b->GetNext()) {
        
        if (b->GetUserData() != NULL) {
            
            //更新cocos2d中对应的精灵的位置或角度
           CCSprite* myActor = (CCSprite*)b->GetUserData();
            CCAssert(myActor!=NULL,"精灵为空");
            CCLog("%f",b->GetPosition().y);
            
           myActor->setPosition( CCPoint( b->GetPosition().x * PTM_PATIO, b->GetPosition().y * PTM_PATIO) );
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
       
       
    }
    
    
}

GameScene::~GameScene()
{
    
    delete _GameWorld;
    _GameWorld=NULL;
}
