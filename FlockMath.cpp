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

float FlockMath::Heading(const sf::Vector2f& vector) {
	float result = atan2(vector.y, vector.x);
	result = result * (180 / M_PI);
	return result;
}