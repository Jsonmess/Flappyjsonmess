//
//  Bird.cpp
//  FlappyJson
//
//  Created by Json on 14-7-21.
//
//

#include "Bird.h"
#define PTM_RATIO 32
b2Body * Bird:: GetBirdBody()
{
    return birdBody;
}

void Bird::SetBirdBody(b2Body *pBody)
{
    birdBody=pBody;
}
Bird::Bird()
{
    runtheAction();
}
bool Bird::isDirty(void)
{
    return true;
}
void Bird::runtheAction()
{
    
    
    CCTexture2D *thetexture=CCTextureCache::sharedTextureCache()->addImage("bird.png");
    
    
    CCArray *bird_fly=CCArray::createWithCapacity(3);
    for (int i=0; i<3; i++) {
        CCSpriteFrame *birdframe=CCSpriteFrame::createWithTexture(thetexture, CCRectMake(20+80*i, 1, 40, 50));
        bird_fly->addObject(birdframe);
        
        
    }
    
    this->setScaleX(1.8f);
    this->setScaleY(1.5f);
    CCActionInterval *up=CCMoveTo::create(0.4f, ccp(this->getPosition().x, this->getPosition().y+15.0f));
    CCActionInterval *down=CCMoveTo::create(0.4f, ccp(this->getPosition().x, this->getPosition().y-30.0f));
    
    CCAnimation *animation=CCAnimation::createWithSpriteFrames(bird_fly,0.1f);
    
    CCAnimate *animate=CCAnimate::create(animation);
    CCSpawn *spawn=CCSpawn::create(up,down,animate,NULL);
    CCRepeatForever *forever=CCRepeatForever::create(spawn);
    this->runAction(forever);
    
    
    
    
}
