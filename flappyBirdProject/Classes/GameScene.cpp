#include "GameScene.h"
#include "Definitions.h"
#include <iostream>

USING_NS_CC;

Scene* GameScene::createScene()
{
    //Araþtýr
    auto scene = Scene::createWithPhysics();
    //Araþtýr
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto layer = GameScene::create();
    //Araþtýr
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
    //unity'deki rigidbody gibi düþünebilirsin.
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    //Node oluþturuyoruz
    auto edgeNode = Node::create();
    //pozisyon veriyoruz
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x,
                         visibleSize.height / 2 + origin.y));
    //objeye þekil veriyoruz
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::createPipe), Pipe_Spawn_Time*visibleSize.width);

    bird = new Bird(this);

    return true;
}

void GameScene::createPipe(float time)
{
    pipe.spawnPipe(this);
}