#include "VehicleSystem.h"

VehicleSystem::VehicleSystem(unsigned int count = 1) {
	AddVehicle(count, sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	
	if (!m_Font.loadFromFile("arial.ttf"))
	{
		fprintf(stderr, "Couldn't load font!");
	}

	m_Text.setFont(m_Font);
	m_Text.setFillColor(sf::Color::Green);
	m_Text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2, 20));
	m_Text.setCharacterSize(28);
	m_Text.setString("BNAG");
	m_Text.setOrigin(m_Text.getGlobalBounds().width / 2, m_Text.getGlobalBounds().height / 2);
}

void VehicleSystem::Update(float dt) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	m_Target.x = (float)mousePos.x;
	m_Target.y = (float)mousePos.y;

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		m_MousePressed = false;
	}
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_MousePressed) {
		m_MousePressed = true;
		AddVehicle(1, m_Target);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !m_MousePressed) {
		m_MousePressed = true;
		RemoveVehicle(1);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		m_KeyPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_KeyPressed) {
		m_SepToggle = (m_SepToggle == 0) ? 1 : 0;
		m_KeyPressed = true;
		if (m_SepToggle == 0) {
			m_Text.setString("Separation: Off");
		}
		else {
			m_Text.setString("Separation: On");
		}
		
		printf("Separation: %f\n", m_SepToggle);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !m_KeyPressed) {
		m_AlToggle = (m_AlToggle == 0) ? 1 : 0;
		m_KeyPressed = true;
		if (m_AlToggle == 0) {
			m_Text.setString("Alignment: Off");
		}
		else {
			m_Text.setString("Alignment: On");
		}
		printf("Alignment: %f\n", m_AlToggle);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && !m_KeyPressed) {
		m_CoToggle = (m_CoToggle == 0) ? 1 : 0;
		m_KeyPressed = true;
		if (m_CoToggle == 0) {
			m_Text.setString("Cohesion: Off");
		}
		else {
			m_Text.setString("Cohesion: On");
		}
		printf("Cohesion: %f\n", m_CoToggle);
	}

	for (size_t i = 0; i < m_Vehicles.size(); i++) {
		//m_Vehicles[i].Seek(m_Target);
		//m_Vehicles[i].Arrive(m_Target);
		m_Vehicles[i].Update(dt);
	}
}

void VehicleSystem::Draw() {
	for (size_t i = 0; i < m_Vehicles.size(); i++) {
		m_Vehicles[i].Draw();
	}
	m_Text.setOrigin(m_Text.getGlobalBounds().width / 2, m_Text.getGlobalBounds().height / 2);
	//window.draw(m_Text);
}

void VehicleSystem::AddVehicle(const unsigned int count = 1, sf::Vector2f position = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)) {
	m_Vehicles.resize(m_Vehicles.size() + count, Vehicle(position, this));
}

void VehicleSystem::RemoveVehicle(unsigned int count = 1) {
	if (count > m_Vehicles.size()) count = 0;
	m_Vehicles.resize(m_Vehicles.size() - count, Vehicle(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), this));
}