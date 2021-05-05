
#ifndef __Bird__
#define __Bird__

#include "cocos2d.h"

class Bird
{
public:
	Bird(cocos2d::Layer* layer);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	
	cocos2d::Sprite* flappyBird;
};



#endif // __Bird__