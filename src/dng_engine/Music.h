/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MUSIC_H_
#define _MUSIC_H_
#pragma once

#include <SDL_mixer.h>

class Music {

public:
	Music(const std::string musicFile);
	Music(const std::string musicFile, int volume);
	~Music();

	Mix_Music* getMusic();

	bool playMusic(bool _loop);
	bool playMusic(int _volume);
	bool playMusic(bool _loop, int _volume);

	static const int DEFAULT_MUSIC_VOLUME = 25;

private:
	Mix_Music* music;
	int volume;
	bool loop;
	bool playMusic();
};

#endif
