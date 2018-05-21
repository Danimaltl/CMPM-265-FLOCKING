#include "VehicleSystem.h"

VehicleSystem::VehicleSystem(unsigned int count = 1) {
	AddVehicle(count);
	
}

void VehicleSystem::Update(float dt) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	m_Target.x = (float)mousePos.x;
	m_Target.y = (float)mousePos.y;

	for (size_t i = 0; i < m_Vehicles.size(); i++) {
		//m_Vehicles[i].Seek(m_Target, dt);
		m_Vehicles[i].Arrive(m_Target, dt);
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