//
//  Bird.h
//  FlappyBird_demo
//
//  Created by Json on 14-6-25.
//
//

#ifndef __FlappyBird_demo__Bird__
#define __FlappyBird_demo__Bird__

#include <iostream>
#include "cocos2d.h"
#include "CCPhysicsSprite.h"
#include "Box2D.h"

using namespace cocos2d;

class Bird:public CCSprite
{
private:
    b2Body *birdBody;

public:
    Bird();
void  SetBirdBody(b2Body *pBody);
    b2Body * GetBirdBody();
//virtual  cocos2d::CCAffineTransform nodeToParentTransform(void);
    virtual  bool isDirty(void);
    
};
#endif /* defined(__FlappyBird_demo__Bird__) */
