/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#ifndef _LEVEL_H_
#define _LEVEL_H_
#pragma once

#include <string>


class Level {

public:
	Level();
	~Level();

private:
	const std::string base64_chars =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	inline bool is_base64(unsigned char c);
	std::string base64_decode(std::string const& encoded_string);

};

#endif
