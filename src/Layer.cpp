#include "Layer.h"

Layer::Layer(sf::FloatRect viewport, const int depth, const bool acceptsEvents, const bool isVisible) {
	m_view = sf::View(viewport);
	
	m_depth = depth;
	m_isVisible = isVisible;
	m_isPaused = false;

	m_lastMousePosition = sf::Vector2f(100, 100);
}

Layer::~Layer() {
	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); ++i) {
		delete (*i);
	}
}

void Layer::setVisible(const bool isVisible) {
	m_isVisible = isVisible;
}

void Layer::setPaused(const bool paused) {
	m_isPaused = paused;
}

bool Layer::isVisible() {
	return m_isVisible;
}

bool Layer::isPaused() {
	return m_isPaused;
}

void Layer::step() {
	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); ++i) {
		(*i)->step();
	}
}

void Layer::update() {
	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); ++i) {
		(*i)->update();
	}
}

void Layer::render() {
	Application::getInstance().window.setView(m_view);

	for (std::vector<Entity*>::iterator i = entities.begin(); i < entities.end(); ++i) {
		(*i)->render();
	}
}

void Layer::handleEvent(sf::Event &event) {
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
			{
			mouseClick(m_lastMousePosition);
			break;
			}

		case sf::Event::MouseButtonReleased:
			{
			mouseReleased(m_lastMousePosition);
			break;
			}

		case sf::Event::MouseMoved:
			{
			sf::Vector2i mouse = sf::Mouse::getPosition(Application::getInstance().window);
			mouseMoved(sf::Vector2f((float)mouse.x, (float)mouse.y));
			m_lastMousePosition = sf::Vector2f((float)mouse.x, (float)mouse.y);
			break;
			}

		case sf::Event::KeyPressed:
			{
			keyPressed(event.key.code);
			break;
			}

		case sf::Event::KeyReleased:
			{
			keyReleased(event.key.code);
			break;
			}
	}
}

void Layer::mouseClick(const sf::Vector2f mouse) {	
}

void Layer::mouseReleased(const sf::Vector2f mouse) {
}

void Layer::mouseMoved(const sf::Vector2f mouse) {
}

void Layer::keyPressed(sf::Keyboard::Key key) {
}

void Layer::keyReleased(sf::Keyboard::Key key) {
}