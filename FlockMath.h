#pragma once
#include "SFML\System.hpp"
#include <cmath>

namespace FlockMath {
	float Magnitude(const sf::Vector2f& vector) {
		return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
	}

	sf::Vector2f Normalize(sf::Vector2f vector) {
		float length = Magnitude(vector);

		vector.x = vector.x / length;
		vector.y = vector.y / length;

		return vector;
	}

	void Limit(sf::Vector2f& vector, float limit) {
		if (Magnitude(vector) > limit) {
			vector = Normalize(vector);
			vector.x *= limit;
			vector.y *= limit;
		}
	}

	float Heading(const sf::Vector2f& vector) {
		return atan2(vector.y, vector.x);
	}
}