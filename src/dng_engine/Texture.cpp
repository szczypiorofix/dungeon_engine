/*
 * Dungeon Engine
 * Copyright (C) 2020 szczypiorofix <szczypiorofix@o2.pl>
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>

#include "Texture.h"
#include "Defines.h"


Texture::Texture(std::string fileName, GLfloat tileWidth, GLfloat tileHeight) {
	this->id = loadTexture(fileName);
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->columns = (int)(this->width / this->tileWidth);

	if (!this->initShaders()) {
		std::cout << "Unable to initialize OGL shaders." << std::endl;
		exit(1);
	}

#ifdef _DEBUG 
	std::cout << "Texture: " << fileName << ", columns: " << this->columns << std::endl;
#endif
	
}


Texture::Texture(std::string fileName) {
	this->id = loadTexture(fileName);
	this->tileWidth = 0.0f;
	this->tileHeight = 0.0f;
	this->columns = 0;

	if (!this->initShaders()) {
		std::cout << "Unable to initialize OGL shaders." << std::endl;
		exit(1);
	}

}


GLuint Texture::loadTexture(std::string fileName) {

	SDL_Surface* image = IMG_Load(fileName.c_str());
	if (image == NULL) {
		std::cout << "Unable to load image " << fileName << ", : " << IMG_GetError() << std::endl;
		exit(1);
	}

	this->width = (GLfloat)image->w;
	this->height = (GLfloat)image->h;

	unsigned object(0);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &object);
	glBindTexture(GL_TEXTURE_2D, object);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	glDisable(GL_TEXTURE_2D);

	SDL_FreeSurface(image);
	
	return object;
}


Texture::~Texture() {}


void Texture::drawTile(int _id, GLfloat dx, GLfloat dy) {

	if (this->tileWidth > 0 && this->tileHeight > 0) {
		glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, this->id);

		int sx = (int)( (_id % this->columns) * this->tileWidth );
		int sy = (int)( (_id / this->columns) * this->tileHeight );

		//GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON
		glBegin(GL_QUADS);

			glTexCoord2f( sx / this->width, sy / this->height );
			glVertex2f( dx, dy );

			glTexCoord2f( (sx + this->tileWidth) / this->width, sy / this->height );
			glVertex2f( dx + this->tileWidth, dy );

			glTexCoord2f( (sx + this->tileWidth) / this->width, (sy + this->tileHeight) / this->height );
			glVertex2f( dx + this->tileWidth, dy + this->tileHeight );

			glTexCoord2f( sx / this->width, (sy + this->tileHeight) / this->height );
			glVertex2f( dx, dy + this->tileHeight );

		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

}


void Texture::draw(TextureRect src, TextureRect dest) {
	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->id);

	//GL_POINTS, GL_LINES, GL_LINE_STRIP, GL_LINE_LOOP, GL_QUADS, GL_TRIANGLES, GL_POLIGON
	glBegin(GL_QUADS);

		glTexCoord2f( src.x / this->width, src.y / this->height );
		glVertex2f( dest.x, dest.y );

		glTexCoord2f( (src.x + src.w) / this->width , src.y / this->height );
		glVertex2f( dest.x + dest.w, dest.y );

		glTexCoord2f( (src.x + src.w) / this->width, (src.y + src.h) / this->height );
		glVertex2f( dest.x + dest.w, dest.y + dest.h );

		glTexCoord2f( src.x / this->width, (src.y + src.h) / this->height );
		glVertex2f( dest.x, dest.y + dest.h );

	glEnd();
	glDisable(GL_TEXTURE_2D);
}


bool Texture::initShaders(void) {
#ifdef _DEBUG 
	std::cout << "Initializing shaders ...\n";
#endif

	//Success flag
	bool success = true;

	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex source
	const GLchar* vertexShaderSource[] = {
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	// Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE) {
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
		success = false;
	}
	else {
		// Attach vertex shader to program
		glAttachShader(gProgramID, vertexShader);

		// Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Get fragment shader source
		const GLchar* fragmentShaderSource[] = {
			"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 0.0, 0.8, 0.8, 1.0 ); }"
		};

		// Set fragment source
		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

		// Compile fragment shader
		glCompileShader(fragmentShader);

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE) {
			printf("Unable to compile fragment shader %d!\n", fragmentShader);
			printShaderLog(fragmentShader);
			success = false;
		}
		else {
			// Attach fragment shader to program
			glAttachShader(gProgramID, fragmentShader);

			// Link program
			glLinkProgram(gProgramID);

			// Check for error
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE) {
				printf("Error linking program %d!\n", gProgramID);
				printProgramLog(gProgramID);
				success = false;
			}
			else {

				//Get vertex attribute location
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
				if (gVertexPos2DLocation == -1) {
					printf("LVertexPos2D is not a valid glsl program variable!\n");
					success = false;
				}
				else {
					// Initialize clear color
					glClearColor(0.f, 0.f, 0.f, 1.0f);

					// VBO data
					GLfloat vertexData[] = {
						-0.5f, -0.5f,
						0.5f, -0.5f,
						0.5f, 0.5f,
						-0.5f, 0.5f
					};

					// IVO data
					GLuint indexData[] = { 0, 1, 2, 3 };

					// Create VBO
					glGenBuffers(1, &gVBO);
					glBindBuffer(GL_ARRAY_BUFFER, gVBO);
					glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

					// Create IVO
					glGenBuffers(1, &gIBO);
					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
					glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

				}
			}
		}
	}

	// TODO: http://openil.sourceforge.net/download.php for images ??

	return success;
}


void Texture::printProgramLog(GLuint program) {
	//Make sure name is shader
	if (glIsProgram(program)) {
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0) {
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else {
		printf("Name %d is not a program\n", program);
	}
}


void Texture::printShaderLog(GLuint shader) {
	//Make sure name is shader
	if (glIsShader(shader)) {
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else {
		printf("Name %d is not a shader\n", shader);
	}
}

