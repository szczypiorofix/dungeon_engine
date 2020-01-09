#include "GameObject.h"

GameObject::GameObject() {
	mVector = new Vector2(0.0f, 0.0f);
	mWidth = 0;
	mHeight = 0;
}

GameObject::GameObject(Vector2* vec, int width, int height) {
	mVector = vec;
	mWidth = width;
	mHeight = height;
}

GameObject::~GameObject() {
}

int GameObject::getTileX(unsigned int tileWidth) {
	return (int)((mVector->x + (mWidth / 2)) / tileWidth);
}

int GameObject::getTileY(unsigned int tileHeight) {
	return (int)((mVector->y + (mHeight / 2)) / tileHeight);
}
