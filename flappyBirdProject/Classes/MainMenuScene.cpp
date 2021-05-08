#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "ui/CocosGUI.h"
#include "ui/UITextField.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto backGround = Sprite::create("images/back.png");
    backGround->setPosition(Point(visibleSize.width/2+origin.x,
                            visibleSize.height/2+origin.y));

         float scale = MAX(visibleSize.width / backGround->getContentSize().width,
         visibleSize.height / backGround->getContentSize().height);
         backGround->setScale(scale);

    this->addChild(backGround);

    auto playButton = MenuItemImage::create("images/Play Button.png","images/Play Button Clicked.png",
                                CC_CALLBACK_1(MainMenuScene::OyunSahnesineGit,this));
    playButton->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/3+origin.y));
    auto menu = Menu::create(playButton,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);

    auto textField = ui::TextField::create("Flappy Bird Replica","Marker Felt",30 );
    textField->setPosition(Point(visibleSize.width/2+origin.x,
                            visibleSize.height-textField->getContentSize().height));

    this->addChild(textField);

    return true;
}

void MainMenuScene::OyunSahnesineGit(cocos2d::Ref* sender) 
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_Time, scene));
}