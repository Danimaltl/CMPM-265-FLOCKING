#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "VehicleSystem.h"

//Window to be displayed throughout game
sf::RenderWindow window;

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flocking", sf::Style::Default, settings);

	VehicleSystem system(100);

	sf::Sprite renderSprite;

	sf::Texture renderTexture;
	renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);

	sf::Shader shader;
	shader.loadFromFile("shader.frag", sf::Shader::Fragment);
	shader.setUniform("resolution", sf::Glsl::Vec2(1280, 720));
	shader.setUniform("texture", sf::Shader::CurrentTexture);

	float time = 0;

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
		time += dt;
		shader.setUniform("time", time);
		window.clear();
		system.Draw();
		renderTexture.update(window);
		renderSprite.setTexture(renderTexture);
		window.draw(renderSprite, &shader);
		window.display();
	}

	return 0;
}
