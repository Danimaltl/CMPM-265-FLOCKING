#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "FlockMath.h"
#include "Globals.h"

class Vehicle {
public:
	Vehicle(sf::Vector2f position, std::vector<Vehicle>* vehicles);

	void Update(float dt);
	void Draw();

	//Move towards target
	void Seek(const sf::Vector2f& target);
	void Arrive(const sf::Vector2f& target);
	sf::Vector2f ComputeSeparation();

	sf::Vector2f ComputeAlignment();

	sf::Vector2f ComputeCohesion();

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
};