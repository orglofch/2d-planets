#include "Activity.h"

Activity::Activity() {
}

Activity::~Activity() {
	for (std::vector<Layer*>::iterator i = m_layers.begin(); i < m_layers.end(); ++i) {
		delete (*i);
	}
}

void Activity::start() {
	sf::Event event;
	sf::Clock clock;
	clock.restart();
	render();

    while (Application::getInstance().window.isOpen())
    {
        if (Application::getInstance().window.pollEvent(event)) {
			handleEvent(event);
		}

		step();
		update();
		render();
    }
}

void Activity::addLayer(Layer *layer) {
	layer->init();
	m_layers.push_back(layer);
}

void Activity::handleEvent(sf::Event &event) {
	switch (event.type)
	{
		case sf::Event::Closed:
			Application::getInstance().window.close();
			break;

		case sf::Event::Resized:
			if (OPEN_GL) {
				glViewport(0, 0, event.size.width, event.size.height);
			}
			break;

		case sf::Event::GainedFocus:
			break;

		case sf::Event::LostFocus:
			break;

		// we don't process other types of events, send to layers
		default:
			for (std::vector<Layer*>::iterator i = m_layers.begin(); i < m_layers.end(); ++i) {
				(*i)->handleEvent(event);
			}
			break;
	}
}

void Activity::step() {
	for (std::vector<Layer*>::iterator i = m_layers.begin(); i < m_layers.end(); ++i) {
		if (!(*i)->isPaused()) {
			(*i)->step();
		}
	}
}

void Activity::update() {
	for (std::vector<Layer*>::iterator i = m_layers.begin(); i < m_layers.end(); ++i) {
		if (!(*i)->isPaused()) {
			(*i)->update();
		}
	}
}

void Activity::render() {
	// clear
	if (OPEN_GL) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	} else {
		Application::getInstance().window.clear();
	}

	// render objects
	for (std::vector<Layer*>::iterator i = m_layers.begin(); i < m_layers.end(); ++i) {
		if ((*i)->isVisible()) {
			(*i)->render();
		}
	}

	Application::getInstance().window.display();
}