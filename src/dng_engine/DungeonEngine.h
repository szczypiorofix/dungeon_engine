/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _DUNGEONENGINE_H_
#define _DUNGEONENGINE_H_
#pragma once

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_net.h>
#include <libxml/parser.h>

#include "Camera.h"
#include "Vector2.h"
#include "TextFont.h"


enum class ViewLockedOn {
	PLAYER,
	MOUSE
};

typedef struct Settings {
	int screenWidth;
	int screenHeight;
	float scale;
	int fullScreen;
	int musicVolume;
} Settings;


class DungeonEngine {

public:
	DungeonEngine();
	~DungeonEngine();

	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;

	static const int MIN_SCALE = 1;
	static const int MAX_SCALE = 5;

	const char* CONFIG_FILE_NAME = "dungeon_engine.cfg";

	void launchSubsystems(void);
	void stop(void);

	Settings settings;
	float scale;

	bool isQuit();
	void setQuit(bool quit);

	SDL_Cursor* cursor;
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	TextFont* createFont(std::string, bool s);

	void initTimer();

	bool loadMusic(const std::string musicFile);
	Mix_Music* getMusic();

protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Mix_Music* music;
	Camera* camera;

	Vector2* scrollVector;

	ViewLockedOn viewLockedOn;

private:
	bool started;
	bool quit;
	int tilesOnScreenFromCenterX;
	int tilesOnScreenFromCenterY;

	long lastTime;
	double delta;
	long timer;
	int updates;
	int frames;
	long now;
	float amountOfTicks;
	int fpsCount;
	int ticksCount;
	double ns;
	bool fpsCap;
	int displayMode;
	char coordinatesText[80];
	bool mouseRightButtonPressed;


	bool writeConfigFile();
	bool readConfigFile();

	void initSDL();
	void createWindow();
	void createRenderer();
	void initializePngImages();
	void initializeAudioSystem();
	void initializeNetworkSystem();

};

#endif
