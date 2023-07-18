/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init(); // window -> surface

//Loads media
bool loadMedia(); // surface -> load image

//Frees media and shuts down SDL
void close();

// Notice that these are POINTERS to SDL surfaces. 
// The reason is that 
// 1) we'll be dynamically allocating memory to load images and 
// 2) it's better to reference an image by memory location. 
// Imagine you had a game with a brick wall that consisted of the same brick image being rendered multiple times (like Super Mario Bros). 
// It's wasteful to have dozens of copies of the image in memory when you can have one copy of the image and render it over and over again.

// Also, always remember to initialize your pointers. We set them to NULL immediately when declaring them.

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gBackground = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load splash image
	gBackground = SDL_LoadBMP( "Pink_bkground.bmp" );
	if( gBackground == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "Pink_bkground.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

void close()
{
	//Deallocate surface
	SDL_FreeSurface( gBackground);
	gBackground = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( init() == false )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( loadMedia() == false )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Apply the image
			SDL_BlitSurface( gBackground, NULL, gScreenSurface, NULL );
			
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );

            //Hack to get window to stay up
            SDL_Event e; 
			bool quit = false; 
			while( quit == false ){ 
				while( SDL_PollEvent( &e ) )
				{ if( e.type == SDL_QUIT ) 
						quit = true; } }
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
