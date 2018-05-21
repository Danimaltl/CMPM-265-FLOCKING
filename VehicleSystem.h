#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>

#include "Globals.h"
#include "Vehicle.h"

class VehicleSystem {
public:
	VehicleSystem(unsigned int count);

	void Update(float dt);
	void Draw();

	void AddVehicle(const unsigned int count);
	void RemoveVehicle(unsigned int count);
private:
	std::vector<Vehicle> m_Vehicles;

	sf::Vector2f m_Target;
};
