#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { 
    sceneWorld = world; };  
  
    bool contactBegin(cocos2d::PhysicsContact &contact);
    bool touchBegin(cocos2d::Touch *touch , cocos2d::Event *event);
    void stopFlying(float dt);
    void update(float dt);
    void createPipe(float timer);
    cocos2d::PhysicsWorld* sceneWorld;
    Pipe pipe;
    Bird* bird;
    unsigned int score;
    cocos2d::Label* lblScore;
};

#endif // __GameScene_H__
