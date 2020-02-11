/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _MUSIC_H_
#define _MUSIC_H_
#pragma once

#include <BASS/bass.h>

class Music {

public:
	Music(const std::string musicFile);
	Music(const std::string musicFile, float volume);
	~Music();

	bool playMusic(bool _loop);
	bool playMusic(float _volume);

	constexpr static float DEFAULT_MUSIC_VOLUME = 1.0f;

private:
	HSAMPLE sample;
	HCHANNEL channel;

	float volume;
	bool loop;
	bool playMusic();
};

#endif
