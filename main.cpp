#include <iostream>
#include <SDL.h>
#include "Window.h"
#include "Painter.h"
#include "Game.h"
#include "SDL_mixer.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
Window canvas;
SDL_Texture* texture = NULL;

bool visit[100], image_index, image_dir, res;

int main(int argc, char** argv) {
    /*
    cout << "Have " << argc << " arguments:" << endl;
    for (int i = 0; i < argc; ++i) {
        cout << argv[i] << endl;
    }
    */

    canvas.initSDL(window, renderer);
    Painter painter(window, renderer);

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }



    //Game here
    Game game(window, renderer, canvas, painter);

    canvas.waitUntilKeyPressedToCloseWindow();
    SDL_DestroyTexture(texture);
    Mix_CloseAudio();
    canvas.quitSDL(window, renderer);
}
