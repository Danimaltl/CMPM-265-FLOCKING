#include "VehicleSystem.h"

VehicleSystem::VehicleSystem(unsigned int count = 1) {
	AddVehicle(count, sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	
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
}

void VehicleSystem::AddVehicle(const unsigned int count = 1, sf::Vector2f position = sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)) {
	m_Vehicles.resize(m_Vehicles.size() + count, Vehicle(position, &m_Vehicles));
}

void VehicleSystem::RemoveVehicle(unsigned int count = 1) {
	if (count > m_Vehicles.size()) count = 0;
	m_Vehicles.resize(m_Vehicles.size() - count, Vehicle(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), &m_Vehicles));
}