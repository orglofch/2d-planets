#ifndef _DEBUG_LAYER_H_
#define _DEBUG_LAYER_H_

#include "Layer.h"

class DebugLayer : public Layer
{
private:
	sf::Font m_font;

public:
	DebugLayer(sf::FloatRect viewport, const int depth = 0, const bool acceptsEvents = true, const bool isVisible = true);

	void init();
	void render();
};

#endif