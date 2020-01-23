/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */


#include "GameManager.h"


int main(int argc, char* argv[]) {
	
	if (argc > 1) {
		printf("Parameters: (%i)\n", argc);
		for (int i = 1; i < argc; i++) {
			std::cout << i << ":" << argv[i] << std::endl;
		}
	}

	GameManager* gameManager = new GameManager();
	gameManager->launch();
	
	return 0;

}
