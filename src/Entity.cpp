#include "Entity.h"

Entity::Entity() {
	m_position = sf::Vector2f(0, 0);
	m_velocity = sf::Vector2f(0, 0);
	m_size = sf::Vector2f(0, 0);
	m_angle = 0;
	m_mass = 0;
}

Entity::~Entity() {
}

sf::Vector2f Entity::getPosition() {
	return m_position;
}

sf::Vector2f Entity::getVelocity() {
	return m_velocity;
}

sf::Vector2f Entity::getSize() {
	return m_size;
}

float Entity::getAngle() {
	return m_angle;
}

float Entity::getMass() {
	return m_mass;
}

void Entity::setPosition(sf::Vector2f position) {
	m_position = position;
}

void Entity::setVelocity(sf::Vector2f velocity) {
	m_velocity = velocity;
}

void Entity::setSize(sf::Vector2f size) {
	m_size = size;
}

void Entity::setAngle(float angle) {
	m_angle = angle;
}

void Entity::setMass(float mass) {
	m_mass = mass;
}

void Entity::step() {
}

void Entity::update() {
	m_position += m_velocity;
}

void Entity::render() {
}

int Entity::getType() {
	return m_type;
}

void Entity::beginContact(Entity *entity) {
}

void Entity::endContact(Entity *entity) {
}

void Entity::onClick() {
}

void Entity::onRelease() {
}

void Entity::onEnter() {
}

void Entity::onExit() {
}