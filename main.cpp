#include <iostream>
#include <SDL.h>
#include "graphics.h"


using namespace std;

int main(int argc, char** argv) {
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    SDL_Window* window;
    SDL_Renderer* renderer;
    graphics Screen;
    Screen.initSDL(window, renderer);

    // Drawing code here
    // use SDL_RenderPresent(renderer) to show it

	Screen.waitUntilKeyPressed();
    Screen.quitSDL(window, renderer);
}
