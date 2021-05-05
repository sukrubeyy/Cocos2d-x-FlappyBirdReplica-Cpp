
#ifndef __Pipe_H__
#define __Pipe_H__

#include "cocos2d.h"

class Pipe 
{
public:
	Pipe();

	void spawnPipe(cocos2d::Layer* layer);
private:

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

#endif // __Pipe_H__
