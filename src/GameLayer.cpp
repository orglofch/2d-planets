#include "GameLayer.h"

GameLayer::GameLayer(sf::FloatRect viewport, const int depth, const bool acceptsEvents, const bool isVisible) :
	Layer(viewport, depth, acceptsEvents, isVisible) {
}

void GameLayer::init() {
	planet = new Planet();
	planet->init();
	planet->setMass(500);
	planet->setRadius(100);
	planet->generate();
	entities.push_back(planet);
}

void GameLayer::mouseClick(const sf::Vector2f mouse) {
	planet->randSeed();
	planet->generate();
}