#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

#include "Vehicle.h"

class VehicleSystem {
public:
	VehicleSystem(int count = 1);

	void Update();
	void Draw(sf::RenderWindow window);

	void AddVehicle(int count = 1);
	void RemoveVehicle(int count = 1);
private:
	std::vector<Vehicle> m_Vehicles;
};
