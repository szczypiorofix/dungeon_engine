#include "Player.h"
#include "GraphicAssets.h"


Player::Player(std::string name, float x, float y, int width, int height, SDL_Renderer* renderer) {
	this->name = name;
	this->width = width;
	this->height = height;
	this->direction = DIR_RIGHT;
	this->speed = 1.0f;
	this->tileIndex = 0;
	this->tileX = 0;
	this->tileY = 0;
	this->vector = new Vector2(x, y);
	this->moveVector = new Vector2(0.0f, 0.0f);
	this->moving = false;
	this->col = { (int)x, (int)y, width, height };
	this->renderer = renderer;

	// ==================== ANIMATION ==================== //

	const unsigned int framesPlayerLeft[]	= { 16, 17, 18 };
	const unsigned int framesPlayerRight[]	= { 28, 29, 30 };
	const unsigned int framesPlayerUp[]		= { 40, 41, 42 };
	const unsigned int framesPlayerDown[]	= { 4 , 5 , 6  };
	
	SpriteSheet* playerSprite = GraphicAssets::getAssets()->spriteSheets[SpriteSheet::CHARACTERS];
	this->walkingAnimation = new Animation * [4];

	this->walkingAnimation[DIR_UP]		= new Animation(playerSprite, 6, this->width, this->height, 3, framesPlayerUp);
	this->walkingAnimation[DIR_RIGHT]	= new Animation(playerSprite, 6, this->width, this->height, 3, framesPlayerRight);
	this->walkingAnimation[DIR_DOWN]	= new Animation(playerSprite, 6, this->width, this->height, 3, framesPlayerDown);
	this->walkingAnimation[DIR_LEFT]	= new Animation(playerSprite, 6, this->width, this->height, 3, framesPlayerLeft);

	this->walkingAnimation[this->direction]->setCurrentFrame(1);
}


Player::~Player() {
}

void Player::draw(float scale, float x, float y) {
	SDL_Rect drawRect = { 0, 0, 16, 16 };
	Animation* curAnim = this->walkingAnimation[this->direction];
	SDL_Rect tempClip = curAnim->getFrame(curAnim->getCurFrame());
	GraphicAssets::getAssets()->spriteSheets[SpriteSheet::CHARACTERS]->draw(
		this->renderer,
		&tempClip,
		(int) ( this->vector->x + x ),
		(int) ( this->vector->y + y ),
		scale);
}

void Player::update(float scale) {
	
	this->vector->x += (this->moveVector->x * scale);
	this->vector->y += (this->moveVector->y * scale);

	this->moving = true;

	if (this->moveVector->x == this->speed) {
		this->direction = DIR_RIGHT;
	}
	else if (this->moveVector->x == -this->speed) {
		this->direction = DIR_LEFT;
	}
	else if (this->moveVector->y == this->speed) {
		this->direction = DIR_DOWN;
	}
	else if (this->moveVector->y == -this->speed) {
		this->direction = DIR_UP;
	}
	else this->moving = false;

	if (this->moving) {
		this->walkingAnimation[this->direction]->nextFrame();
	}
}
