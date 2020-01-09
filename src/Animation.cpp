#include "Animation.h"


Animation::Animation(SpriteSheet* spriteSheet, unsigned short speed, unsigned int sw, unsigned int sh, const unsigned short size, const unsigned int* frames) {
	mSize = size;
	mSpeed = speed;
	mCounter = 0;
	mCurFrame = 0;
	mSpriteSheet = spriteSheet;
	mFrames = new SDL_Rect[size];

	for (unsigned int i = 0; i < size; i++) {
		int col = spriteSheet->getWidth() / spriteSheet->getTileWidth();
		mFrames[i].x = ((frames[i] - 1) % col) * sw;
		mFrames[i].y = ((frames[i] - 1) / col) * sh;
		mFrames[i].w = sw;
		mFrames[i].h = sh;
	}
}

int Animation::nextFrame() {
	mCounter++;
	if (mCounter > mSpeed) {
		mCounter = 0;
		mCurFrame++;
		if (mCurFrame >= mSize)
			mCurFrame = 0;
	}
	return mCurFrame;
}

SDL_Rect Animation::getFrame(int index)
{
	return mFrames[index];
}

int Animation::getCurFrame()
{
	return mCurFrame;
}

void Animation::setCurrentFrame(int curFrame)
{
	mCurFrame = curFrame;
}

Animation::~Animation() {

}

