#include "FlockMath.h"

float FlockMath::Magnitude(const sf::Vector2f& vector) {
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
}

sf::Vector2f FlockMath::Normalize(sf::Vector2f vector) {
	float length = Magnitude(vector);

	if (length == 0) return sf::Vector2f(0, 0);

	vector.x = vector.x / length;
	vector.y = vector.y / length;

	return vector;
}

void FlockMath::Limit(sf::Vector2f& vector, float limit) {
	if (Magnitude(vector) > limit) {
		vector = Normalize(vector);
		vector.x *= limit;
		vector.y *= limit;
	}
}

float FlockMath::Dot(sf::Vector2f v1, sf::Vector2f v2) {
	return v1.x*v2.x + v1.y*v2.y;
}

float FlockMath::AngleBetween(sf::Vector2f v1, sf::Vector2f v2) {
	return acos(Dot(v1, v2) / (Magnitude(v1) * Magnitude(v2)));
}

float FlockMath::Heading(const sf::Vector2f& vector) {
	float result = atan2(vector.y, vector.x);
	result = result * (float)(180 / M_PI);
	return result;
}

float FlockMath::Map(float value, float start1, float  stop1, float  start2, float stop2) {
	float slope = (stop2 - start2) / (stop1 - start1);
	return start2 + slope * (value - start1);
}
