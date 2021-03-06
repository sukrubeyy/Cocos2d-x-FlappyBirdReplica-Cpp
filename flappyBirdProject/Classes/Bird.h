
#ifndef __Bird__
#define __Bird__

#include "cocos2d.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.h>
class Bird
{
public:
	Bird(cocos2d::Layer* layer);
	

	void Fly() { CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Wing.mp3"); isFall = false; }
	void fall();
	void stopfly() { isFall = true;}

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	bool isFall;
	cocos2d::Sprite* flappyBird;
	
};



#endif // __Bird__