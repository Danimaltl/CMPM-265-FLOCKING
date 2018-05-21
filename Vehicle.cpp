#include "Vehicle.h"

Vehicle::Vehicle(sf::Vector2f position) {
	m_Acceleration = sf::Vector2f(0, 0);
	m_Velocity = sf::Vector2f(0, 0);
	m_Position = sf::Vector2f();

	//Set shape attributes
	m_Shape.setPointCount(3);
	m_Shape.setPoint(0, sf::Vector2f(0, 0));
	m_Shape.setPoint(1, sf::Vector2f(20, 10));
	m_Shape.setPoint(2, sf::Vector2f(0, 20));
	m_Shape.setFillColor(sf::Color::Green);
	m_Shape.setOutlineThickness(2);
	m_Shape.setOutlineColor(sf::Color::Black);
	m_Shape.setOrigin(sf::Vector2f(10, 10));

	m_MaxSpeed = 400;
	m_MaxForce = 300;

	m_ArriveRadius = 100;
}

void Vehicle::Update(float dt) {
	m_Velocity += m_Acceleration * dt;
	FlockMath::Limit(m_Velocity, m_MaxSpeed);
	m_Position += m_Velocity * dt;
	m_Acceleration = m_Acceleration * 0.0f; //reset so forces don't continue when stopped

	//printf("m_Position: %f, %f\n", m_Position.x, m_Position.y);
	//printf("m_Velocity: %f, %f\n", m_Velocity.x, m_Velocity.y);

	//Set new shape position and rotation
	m_Shape.setPosition(m_Position);
	printf("Heading: %f\n", FlockMath::Heading(m_Velocity));
	m_Shape.setRotation(FlockMath::Heading(m_Velocity));
}

void Vehicle::Draw() {
	window.draw(m_Shape);
}

void Vehicle::Seek(const sf::Vector2f& target, float dt) {
	
	
	sf::Vector2f desired = target - m_Position;
	desired = FlockMath::Normalize(desired);
	desired *= m_MaxSpeed;

	sf::Vector2f steer = desired - m_Velocity;

	FlockMath::Limit(steer, m_MaxForce);

	ApplyForce(steer);
}

void Vehicle::Arrive(const sf::Vector2f& target, float dt) {
	sf::Vector2f desired = target - m_Position;
	float d = FlockMath::Magnitude(desired);
	desired = FlockMath::Normalize(desired);
	if (d < m_ArriveRadius) {
		float m = FlockMath::Map(d, 0, m_ArriveRadius, 0, m_MaxSpeed);
		desired *= m;
	}
	else {
		desired *= m_MaxSpeed;
	}

	sf::Vector2f steer = desired - m_Velocity;

	FlockMath::Limit(steer, m_MaxForce);

	ApplyForce(steer);
}

void Vehicle::ApplyForce(const sf::Vector2f& force) {
	m_Acceleration += force;
}