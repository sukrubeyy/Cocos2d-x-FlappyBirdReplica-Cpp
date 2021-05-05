

#ifndef __MainMenuScene_SCENE_H__
#define __MainMenuScene_SCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

private:
    void OyunSahnesineGit(cocos2d::Ref* sender);

};

#endif // __MainMenuScene_H__
