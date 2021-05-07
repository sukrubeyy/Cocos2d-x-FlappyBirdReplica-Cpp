

#ifndef __GameOverScene_SCENE_H__
#define __GameOverScene_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(unsigned int tempScore);

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

private:
    void goToMainMenuScene(cocos2d::Ref* sender);
    void goToGameScene(cocos2d::Ref* sender);
};

#endif // __GameOverScene_H__
