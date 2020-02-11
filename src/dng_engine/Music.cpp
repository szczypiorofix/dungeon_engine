/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <iostream>
#include "Music.h"
#include "Defines.h"





 // ############################ BASS ############################

//BASS_Init(-1, 44100, 0, 0, NULL);
//std::cout << "ERROR CODE: " << BASS_ErrorGetCode() << std::endl;

// ############### FOR MOD & XM #####################
//HMUSIC music = BASS_MusicLoad(FALSE, "../res/music/ex-aws_cave.xm", 0, 0, 0, 0);
//std::cout << "ERROR CODE: " << BASS_ErrorGetCode() << std::endl;

//BASS_ChannelPlay(music, TRUE);

// ########### SAMPLE ############
//HSAMPLE sample = BASS_SampleLoad(FALSE, "../res/music/menu-music.ogg", 0, 0, 1, 0);
//HCHANNEL channel = BASS_SampleGetChannel(sample, TRUE);
//std::cout << "Sample: " << sample << std::endl;
//std::cout << "ERROR CODE: " << BASS_ErrorGetCode() << std::endl;
//BASS_Start();
//std::cout << "ERROR CODE: " << BASS_ErrorGetCode() << std::endl;
//
//BASS_ChannelPlay(channel, TRUE);
//std::cout << "ERROR CODE: " << BASS_ErrorGetCode() << std::endl;



Music::Music(const std::string musicFile) {
	this->volume = Music::DEFAULT_MUSIC_VOLUME;
	this->loop = false;
	std::string musicFileName = DIR_RES_MUSIC + musicFile;
	this->sample = BASS_SampleLoad(FALSE, musicFileName.c_str(), 0, 0, 1, 0);
	if (this->sample == 0) {
		std::cout << "Failed to load sample! BASS_SampleLoad Error: " << BASS_ErrorGetCode() << std::endl;
		exit(1);
	}
	this->channel = BASS_SampleGetChannel(sample, TRUE);
	if (this->channel == NULL) {
		std::cout << "Failed to get channel! BASS_SampleGetChannel Error: " << BASS_ErrorGetCode() << std::endl;
		exit(1);
	}
}


Music::Music(const std::string musicFile, float volume) {
	this->volume = volume;
	this->loop = false;
	std::string musicFileName = DIR_RES_MUSIC + musicFile;
	this->sample = BASS_SampleLoad(FALSE, musicFileName.c_str(), 0, 0, 1, 0);
	if (this->sample == 0) {
		std::cout << "Failed to load sample! BASS_SampleLoad Error: " << BASS_ErrorGetCode() << std::endl;
		exit(1);
	}
	this->channel = BASS_SampleGetChannel(sample, TRUE);
	if (this->channel == NULL) {
		std::cout << "Failed to get channel! BASS_SampleGetChannel Error: " << BASS_ErrorGetCode() << std::endl;
		exit(1);
	}
}


Music::~Music() {
#ifdef _DEBUG 
	std::cout << "Releasing music... ";
#endif
	BASS_Free();
#ifdef _DEBUG 
	std::cout << "done." << std::endl;
#endif
}


bool Music::playMusic() {
	BASS_ChannelPlay(this->channel, TRUE);
	return true;
}


bool Music::playMusic(bool _loop) {
	this->loop = _loop;
	this->playMusic();
	return true;
}


bool Music::playMusic(float _volume) {
	this->volume = _volume;
	BASS_SetVolume(_volume);
	BASS_ChannelPlay(this->channel, TRUE);
	return true;
}

