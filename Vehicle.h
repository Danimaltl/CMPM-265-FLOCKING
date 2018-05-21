#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "FlockMath.h"

class Vehicle {
public:
	Vehicle(sf::Vector2f position);

	void Update();
	void Draw(sf::RenderWindow window);

	//Move towards target
	void Seek(const sf::Vector2f& target);

private:
	sf::ConvexShape m_Shape;

	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Acceleration;

	float m_MaxSpeed;
	float m_MaxForce;

	void ApplyForce(const sf::Vector2f& force);

};