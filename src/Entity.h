#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>

#include <SFML/Graphics.hpp>

#include "AnimatedSprite.hpp"
#include "Application.h"
#include "Constants.h"
#include "Utility.h"

//class Sensor;

class Entity
{
protected:
	int m_type;

	//std::vector<Sensor*> sensors;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_size;
	float m_angle;
	float m_mass;

public:
	Entity();
	~Entity();

	int getType();

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	sf::Vector2f getSize();
	float getAngle();
	float getMass();

	void setPosition(sf::Vector2f position);
	void setVelocity(sf::Vector2f velocity);
	void setSize(sf::Vector2f size);
	void setAngle(float angle);
	void setMass(float mass);

	virtual void step();
	virtual void update();
	virtual void render();

	virtual void beginContact(Entity *entity);
	virtual void endContact(Entity *entity);
	virtual void onClick();
	virtual void onRelease();
	virtual void onEnter();
	virtual void onExit();
};

#endif