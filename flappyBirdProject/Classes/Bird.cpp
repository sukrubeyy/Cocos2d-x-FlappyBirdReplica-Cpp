#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer* layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	flappyBird = Sprite::create("images/bird.png");
   
	flappyBird->setPosition(Point(visibleSize.width /2+origin.x, visibleSize.height / 2 + origin.y));
	auto flappyBirdBody = PhysicsBody::createCircle(flappyBird->getContentSize().width/2);

	flappyBirdBody->setCollisionBitmask(Bird_Collision_BitMask);
	flappyBirdBody->setContactTestBitmask(true);

	flappyBird->setPhysicsBody(flappyBirdBody);
	isFall = true;
	layer->addChild(flappyBird,100);
}

void Bird::fall()
{
	if (true == isFall)
	{
		flappyBird->setPositionX(visibleSize.width/2+origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY()-(Bird_Falling_Speed*(visibleSize.height/ 10)));
	}
	else
	{
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() + ( Bird_Falling_Speed * (visibleSize.height / 10)));
	}
}