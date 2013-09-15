#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "AnimatedSprite.hpp"

class Animation
{
protected:
	bool m_isFinished;

public:
	Animation();

	virtual void start() {};
	virtual void update(AnimatedSprite *owner) = 0;

	bool isFinished();
};

#endif