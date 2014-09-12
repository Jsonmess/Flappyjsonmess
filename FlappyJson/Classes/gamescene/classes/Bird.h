//
//  Bird.h
//  FlappyJson
//
//  Created by Json on 14-7-21.
//
//

#ifndef __FlappyJson__Bird__
#define __FlappyJson__Bird__

#include <iostream>
#include "cocos2d.h"
#include "CCPhysicsSprite.h"
#include "Box2D.h"

using namespace cocos2d;

class Bird:public cocos2d::CCSprite
{
private:
    b2Body *birdBody;
    
public:
    Bird();
    void  SetBirdBody(b2Body *pBody);
    b2Body * GetBirdBody();
   
    virtual  bool isDirty(void);
    void runtheAction();
    
};
#endif /* defined(__FlappyJson__Bird__) */
