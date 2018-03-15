#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <iostream>
#include <SDL.h>

class graphics {
public:
    void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
    void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
    void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
    void waitUntilKeyPressedToCloseWindow();
    bool havePressed();
private:

};

class button {
private:
    SDL_Rect box;
    SDL_Rect* clip;
public:
    button( int x, int y, int w, int h );
    void handle_events();
    void show();
};


#endif // GRAPHICS_H_INCLUDED
