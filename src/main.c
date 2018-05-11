//BEGIN HEAD
//BEGIN DESCRIPTION

/* This is a small Sprite Animation Demo
 *
 */

/* DEFINED PROGRESS GOALS
 * Got the Sprite-Sheet
 * Need to know the
 * 	number of frames [4*2]
 * 	need single frame ratio:
 * 		identify Cheetah.png
 * 		512x252
 * 	time to be displayed [100 ms per frame]
 * 
 * Need a Texture a source rect and a dest rect
 * Need timing and source frame switching code
 * 
 */
//END   DESCRIPTION

//BEGIN INCLUDES
//system headers
#include <math.h>
//local headers
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define TZ_H	512/4
#define TZ_V	252/2
#define WHITE 	255,255,255,255
#define BLACK 	0,0,0,255
#define RED   	255,0,0,255
#define WW 	TZ_H * 2.5
#define WH 	TZ_V * 2.5
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=WW;
int wh=WH;

//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;

SDL_Texture    *cheetah		= NULL;
SDL_Rect 	cheetah_dst;
SDL_Rect 	cheetah_src;
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
float time_(void);
void assets_in	(void);
void assets_out	(void);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();
assets_in();

//BEGIN WINDOW
SDL_SetWindowPosition(Window,0,0);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "Sprite Animation");
SDL_ShowWindow(Window);
//END WINDOW
float currentTime = 0.0f;
float accumulator = 0.0f;
SDL_Event event;
int running = 1;
//END   INIT

//BEGIN MAIN LOOP
while(running){

	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running =0;
		}
		if(event.type == SDL_MOUSEMOTION){
			;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			if(event.button.button == SDL_BUTTON_RIGHT){
				;
			}
			if(event.button.button == SDL_BUTTON_MIDDLE){
				;
			}
			if(event.button.button==SDL_BUTTON_LEFT){
				;
			}
		}
		if(event.type == SDL_KEYDOWN ){
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
					running =0;
					break;

				case SDLK_r:
				case SDLK_BACKSPACE:
					break;

				case SDLK_p:	
				case SDLK_SPACE:
					break;
					
				default:
					break;
			}
		}
	}
	//END   EVENT LOOP
	float newTime = time_();
	float deltaTime = newTime - currentTime;
	currentTime = newTime;
	accumulator += deltaTime;
	if (accumulator>=0.1){
		cheetah_src.x+=TZ_H;
		
		if (cheetah_src.x>TZ_H*3){
			cheetah_src.x=0;
			if (cheetah_src.y==0)
				cheetah_src.y=TZ_V;
			else
				cheetah_src.y=0;
		}
		
		accumulator=0;
		
	}

	//BEGIN RENDERING
	SDL_SetRenderDrawColor	(Renderer, WHITE);
	SDL_RenderClear		(Renderer);
	SDL_RenderCopy		(Renderer, cheetah, &cheetah_src, &cheetah_dst);
	SDL_RenderPresent	(Renderer);
	//END   RENDERING
}
//END   MAIN LOOP

assets_out();
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void assets_in(void)
{
	
	//BEGIN CHEETAH
	temp_surface = IMG_Load("./assets/gfx/Cheetah.png");
	cheetah= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	cheetah_dst.w=TZ_H*2;
	cheetah_dst.h=TZ_V*2;
	cheetah_dst.x=ww/2-cheetah_dst.w/2;
	cheetah_dst.y=wh/2-cheetah_dst.h/2;
	
	cheetah_src.w=TZ_H;
	cheetah_src.h=TZ_V;
	cheetah_src.x=0;
	cheetah_src.y=0;
	//END 	CHEETAH
}

void assets_out(void)
{
	SDL_DestroyTexture(cheetah);
}
float time_(void)
{
	
	static Uint64 start = 0;
	static float frequency = 0;
	
	if (start==0){
		start	 = SDL_GetPerformanceCounter();
		frequency= (float)SDL_GetPerformanceFrequency();
		return 0.0f;
	}
	
	Uint64 counter = 0;
	counter=SDL_GetPerformanceCounter();
	return  (((float)counter - (float)start) /frequency);
	// 	real64 MSPerFrame = (((1000.0f * (real64)CounterElapsed) / (real64)PerCountFrequency));
}

//END   FUNCTIONS
