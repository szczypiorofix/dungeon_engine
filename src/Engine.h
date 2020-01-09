#ifndef _ENGINE_H_
#define _ENGINE_H_
#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <libxml/parser.h>

#include "Camera.h"
#include "Vector2.h"
#include "TextFont.h"


enum class ViewLockedOn {
	PLAYER,
	MOUSE
};


class Engine
{
public:
	Engine();
	~Engine();

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static const int MIN_SCALE = 1;
	static const int MAX_SCALE = 5;

	void launchSubsystems(void);
	void engineStop(void);

	float scale;

	bool isQuit();
	void setQuit(bool quit);

	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	void initTimer();

	bool loadMusic(const std::string musicFile);
	Mix_Music* getMusic();

private:
	bool mStarted;
	bool mQuit;
	int mTilesOnScreenFromCenterX;
	int mTilesOnScreenFromCenterY;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Mix_Music* mMusic;
	Camera* mCamera;

	Vector2* mScrollVector;

	bool mFullScreen;
	ViewLockedOn mViewLockedOn;
	int mMusicVolume;
	long mLastTime;
	double mDelta;
	long mTimer;
	int mUpdates;
	int mFrames;
	long mNow;
	float mAmountOfTicks;
	int mFpsCount;
	int mTicksCount;
	double mNs;
	bool mFpsCap;
	int mDisplayMode;
	//TextFont* mCoordinates;
	char mCoordinatesText[80];
	bool mMouseRightButtonPressed;


	void initSDL();
	void createWindow();
	void createRenderer();
	void initializePngImages();
	void initializeAudioSystem();
	void initializeTTFFonts();
};

#endif
