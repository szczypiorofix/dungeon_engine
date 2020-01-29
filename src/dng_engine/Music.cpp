/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <iostream>
#include "Music.h"
#include "Defines.h"

Music::Music(const std::string musicFile) {
	this->volume = Music::DEFAULT_MUSIC_VOLUME;
	this->loop = false;
	std::string musicFileName = DIR_RES_MUSIC + musicFile;
	this->music = Mix_LoadMUS(musicFileName.c_str());
	if (this->music == NULL) {
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit(1);
	}
}


Music::Music(const std::string musicFile, int volume) {
	this->volume = volume;
	this->loop = false;
	std::string musicFileName = DIR_RES_MUSIC + musicFile;
	this->music = Mix_LoadMUS(musicFileName.c_str());
	if (this->music == NULL) {
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		exit(1);
	}
}


Music::~Music() {
#ifdef _DEBUG 
	std::cout << "Releasing music... ";
#endif
	Mix_FreeMusic(this->music);
#ifdef _DEBUG 
	std::cout << "done." << std::endl;
#endif
}


Mix_Music* Music::getMusic() {
	return this->music;
}


bool Music::playMusic() {
	if (Mix_PlayingMusic() == 0) {
		if (this->loop) {
			Mix_PlayMusic(this->music, -1); // -1 play forever, 0 - no play
		}
		else {
			Mix_PlayMusic(this->music, 0); // -1 play forever, 0 - no play
		}
		
		Mix_VolumeMusic(this->volume);
	}
	return true;
}


bool Music::playMusic(bool _loop) {
	this->loop = _loop;
	this->playMusic();
	return true;
}


bool Music::playMusic(int _volume) {
	this->volume = _volume;
	Mix_VolumeMusic(_volume);
	this->playMusic();
	return true;
}


bool Music::playMusic(bool _loop, int _volume) {
	this->volume = _volume;
	this->loop = _loop;
	Mix_VolumeMusic(_volume);
	this->playMusic();
	return true;
}
