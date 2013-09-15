#include "DebugLayer.h"

DebugLayer::DebugLayer(sf::FloatRect viewport, const int depth, const bool acceptsEvents, const bool isVisible) :
	Layer(viewport, depth, acceptsEvents, isVisible) {
}

void DebugLayer::init() {
	if (!m_font.loadFromFile("arial.ttf")) {
	}
}

void DebugLayer::render() {
	sf::Text text;
	sf::Vector2i pixelPos = sf::Mouse::getPosition(Application::getInstance().window);

	text.setFont(m_font);
	text.setCharacterSize(15);

	text.setString("Mouse pos: (" + toString(pixelPos.x) + ", " + toString(pixelPos.y) + ")");

	Application::getInstance().window.draw(text);
}