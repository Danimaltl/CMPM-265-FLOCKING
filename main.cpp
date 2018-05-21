#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "VehicleSystem.h"

//Window to be displayed throughout game
sf::RenderWindow window;

int main()
{
	window.create(sf::VideoMode(800, 600), "Flocking");

	VehicleSystem system(1);

	sf::Clock clock;
	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) {
					window.close();
					break;
				}
				break;
			}
		}
		system.Update(dt);

		window.clear();
		system.Draw();
		window.display();
	}

	return 0;
}
