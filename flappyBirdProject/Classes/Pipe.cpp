
#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Pipe ::spawnPipe(cocos2d::Layer*layer)
{


	auto topPipe = Sprite::create("images/Pipe.png");
	auto bottomPipe = Sprite::create("images/Pipe.png");
	auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
	auto bottomPipeBody = PhysicsBody::createBox(bottomPipe->getContentSize());

	topPipeBody->setCollisionBitmask(Pipe_Collision_BitMask);
	topPipeBody->setContactTestBitmask(true);

	bottomPipeBody->setCollisionBitmask(Pipe_Collision_BitMask);
	bottomPipeBody->setContactTestBitmask(true);

	auto random = CCRANDOM_0_1();
	if (random < lower_screen_pipe_)
	{
		random = lower_screen_pipe_;
	}
	else if (random > upper_screen_pipe_) 
	{ 
		random = upper_screen_pipe_; 
	}

	auto topPipePos = (random * visibleSize.width) + (topPipe->getContentSize().height / 2);

	topPipeBody->setDynamic(false);
	bottomPipeBody->setDynamic(false);

	topPipe->setPhysicsBody(topPipeBody);
	bottomPipe->setPhysicsBody(bottomPipeBody);

	topPipe->setPosition(Point(visibleSize.width+topPipe->getContentSize().width+origin.x,topPipePos));

	bottomPipe->setPosition(Point(topPipe->getPositionX(),
							topPipePos-(Sprite::create("images/Ball.png")->
							getContentSize().height*Pipe_Gap)
							-topPipe->getContentSize().height));

	layer->addChild(topPipe);
	layer->addChild(bottomPipe);

	auto topPipeAction = MoveBy::create(pipe_speed*visibleSize.width,Point(-visibleSize.width*1,0));
	auto bottomPipeAction = MoveBy::create(pipe_speed * visibleSize.width, Point(-visibleSize.width * 1, 0));

	topPipe->runAction(topPipeAction);
	bottomPipe->runAction(bottomPipeAction);

	auto pointNode = Node::create();
	auto pointBody = PhysicsBody::createBox(Size(1, Sprite::create("images/Ball.png")->getContentSize().height * Pipe_Gap));
	pointBody->setDynamic(false);
	pointBody->setCollisionBitmask(Point_Collision_BitMask);
	pointBody->setContactTestBitmask(true);
	pointNode->setPhysicsBody(pointBody);
	pointNode->setPosition(topPipe->getPositionX(),topPipe->getPositionY()-(topPipe->getContentSize().height/2)-
									((Sprite::create("images/Ball.png")->getContentSize().height * Pipe_Gap/2)));
	layer->addChild(pointNode);
	auto pointNodeAction = MoveBy::create(pipe_speed*visibleSize.width,Point(-visibleSize.width*1,0));
	pointNode->runAction(pointNodeAction);

	
	


}

