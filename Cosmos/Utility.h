#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <cmath>

#include <SFML/Graphics.hpp>

#include <sstream>
#include <string>

#include "Constants.h"

int sign(int number);

float toDegrees(float radian);
float toRadians(float degree);

float angle(sf::Vector2f p1, sf::Vector2f p2);
float distance(sf::Vector2f p1, sf::Vector2f p2);

sf::Vector2f makeVector(float angle, float magnitude, sf::Vector2f offset = sf::Vector2f(0, 0));

std::string toString(int num);
std::string toString(float num);
std::string toString(double num);

int min(int n1, int n2);
float min(float n1, float n2);
int max(int n1, int n2);
float max(float n1, float n2);

int round(float n);

#endif