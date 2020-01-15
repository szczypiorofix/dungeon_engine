#include "GameObject.h"

GameObject::GameObject() {
	this->vector = new Vector2(0.0f, 0.0f);
	this->width = 0;
	this->height = 0;
}

GameObject::GameObject(Vector2* vec, int width, int height) {
	this->vector = vec;
	this->width = width;
	this->height = height;
}

GameObject::~GameObject() {
}

int GameObject::getTileX(unsigned int tileWidth) {
	return (int)((this->vector->x + (this->width / 2)) / tileWidth);
}

int GameObject::getTileY(unsigned int tileHeight) {
	return (int)((this->vector->y + (this->height / 2)) / tileHeight);
}
