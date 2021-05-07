#include "GameOverScene.h"
#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

unsigned int score;

Scene* GameOverScene::createScene(unsigned int tempScore)
{
    score = tempScore;
    return GameOverScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
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

    auto retryItem = MenuItemImage::create("images/Retry Button.png","images/Retry Button Clicked.png",
                            CC_CALLBACK_1(GameOverScene::goToGameScene,this));
    retryItem->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/4*3));

    auto mainMenuItem = MenuItemImage::create("images/Menu Button.png","images/Menu Button Clicked.png",
                        CC_CALLBACK_1(GameOverScene::goToMainMenuScene,this));
    mainMenuItem->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/4));

    auto menu = Menu::create(retryItem,mainMenuItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);


    auto tempScore = Label::createWithTTF(std::to_string(score), "fonts/Arial.ttf", 50);
    auto currentLblScore = tempScore;
    currentLblScore->setColor(Color3B::YELLOW);
    currentLblScore->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.90 + origin.y);
    this->addChild(currentLblScore, 10000000);




    return true;
}

void GameOverScene::goToGameScene(cocos2d::Ref* sender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_Time,scene));
}

void GameOverScene::goToMainMenuScene(cocos2d::Ref *sender)
{
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_Time, scene));
}