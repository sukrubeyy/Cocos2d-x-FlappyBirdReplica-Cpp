#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

Scene* GameScene::createScene()
{
    //Araþtýr
    auto scene = Scene::createWithPhysics();
    //Araþtýr
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vect(0,0));
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
    //unity'deki collider gibi düþünebilirsin.
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    edgeBody->setCollisionBitmask(Pipe_Collision_BitMask);
    edgeBody->setContactTestBitmask(true);
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

    auto eventListener = EventListenerPhysicsContact::create();
    eventListener->onContactBegin = CC_CALLBACK_1(GameScene::contactBegin,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::touchBegin,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);

    score = 0;
    auto tempScore = Label::createWithTTF(std::to_string(score), "fonts/Arial.ttf", 50);
    lblScore = tempScore;
    lblScore->setColor(Color3B::YELLOW);
    lblScore->setPosition(visibleSize.width/2+origin.x,visibleSize.height*0.90+origin.y);
    this->addChild(lblScore,10000000);

    this->scheduleUpdate();
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

    else if ((Bird_Collision_BitMask == first->getCollisionBitmask() && Point_Collision_BitMask == second->getCollisionBitmask()) 
                                                        ||
        (Bird_Collision_BitMask == second->getCollisionBitmask() && Point_Collision_BitMask == first->getCollisionBitmask()))
    {
        score++;
         auto tempScore = Label::createWithTTF(std::to_string(score), "fonts/Arial.ttf", 50);
         lblScore->setString(tempScore->getString());
      
    }

    return true;
}

bool GameScene::touchBegin(cocos2d::Touch* touch, cocos2d::Event* event)
{
    bird->Fly();
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::stopFlying), Bird_Duration);
    return true;
}

void GameScene::stopFlying(float dt)
{
    bird->stopfly();
}
void GameScene::update(float dt)
{
    bird->fall();
}