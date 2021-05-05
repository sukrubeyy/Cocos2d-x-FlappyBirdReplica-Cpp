#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
#include <iostream>

USING_NS_CC;

Scene* GameScene::createScene()
{
    //Ara�t�r
    auto scene = Scene::createWithPhysics();
    //Ara�t�r
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = GameScene::create();
    //Ara�t�r
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);

    return scene;

}
// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
    auto backGround = Sprite::create("images/background.png");
    backGround->setPosition(Point(visibleSize.width / 2 + origin.x,
    visibleSize.height / 2 + origin.y));

    float scale = MAX(visibleSize.width / backGround->getContentSize().width,
        visibleSize.height / backGround->getContentSize().height);
    backGround->setScale(scale);

    this->addChild(backGround);
    //unity'deki collider gibi d���nebilirsin.
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    edgeBody->setCollisionBitmask(Pipe_Collision_BitMask);
    edgeBody->setContactTestBitmask(false);
    //Node olu�turuyoruz
    auto edgeNode = Node::create();
    //pozisyon veriyoruz
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x,
                         visibleSize.height / 2 + origin.y));
    //objeye �ekil veriyoruz
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::createPipe), Pipe_Spawn_Time*visibleSize.width);
    bird = new Bird(this);

    auto eventListener = EventListenerPhysicsContact::create();
    eventListener->onContactBegin = CC_CALLBACK_1(GameScene::contactBegin,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);


    return true;
}

void GameScene::createPipe(float time)
{
    pipe.spawnPipe(this);
}

bool GameScene::contactBegin(cocos2d::PhysicsContact &contact)
{
    PhysicsBody* first = contact.getShapeA()->getBody();
    PhysicsBody* second = contact.getShapeB()->getBody();

    if ((Bird_Collision_BitMask==first->getCollisionBitmask() && Pipe_Collision_BitMask==second->getCollisionBitmask()) 
                                                ||
        (Bird_Collision_BitMask==second->getCollisionBitmask() && Pipe_Collision_BitMask==first->getCollisionBitmask()))
    {
        auto scene = GameOverScene::create();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_Time,scene));
    }

    return true;
}