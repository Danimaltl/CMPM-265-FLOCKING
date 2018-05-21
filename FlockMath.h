#pragma once
#include "SFML\System.hpp"
#include <cmath>
#include "Globals.h"

namespace FlockMath {
	float Magnitude(const sf::Vector2f& vector);

	sf::Vector2f Normalize(sf::Vector2f vector);

	void Limit(sf::Vector2f& vector, float limit);

	float Heading(const sf::Vector2f& vector);
}