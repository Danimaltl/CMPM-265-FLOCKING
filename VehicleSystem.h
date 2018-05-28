#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "FlockMath.h"
#include "Globals.h"

class Vehicle;
class VehicleSystem;

class Vehicle {
public:
	Vehicle(sf::Vector2f position, VehicleSystem* system);

	void Update(float dt);
	void Draw();

	//Move towards target
	void Seek(const sf::Vector2f& target);
	void Arrive(const sf::Vector2f& target);

	VehicleSystem* m_System;
	std::vector<Vehicle>* m_Vehicles;

private:
	sf::ConvexShape m_Shape;

	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;

	float m_MaxSpeed;
	float m_MaxForce;

	float m_ArriveRadius;
	float m_NeighborRadius;

	void ApplyForce(const sf::Vector2f& force);

	sf::Vector2f ComputeSeparation();
	sf::Vector2f ComputeAlignment();
	sf::Vector2f ComputeCohesion();
	sf::Vector2f WallsForce();
};

class VehicleSystem {
public:
	VehicleSystem(unsigned int count);

	void Update(float dt);
	void Draw();

	void AddVehicle(const unsigned int count, sf::Vector2f position);
	void RemoveVehicle(unsigned int count);

	std::vector<Vehicle> m_Vehicles;

	float m_Separation = 1.2f;
	float m_Alignment = 0.8f;
	float m_Cohesion = 1.1f;

	float m_SepToggle = 1;
	float m_AlToggle = 1;
	float m_CoToggle = 1;

private:
	sf::Vector2f m_Target;

	sf::Font m_Font;
	sf::Text m_Text;

	bool m_MousePressed = false;
	bool m_KeyPressed = false;
};