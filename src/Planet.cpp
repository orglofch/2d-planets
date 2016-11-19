#include "Planet.h"

void Planet::init() {
	m_population = 0;
	m_position = sf::Vector2f(200, 200);
	m_radius = 100;
	m_size = sf::Vector2f(m_radius * 2, m_radius * 2);
	m_mass = 2;
	m_name = "";
	m_seed = time(NULL);
	m_waterLevel = 0.0f;

	numHeightSurfaces = 25;

	m_circumference = 2 * PI * m_radius;
	m_heightVariance = m_radius / 4;
}

sf::Vector2f Planet::toProjection(sf::Vector2f point, float radius) {
	float circumference = 2 * PI * radius;

	float r = sqrt(pow(point.x, 2) + pow(point.y, 2));
	float angle = toDegrees(atan2(point.y, point.x));

	float r2 = (sqrt(r) * sqrt(circumference / 4)) / (circumference / 4) * radius;
	sf::Vector2f pos = makeVector(angle, r2, sf::Vector2f(radius, radius));

	return pos;
}

sf::Vector2f Planet::toPlane(sf::Vector2f point, float radius) {
	float circumference = 2 * PI * radius;

	float r = sqrt(pow(point.x, 2) + pow(point.y, 2));
	float angle = toDegrees(atan2(point.y, point.x));

	float r2 = (pow(r, 2) / radius) / radius * (circumference / 4);
	sf::Vector2f pos = makeVector(angle, r2, sf::Vector2f(circumference / 4, circumference /4));

	return pos;
}

void Planet::generatePlanetSprite() {
	m_planet_image.create(m_radius * 2, m_radius * 2, sf::Color(0, 0, 0, 0));

	for (int i = 0; i < m_radius * 2; ++i) {
		for (int j = 0; j < m_radius * 2; ++j) {
			float x = (i - m_radius);
			float y = (j - m_radius);
			if (distance(sf::Vector2f(x, y), sf::Vector2f(0, 0)) <= m_radius) {
				sf::Vector2f planePos = toPlane(sf::Vector2f(x, y), m_radius);

				float height = heightMap.GetValue(planePos.x / 1, planePos.y / 1);
				m_test_image.setPixel(planePos.x, planePos.y, sf::Color(255, 255, 255, 255));
				m_planet_image.setPixel(i, j, colorByHeight(height));
			}
		}
	}

	m_planet_texture.loadFromImage(m_planet_image, sf::IntRect(0, 0, (int)(m_radius * 2), (int)(m_radius * 2)));
	m_planet_sprite.setTexture(m_planet_texture);
}

void Planet::generateHeightImage(const int surfaceDensity) {
	m_heightMapSurface.setPointCount(surfaceDensity);

	float angleInc = (float)(360 / surfaceDensity);
	int index = 0;
	for (float i = 0; i <= 360 && index < surfaceDensity; i += angleInc) {
		float x = cos(toRadians(i)) * m_circumference / 4 + m_circumference / 4; 
		float y = sin(toRadians(i)) * m_circumference / 4 + m_circumference / 4;

		float height;
		if (heightMap.GetValue((int)x, (int)y) >= m_waterLevel) {
			height = m_radius + heightMap.GetValue((int)x, (int)y) * m_heightVariance;
		} else {
			height = m_radius + m_waterLevel * m_heightVariance;
		}
		sf::Vector2f position(makeVector(i, height));
		m_heightMapSurface.setPoint(index, position);
		m_test_image.setPixel((int)x, (int)y, sf::Color(0, 255, 0, 255));
		index++;
	}
}

sf::Color Planet::colorByHeight(float height) {
	if (height < m_waterLevel) { 
		if (height < m_waterLevel - 0.3f) { // DEEP WATER
			return sf::Color(0, 12, 140, 255);
		} else if (height < m_waterLevel - 0.1f) { // MODERATE WATER
			return sf::Color(65, 75, 214, 255);
		} else { // SHALLOW WATER
			return sf::Color(141, 150, 240, 255);
		}
	} else { // LAND
		if (height < m_waterLevel + 0.05f) { // SAND
			return sf::Color(236, 245, 191, 255);
		} else if (height < m_waterLevel + 0.5f) { // GRASS
			return sf::Color(96, 115, 0, 255);
		} else {
			return sf::Color(74, 79, 46, 255);
		} 
	}
}

void Planet::seed(int seed) {
	m_seed = seed;
}

void Planet::randSeed() {
	m_seed = time(NULL);
}

void Planet::accelerateObjectsInField() {	
}

void Planet::accelerateObject(Entity *entity) {
	sf::Vector2f position = entity->getPosition();
	sf::Vector2f velocity = entity->getVelocity();

	float a = angle(position, m_position);
	float d = distance(position, m_position);
	d = (d == 0 ? (float)0.001 : d);
	float force = GRAVITATIONAL_CONSTANT * entity->getMass() * this->getMass() / pow(d, 2);
	float acceleration = force / entity->getMass();

	velocity += makeVector(a, acceleration);
	entity->setVelocity(velocity);
}

void Planet::generate() {
	m_test_image.create(m_circumference / 2 + 1, m_circumference / 2 + 1, sf::Color(0, 0, 0, 0));

	noise::module::Perlin myModule;
	myModule.SetSeed(m_seed);
	noise::utils::NoiseMapBuilderPlane heightMapBuilder;
	heightMapBuilder.SetSourceModule (myModule);
	heightMapBuilder.SetDestNoiseMap (heightMap);
	heightMapBuilder.SetDestSize (m_circumference / 2, m_circumference / 2);
	heightMapBuilder.SetBounds (0.0, 2.0, 0.0, 2.0);
	heightMapBuilder.Build();

	for (int i = 0; i < m_circumference / 2; ++i) {
		for (int j = 0; j < m_circumference / 2; ++j) {
			float x = i - m_circumference / 4;
			float y = j - m_circumference / 4;
			if (distance(sf::Vector2f(x, y), sf::Vector2f(0, 0)) <= m_circumference / 4) {
				float height = heightMap.GetValue(i, j);
				m_test_image.setPixel(i, j, colorByHeight(height));
			}
		}
	}

	generatePlanetSprite();
	generateHeightImage(360);

	m_test_texture.loadFromImage(m_test_image, sf::IntRect(0, 0, (int)(m_circumference / 2), (int)(m_circumference /2)));
	m_test_sprite.setTexture(m_test_texture);

	m_font.loadFromFile("arial.ttf");
	text.setFont(m_font);
	text.setCharacterSize(15);
	text.setString(m_name);
}

void Planet::alterWaterLevel(const float delta) {
	m_waterLevel += delta;

	generatePlanetSprite();
	generateHeightImage(360);

	m_planet_texture.loadFromImage(m_planet_image, sf::IntRect(0, 0, (int)(m_radius * 2), (int)(m_radius * 2)));
	m_planet_sprite.setTexture(m_planet_texture);
}

float Planet::getRadius() {
	return m_radius;
}

void Planet::setRadius(float radius) {
	m_radius = radius;
	m_size = sf::Vector2f(m_radius * 2, m_radius * 2);
	m_circumference = 2 * PI * m_radius;
	m_heightVariance = m_radius / 4;
}

void Planet::step() {
	m_angle += 0.7f;
	//alterWaterLevel(0.01f);
	accelerateObjectsInField();
}

void Planet::render() {
	Application::getInstance().window.pushGLStates();

	m_heightMapSurface.setPosition(m_position);
	m_heightMapSurface.setRotation(m_angle);
	//m_heightMapSurface.setTexture(&m_planet_texture);
	m_heightMapSurface.setFillColor(colorByHeight(1.0f));
	m_heightMapSurface.setScale(0.97f, 0.97f);
	Application::getInstance().window.draw(m_heightMapSurface);

	m_planet_sprite.setOrigin(m_radius, m_radius);
	m_planet_sprite.setPosition(m_position);
	m_planet_sprite.setRotation(m_angle);
	Application::getInstance().window.draw(m_planet_sprite);

	m_test_sprite.setPosition(m_position + sf::Vector2f(200, -150));
	Application::getInstance().window.draw(m_test_sprite);

	text.setPosition(sf::Vector2f(m_position.x + m_radius, m_position.y));
	Application::getInstance().window.draw(text);

	Application::getInstance().window.popGLStates();
}

void Planet::onClick() {
}

void Planet::beginContact(Entity *entity) {
	int craterSize = 40;

	float a = 180 + angle(entity->getPosition(), m_position);
	sf::Vector2f pos = makeVector(a, m_circumference / 4);

	for (int i = 0; i < craterSize; ++i) {
		for (int j = 0; j < craterSize; ++j) {
			int x = i + pos.x - craterSize / 2 + m_circumference / 4;
			int y = j + pos.y - craterSize / 2 + m_circumference / 4;
			int x2 = i - craterSize / 2;
			int y2 = j - craterSize / 2;
			if (distance(sf::Vector2f(x2, y2), sf::Vector2f(0, 0)) <= craterSize) {
				int z = sqrt(pow((float)(craterSize / 2), 2) - pow((float)x2, 2) - pow((float)y2, 2));
				heightMap.SetValue(x, y, heightMap.GetValue(x, y) - 100);
			}
		}
	}

	generatePlanetSprite();
	generateHeightImage(360);
}

void Planet::endContact(Entity *entity) {
}