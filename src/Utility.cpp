#include "Utility.h"

int sign(int number) {
	if (number < 0.0f) {
		return -1;
	} else {
		return 1;
	}
}

float toDegrees(float radian){
    return (float)(radian * 180 / PI);
}

float toRadians(float degree){
    return (float)(degree * PI / 180);
}

float angle(sf::Vector2f p1, sf::Vector2f p2) {
	return toDegrees(atan2(p2.y - p1.y, p2.x - p1.x));
}

float distance(sf::Vector2f p1, sf::Vector2f p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

sf::Vector2f makeVector(float angle, float magnitude, sf::Vector2f offset) {
	return sf::Vector2f(cos(toRadians(angle)) * magnitude, sin(toRadians(angle)) * magnitude) + offset;
}

std::string toString(int num) {
	std::ostringstream os;
	os << num;
	return os.str();
}

std::string toString(float num) {
	std::ostringstream os;
	os << num;
	return os.str();
}

std::string toString(double num) {
	std::ostringstream os;
	os << num;
	return os.str();
}

int min(int n1, int n2) {
	if (n1 < n2) {
		return n1;
	} else {
		return n2;
	}
}

float min(float n1, float n2) {
	if (n1 < n2) {
		return n1;
	} else {
		return n2;
	}
}

int max(int n1, int n2) {
	if (n1 > n2) {
		return n1;
	} else {
		return n2;
	}
}

float max(float n1, float n2) {
	if (n1 > n2) {
		return n1;
	} else {
		return n2;
	}
}

int round(float n) {
    return floor( n + 0.5 );
}