#ifndef _ACTIVITY_H_
#define _ACTIVITY_H_

#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Layer.h"

class Activity 
{
protected:
	std::vector<Layer*> m_layers; /* TODO: Make Heap eventually with depth value */

public:
	Activity();
	~Activity();

	void start();

	void addLayer(Layer *layer);

	void handleEvent(sf::Event &event);
	void step();
	void update();
	void render();
};

#endif