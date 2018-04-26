#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream>
#include <SDL.h>

class Window {
public:
    void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
    void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
    void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
    void waitUntilKeyPressedToCloseWindow();
    bool havePressed();
    void haveClick(bool visit[], int image_index, int& res);
private:

};




#endif // WINDOW_H_INCLUDED
