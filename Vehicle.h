#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "FlockMath.h"
#include "Globals.h"

class Vehicle {
public:
	Vehicle(sf::Vector2f position);

	void Update(float dt);
	void Draw();

	//Move towards target
	void Seek(const sf::Vector2f& target, float dt);
	void Arrive(const sf::Vector2f& target, float dt);

private:
	sf::ConvexShape m_Shape;

	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;

	float m_MaxSpeed;
	float m_MaxForce;

	float m_ArriveRadius;

	void ApplyForce(const sf::Vector2f& force);

};