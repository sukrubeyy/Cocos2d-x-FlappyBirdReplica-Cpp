

#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SplashScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::mainMenuyeGir), Display_SplashSceneTime);

    //Sprite oluþturuyoruz background için.
    auto SpriteBackground = Sprite::create("images/SplashScreen.png");
    SpriteBackground->setPosition(Point(visibleSize.width / 2 + origin.x,
                                  visibleSize.height / 2 + origin.y));
    float scale = MAX(visibleSize.width/SpriteBackground->getContentSize().width,
                     visibleSize.height/SpriteBackground->getContentSize().height);
    SpriteBackground->setScale(scale);
    
    this->addChild(SpriteBackground);
    return true;
}

void SplashScene::mainMenuyeGir(float deltaTime)
{
    //MainMenuScene sahnesini oluþturuyoruz.
    //Auto türü c++ dilinde türü belirli olmayan deðiþkenlere veriliyor.
    //C# var türü gibi.
    auto scene = MainMenuScene::create();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_Time,scene));
}
