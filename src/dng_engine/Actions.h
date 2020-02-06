#ifndef _ACTIONS_H_
#define _ACTIONS_H_
#pragma once


class Actions {

public:

	void doNewGame();
	void doQuit();

};

typedef void (Actions::* ActionsMemFn)();


#endif
