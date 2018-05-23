#include "Vehicle.h"

Vehicle::Vehicle(sf::Vector2f position, std::vector<Vehicle>* vehicles) {
	m_Acceleration = sf::Vector2f(0, 0);
	m_Velocity = sf::Vector2f(0, 0);
	m_Position = position;

	//Set shape attributes
	m_Shape.setPointCount(3);
	m_Shape.setPoint(0, sf::Vector2f(0, 0));
	m_Shape.setPoint(1, sf::Vector2f(25, 10));
	m_Shape.setPoint(2, sf::Vector2f(0, 20));
	m_Shape.setFillColor(sf::Color(31, 84, 145));
	m_Shape.setOutlineThickness(1);
	m_Shape.setOutlineColor(sf::Color(100,100,100));
	m_Shape.setOrigin(sf::Vector2f(10, 10));
	m_Shape.setPosition(m_Position);

	m_MaxSpeed = 350;
	m_MaxForce = 300;

	m_ArriveRadius = 100;
	m_NeighborRadius = 50;

	m_Vehicles = vehicles;
}

void Vehicle::Update(float dt) {
	ApplyForce(ComputeSeparation() * 1.5f);
	ApplyForce(ComputeAlignment());
	ApplyForce(ComputeAlignment() * .8f);

	m_Velocity += m_Acceleration * dt;
	FlockMath::Limit(m_Velocity, m_MaxSpeed);
	m_Position += m_Velocity * dt;
	m_Acceleration = m_Acceleration * 0.0f; //reset so forces don't continue when stopped

	if (m_Position.x > SCREEN_WIDTH) {
		m_Position.x -= SCREEN_WIDTH;
	}
	else if (m_Position.x < 0) {
		m_Position.x += SCREEN_WIDTH;
	}

	if (m_Position.y > SCREEN_HEIGHT) {
		m_Position.y -= SCREEN_HEIGHT;
	}
	else if (m_Position.y < 0) {
		m_Position.y += SCREEN_HEIGHT;
	}
	//printf("m_Position: %f, %f\n", m_Position.x, m_Position.y);
	//printf("m_Velocity: %f, %f\n", m_Velocity.x, m_Velocity.y);

	//Set new shape position and rotation
	m_Shape.setPosition(m_Position);
	//printf("Heading: %f\n", FlockMath::Heading(m_Velocity));
	m_Shape.setRotation(FlockMath::Heading(m_Velocity));
}

void Vehicle::Draw() {
	window.draw(m_Shape);
}

void Vehicle::Seek(const sf::Vector2f& target) {
	sf::Vector2f desired = target - m_Position;  //Vector to target from my position
	desired = FlockMath::Normalize(desired);     //Normalize
	desired *= m_MaxSpeed;                       //Magnitude = maxSpeed

	sf::Vector2f steer = desired - m_Velocity;   //Vector to desired velocity from my velocity (force)

	FlockMath::Limit(steer, m_MaxForce);         //Limit magnitude of force

	ApplyForce(steer);
}

void Vehicle::Arrive(const sf::Vector2f& target) {
	sf::Vector2f desired = target - m_Position;
	float d = FlockMath::Magnitude(desired);
	desired = FlockMath::Normalize(desired);
	if (d < m_ArriveRadius) {
		float m = FlockMath::Map(d, 0, m_ArriveRadius, 0, m_MaxSpeed);
		//float m = (d/m_ArriveRadius)*m_MaxSpeed;
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

sf::Vector2f Vehicle::ComputeSeparation() {
	sf::Vector2f desired;
	float count = 0;
	
	if (m_Vehicles->size() == 0) {
		printf("Size is 0\n");
		return sf::Vector2f(0, 0);
	}

	for (size_t i = 0; i < m_Vehicles->size(); i++) {
		Vehicle* current = &m_Vehicles->at(i);
		if (current == this) 
			continue;

		float d = FlockMath::Magnitude(m_Position - current->m_Position);
		if (d < m_NeighborRadius) {
			desired += FlockMath::Normalize(m_Position - current->m_Position);
			count++;
		}
	}

	if (count == 0) {
		printf("Count is 0\n");
		return sf::Vector2f(0, 0);
	}
	desired = desired / count;
	desired = FlockMath::Normalize(desired);
	desired *= m_MaxSpeed;
	sf::Vector2f steer = desired - m_Velocity;
	FlockMath::Limit(steer, m_MaxForce);

	return steer;
}

sf::Vector2f Vehicle::ComputeAlignment() {
	sf::Vector2f desired;
	float count = 0;

	if (m_Vehicles->size() == 0) {
		printf("Size is 0\n");
		return sf::Vector2f(0, 0);
	}

	for (size_t i = 0; i < m_Vehicles->size(); i++) {
		Vehicle* current = &m_Vehicles->at(i);
		if (current == this)
			continue;

		float d = FlockMath::Magnitude(m_Position - current->m_Position);
		if (d < m_NeighborRadius) {
			desired += current->m_Velocity;
			count++;
		}
	}

	if (count == 0) {
		printf("Count is 0\n");
		return sf::Vector2f(0, 0);
	}
	desired = desired / count;
	desired = FlockMath::Normalize(desired);
	desired *= m_MaxSpeed;
	sf::Vector2f steer = desired - m_Velocity;
	FlockMath::Limit(steer, m_MaxForce);

	return steer;
}

sf::Vector2f Vehicle::ComputeCohesion() {
	sf::Vector2f desired;
	float count = 0;

	if (m_Vehicles->size() == 0) {
		printf("Size is 0\n");
		return sf::Vector2f(0, 0);
	}

	for (size_t i = 0; i < m_Vehicles->size(); i++) {
		Vehicle* current = &m_Vehicles->at(i);
		if (current == this)
			continue;

		float d = FlockMath::Magnitude(m_Position - current->m_Position);
		if (d < m_NeighborRadius) {
			desired += current->m_Position;
			count++;
		}
	}

	if (count == 0) {
		printf("Count is 0\n");
		return sf::Vector2f(0, 0);
	}
	desired = desired / count;
	desired = desired - m_Position;
	desired = FlockMath::Normalize(desired);
	desired *= m_MaxSpeed;
	sf::Vector2f steer = desired - m_Velocity;
	FlockMath::Limit(steer, m_MaxForce);

	return steer;
}