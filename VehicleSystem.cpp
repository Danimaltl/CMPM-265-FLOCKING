#include "VehicleSystem.h"

VehicleSystem::VehicleSystem(unsigned int count = 1) {
	AddVehicle(count);
	
}

void VehicleSystem::Update(float dt) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	target.x = (float)mousePos.x;
	target.y = (float)mousePos.y;

	for (size_t i = 0; i < m_Vehicles.size(); i++) {
		m_Vehicles[i].Seek(target, dt);
		m_Vehicles[i].Update(dt);
	}
}

void VehicleSystem::Draw() {
	for (size_t i = 0; i < m_Vehicles.size(); i++) {
		m_Vehicles[i].Draw();
	}
}

void VehicleSystem::AddVehicle(const unsigned int count = 1) {
	m_Vehicles.resize(m_Vehicles.size() + count, Vehicle(sf::Vector2f(400, 300)));
}

void VehicleSystem::RemoveVehicle(unsigned int count = 1) {
	if (count > m_Vehicles.size()) count = 0;
	m_Vehicles.resize(m_Vehicles.size() - count, Vehicle(sf::Vector2f(400, 300)));
}