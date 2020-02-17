/*
 * Dungeon Engine v0.1.0
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <iostream>

#include "game/DungeonGame.h"


/**
* Main entry point
*/
int main(int argc, char* argv[]) {
	
	if (argc > 1) {
		std::cout << "Parameters: " << argc << std::endl;
		for (int i = 1; i < argc; i++) {
			std::cout << i << ":" << argv[i] << std::endl;
		}
	}

	DungeonGame* game = new DungeonGame();
	game->launch();
	
	return 0;

}

