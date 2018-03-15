#include "graphics.h"
#include <iostream>

#define GRID_SIZE 25
#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 800

using namespace std;

const string WINDOW_TITLE = "Cong - A Simple Game";

void graphics::logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void graphics::initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr)
        logSDLError(std::cout, "CreateWindow", true);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //SDL_Renderer *renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr)
        logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void graphics::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void graphics::waitUntilKeyPressedToCloseWindow()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        //SDL_Delay(100);
    }
}

bool graphics::havePressed() {
    SDL_Event e;
    while (1)
    {
        if ( SDL_WaitEvent(&e)!=0 )
        if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) return 1;
        else if (e.type == SDL_QUIT) return 0;
    }
}
/*
//The button
//class Button {
//    private:
    //The attributes of the button
    Button::SDL_Rect box;
    //The part of the button sprite sheet that will be shown
    Button::SDL_Rect* clip;
//public:
    //Initialize the variables
    Button::Button( int x, int y, int w, int h );
    //Handles events and set the button's sprite region
    Button::void handle_events();
    //Shows the button on the screen
    Button::void show();
//};
*/

button::button( int x, int y, int w, int h ) {
    //Set the button's attributes
        box.x = x;
        box.y = y;
        box.w = w;
        box.h = h;
        //Set the default sprite
}
