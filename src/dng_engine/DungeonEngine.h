/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _DUNGEONENGINE_H_
#define _DUNGEONENGINE_H_
#pragma once

#include <string>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_net.h>

#include "Music.h"
#include "GraphicAssets.h"
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
	
	void loadImageToAssets(std::string fileName, int spriteWidth, int spriteHeight, int imagesEnum);
	void drawImage(const int SpriteSheetNo, SDL_Rect clip, int x, int y);

	void initTimer();

	bool loadMusic(std::string musicFile);
	bool playMusic(bool loop, int volume);

	GLuint loadTexture(const std::string& fileName);

protected:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_GLContext glContext;

	Camera* camera;

	Vector2* scrollVector;

	ViewLockedOn viewLockedOn;

private:

	Music* currentMusic;

	bool started;
	bool quit;
	int tilesOnScreenFromCenterX;
	int tilesOnScreenFromCenterY;

	bool writeConfigFile();
	bool readConfigFile();

	void initSDL();
	void createWindow();
	void createRenderer();
	void initOGL();
	void initializePngImages();
	void initializeAudioSystem();
	void initializeNetworkSystem();

};

#endif
