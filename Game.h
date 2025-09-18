#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include "Painter.h"
#include "Window.h"

class Game
{
    public:
        Game( SDL_Window* window, SDL_Renderer* renderer, Window& canvas, Painter& painter );

};
#endif // GAME_H_INCLUDED
