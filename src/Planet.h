#ifndef _PLANET_H_
#define _PLANET_H_

#include <cstdlib>
#include <string>
#include <ctime>

#include <noise/noise.h>

#include "noiseutils.h"
#include "Entity.h"

class Planet : public Entity
{
private:
	int numHeightSurfaces;
	sf::ConvexShape m_heightMapSurface;
	sf::Image m_planet_image;
	sf::Texture m_planet_texture;
	sf::Sprite m_planet_sprite;

	int m_seed;

	int m_population;
	float m_radius;
	float m_circumference;
	float m_heightVariance;
	float m_rotation;
	int m_moons;
	float m_temperature;

	std::string m_name;
	sf::Font m_font;
	sf::Text text;

	sf::Image m_test_image;
	sf::Texture m_test_texture;
	sf::Sprite m_test_sprite;

	noise::utils::NoiseMap heightMap;
	float m_waterLevel;

	void accelerateObjectsInField();
	void accelerateObject(Entity *entity);
	sf::Vector2f toProjection(sf::Vector2f point, float radius);
	sf::Vector2f toPlane(sf::Vector2f point, float radius);
	void generatePlanetSprite();
	void generateHeightImage(const int surfaceDensity);
	sf::Color colorByHeight(float height);

public:
	void init();

	float getRadius();
	void setRadius(float radius);
	void seed(int seed);
	void randSeed();

	void step();
	void render();
	void generate();

	void alterWaterLevel(const float delta);

	void onClick();
	void beginContact(Entity *entity);
	void endContact(Entity *entity);
};

#endif