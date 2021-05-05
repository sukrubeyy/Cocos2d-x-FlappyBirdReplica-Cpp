
#ifndef __SplashScene_SCENE_H__
#define __SplashScene_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
private: void mainMenuyeGir(float deltaTime);
};

#endif // __SplashScene_H__
