#include "Vehicle.h"

Vehicle::Vehicle(sf::Vector2f position) {
	m_Acceleration = sf::Vector2f(0, 0);
	m_Velocity = sf::Vector2f(0, 0);
	m_Position = sf::Vector2f();

	//Set shape attributes
	m_Shape.setPointCount(3);
	m_Shape.setPoint(0, sf::Vector2f(0, 0));
	m_Shape.setPoint(1, sf::Vector2f(10, 5));
	m_Shape.setPoint(2, sf::Vector2f(10, 0));
	m_Shape.setFillColor(sf::Color::Green);
	m_Shape.setOutlineThickness(2);

	m_MaxSpeed = 4;
	m_MaxForce = 0.1;
}

void Vehicle::Update() {
	m_Velocity += m_Acceleration;
	FlockMath::Limit(m_Velocity, m_MaxSpeed);
	m_Position += m_Velocity;
	m_Acceleration = m_Acceleration * 0.0f; //reset so forces don't continue when stopped

	//Set new shape position and rotation
	m_Shape.setPosition(m_Position);
	m_Shape.setRotation(FlockMath::Heading(m_Velocity));
}

void Vehicle::Draw(sf::RenderWindow window) {
	window.draw(m_Shape);
}

void Vehicle::Seek(const sf::Vector2f& target) {
	sf::Vector2f desired = target - m_Position;
	desired = FlockMath::Normalize(desired);
	desired *= m_MaxSpeed;

	sf::Vector2f steer = desired - m_Velocity;

	FlockMath::Limit(steer, m_MaxForce);

	ApplyForce(steer);
}

void Vehicle::ApplyForce(const sf::Vector2f& force) {
	m_Acceleration += force;
}