#pragma once
#include "SFML\System.hpp"
#include <cmath>
#include "Globals.h"

namespace FlockMath {
	float Magnitude(const sf::Vector2f& vector);

	sf::Vector2f Normalize(sf::Vector2f vector);

	void Limit(sf::Vector2f& vector, float limit);

	float Heading(const sf::Vector2f& vector);

	float Map(float value, float start1, float  stop1, float  start2, float stop2);
}