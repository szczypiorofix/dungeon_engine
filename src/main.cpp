/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */


#include "game/DungeonGame.h"


int main(int argc, char* argv[]) {
	
	if (argc > 1) {
		printf("Parameters: (%i)\n", argc);
		for (int i = 1; i < argc; i++) {
			std::cout << i << ":" << argv[i] << std::endl;
		}
	}

	DungeonGame* game = new DungeonGame();
	game->launch();
	
	return 0;

}
