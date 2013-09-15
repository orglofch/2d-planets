#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Constants.h"

#define OPEN_GL true

#define WIDTH	800
#define HEIGHT	400

class Application
{
    private:
        // Private Constructor
		Application() {
			sf::ContextSettings settings;
			settings.depthBits = 24;
			settings.stencilBits = 8;
			settings.antialiasingLevel = 4;
			settings.majorVersion = 3;
			settings.minorVersion = 0;

			window.create(sf::VideoMode(WIDTH, HEIGHT), "Cosmos", sf::Style::Default, settings);
			//window.setFramerateLimit(60);
			window.setVerticalSyncEnabled(true);

			window.setActive();

			glEnable(GL_DEPTH_TEST);
			glDepthMask(GL_TRUE);
			glClearDepth(1.f);

			glDisable(GL_LIGHTING);

			glViewport(0, 0, window.getSize().x, window.getSize().y);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			glEnable(GL_TEXTURE_2D);
		};

        // Stop the compiler generating methods of copy the object
        Application(Application const& copy);            // Not Implemented
        Application& operator=(Application const& copy); // Not Implemented

    public:
        static Application& getInstance()
        {
            // The only instance
            // Guaranteed to be lazy initialized
            // Guaranteed that it will be destroyed correctly
            static Application instance;
            return instance;
        }

		sf::RenderWindow window;
};

#endif