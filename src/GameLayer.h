#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "Planet.h"
#include "Layer.h"

class GameLayer : public Layer
{
private:
	Planet *planet;

public:
	GameLayer(sf::FloatRect viewport, const int depth = 0, const bool acceptsEvents = true, const bool isVisible = true);

	void init();
	void mouseClick(const sf::Vector2f mouse);
};

#endif