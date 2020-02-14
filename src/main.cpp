/*
 * Dungeon Engine v0.1.0
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <iostream>

#include "game/DungeonGame.h"


//#include <GL\glew.h>
//#include <GL\glut.h>
//#include <GL\freeglut.h>



//#define UP 1
//#define DOWN -1
//#define RIGHT 2
//#define LEFT -2
#define WIDTH 800
#define HEIGHT 600
#define FPS 60


//void display_callback();
//void init();
//void timer_callback(int);
//void processSpecialKeys(int, int, int);
//void processNormalKeys(unsigned char key, int x, int y);
//
//void init() {
//	glMatrixMode(GL_PROJECTION);
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//}
//
//void display_callback() {
//
//	glClear(GL_COLOR_BUFFER_BIT);
//	glPushMatrix();
//
//	glClear(GL_COLOR_BUFFER_BIT);
//	glPushMatrix();
//	glOrtho(0, WIDTH, HEIGHT, 0, -1.0, 1.0); // Set the matrix
//
//	// ================================= Render Start =================================
//	glBegin(GL_TRIANGLES); //GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON
//		glColor3ub(255, 0, 0);
//		glVertex2f(400, 200);
//		glColor3ub(0, 255, 0);
//		glVertex2f(600, 400);
//		glColor3ub(0, 0, 255);
//		glVertex2f(200, 400);
//	glEnd();
//
//	// ================================== Render End ==================================
//
//	glPopMatrix();
//	// ----------------------------------------------------------
//
//	glutSwapBuffers();
//
//}
//
//void processSpecialKeys(int key, int mouseX, int mouseY) {
//
//}
//
//void processNormalKeys(unsigned char key, int mouseX, int mouseY) {
//	if (key == 27) {
//		exit(0);
//	}
//}
//
//void timer_callback(int) {
//	glutPostRedisplay();
//	glutTimerFunc(1000 / FPS, timer_callback, 0);
//}

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
	



	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	//glutInitWindowSize(500, 500);
	//glutCreateWindow("GLUCIK");
	//glutDisplayFunc(display_callback);
	////glutReshapeFunc(reshape_callback);
	//glutTimerFunc(0, timer_callback, 0);
	//glutKeyboardFunc(processNormalKeys);
	//glutSpecialFunc(processSpecialKeys);
	//init();
	//glutMainLoop();

	return 0;

}

