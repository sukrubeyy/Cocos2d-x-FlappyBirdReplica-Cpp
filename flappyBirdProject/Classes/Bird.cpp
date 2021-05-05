#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	flappyBird = Sprite::create("images/Ball.png");
   
	flappyBird->setPosition(Point(visibleSize.width /2+origin.x, visibleSize.height / 2 + origin.y));
	auto flappyBirdBody = PhysicsBody::createCircle(flappyBird->getContentSize().width/2);

	flappyBirdBody->setCollisionBitmask(Bird_Collision_BitMask);
	flappyBirdBody->setContactTestBitmask(true);

	flappyBird->setPhysicsBody(flappyBirdBody);
	
	layer->addChild(flappyBird,100);
}