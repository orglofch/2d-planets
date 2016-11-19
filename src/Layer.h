#ifndef _LAYER_H_
#define _LAYER_H_

#include <SFML/Graphics.hpp>

#include "Application.h"
#include "Utility.h"
#include "Entity.h"

class Layer
{
protected:
	std::vector<Entity*> entities;

	int m_depth;

	sf::Vector2f m_lastMousePosition;

	bool m_isVisible;
	bool m_isPaused;

	sf::View m_view;

public:
	Layer(sf::FloatRect viewport, const int depth = 0, const bool acceptsEvents = true, const bool isVisible = true);
	~Layer();

	void setPosition(const sf::Vector2f position);
	void setAcceptsEvents(const bool acceptsEvents);
	void setVisible(const bool isVisible);
	void setPaused(const bool paused);

	sf::Vector2f getPosition();
	bool isVisible();
	bool isPaused();

	virtual void init() = 0;
	virtual void step();
	virtual void update();
	virtual void render();

	void handleEvent(sf::Event &event);
	virtual void mouseClick(const sf::Vector2f mouse);
	virtual void mouseReleased(const sf::Vector2f mouse);
	virtual void mouseMoved(const sf::Vector2f mouse);
	virtual void keyPressed(sf::Keyboard::Key key);
	virtual void keyReleased(sf::Keyboard::Key key);
};

#endif