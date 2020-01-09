#include "Player.h"
#include "GraphicAssets.h"


Player::Player(std::string name, float x, float y, int width, int height, SDL_Renderer* renderer) {
	mName = name;
	mWidth = width;
	mHeight = height;
	mDirection = Direction::DIR_RIGHT;
	mSpeed = 1.0f;
	mTileIndex = 0;
	mTileX = 0;
	mTileY = 0;
	mVector = new Vector2(x, y);
	mMoveVector = new Vector2(0.0f, 0.0f);
	mMoving = false;
	SDL_Rect c = { (int) x, (int) y, width, height };
	mCol = c;
	mRenderer = renderer;

	// ==================== ANIMATION ==================== //

	const unsigned int framesPlayerLeft[]	= { 16, 17, 18 };
	const unsigned int framesPlayerRight[]	= { 28, 29, 30 };
	const unsigned int framesPlayerUp[]		= { 40, 41, 42 };
	const unsigned int framesPlayerDown[]	= { 4 , 5 , 6  };
	
	SpriteSheet* playerSprite = GraphicAssets::getAssets()->spriteSheets[SpriteSheet::CHARACTERS];
	mWalkingAnimation = new Animation * [4];

	mWalkingAnimation[Direction::DIR_UP]	= new Animation(playerSprite, 6, mWidth, mHeight, 3, framesPlayerUp);
	mWalkingAnimation[Direction::DIR_RIGHT]	= new Animation(playerSprite, 6, mWidth, mHeight, 3, framesPlayerRight);
	mWalkingAnimation[Direction::DIR_DOWN]	= new Animation(playerSprite, 6, mWidth, mHeight, 3, framesPlayerDown);
	mWalkingAnimation[Direction::DIR_LEFT]	= new Animation(playerSprite, 6, mWidth, mHeight, 3, framesPlayerLeft);

	mWalkingAnimation[mDirection]->setCurrentFrame(1);
}


Player::~Player() {
}

std::string Player::getName()
{
	return mName;
}

float Player::getSpeed()
{
	return mSpeed;
}

int Player::getWidth()
{
	return mWidth;
}

int Player::getHeight()
{
	return mHeight;
}

int Player::getTileX()
{
	return mTileX;
}

int Player::getTileY()
{
	return mTileY;
}

int Player::getTileIndex()
{
	return mTileIndex;
}

bool Player::isMoving()
{
	return mMoving;
}

SDL_Rect Player::getCollision()
{
	return mCol;
}

Direction Player::getDirection() {
	return mDirection;
}

Animation** Player::getAnimation()
{
	return mWalkingAnimation;
}

void Player::setAnimation(Animation** anim) {
	mWalkingAnimation = anim;
}

void Player::setDirection(Direction dir) {
	mDirection = dir;
}

void Player::setMoving(bool moving) {
	mMoving = moving;
}

void Player::draw(float scale, float ox, float oy) {
	SDL_Rect drawRect = { 0, 0, 16, 16 };
	Animation* curAnim = mWalkingAnimation[mDirection];
	SDL_Rect tempClip = curAnim->getFrame(curAnim->getCurFrame());
	GraphicAssets::getAssets()->spriteSheets[SpriteSheet::CHARACTERS]->draw(
		mRenderer,
		&tempClip,
		(int) ( mVector->x + ox ),
		(int) ( mVector->y + oy ),
		scale);
}

void Player::update(float scale) {
	
	//*mVector += *mMoveVector;

	mVector->x += (mMoveVector->x * scale);
	mVector->y += (mMoveVector->y * scale);

	mMoving = true;

	if (mMoveVector->x == mSpeed) {
		mDirection = Direction::DIR_RIGHT;
	}
	else if (mMoveVector->x == -mSpeed) {
		mDirection = Direction::DIR_LEFT;
	}
	else if (mMoveVector->y == mSpeed) {
		mDirection = Direction::DIR_DOWN;
	}
	else if (mMoveVector->y == -mSpeed) {
		mDirection = Direction::DIR_UP;
	}
	else mMoving = false;

	if (mMoving) {
		mWalkingAnimation[mDirection]->nextFrame();
	}
}
