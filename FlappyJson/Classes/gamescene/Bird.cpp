//
//  Bird.cpp
//  FlappyBird_demo
//
//  Created by Json on 14-6-25.
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
    
}
bool Bird::isDirty(void)
{
    return true;
}
//cocos2d::CCAffineTransform Bird::nodeToParentTransform(void)
//{
//    b2Vec2 pos  = birdBody->GetPosition();
//    
//    float x = pos.x * PTM_RATIO;
//    float y = pos.y * PTM_RATIO;
//    
//    if ( isIgnoreAnchorPointForPosition() ) {
//        x += m_obAnchorPointInPoints.x;
//        y += m_obAnchorPointInPoints.y;
//    }
//    
//    // Make matrix
//    float radians = birdBody->GetAngle();
//    float c = cosf(radians);
//    float s = sinf(radians);
//    
//    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
//        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
//        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
//    }
//    
//    // Rot, Translate Matrix
//    m_sTransform = CCAffineTransformMake( c,  s,
//                                         -s,    c,
//                                         x,    y );
//    
//    return m_sTransform;
//}
