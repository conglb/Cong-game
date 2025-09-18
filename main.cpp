#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring> // memset
#include <SDL.h>
#include "graphics.h"
#include "painter.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
graphics canvas;
SDL_Texture* texture = NULL;

bool visit[100], image_index, image_dir, res;

int main(int argc, char** argv) {
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
    srand(time(NULL));
    canvas.initSDL(window, renderer);
    Painter painter(window, renderer);

    // Drawing code here
    // use SDL_RenderPresent(renderer) to show it

    texture = painter.loadTexture("image/h2.png");
    painter.clearWithBgColor(WHITE_COLOR);
    painter.createImage(texture);
    SDL_RenderPresent(renderer);

    if (canvas.havePressed()) cout << "Click on sence 1"<<endl; else canvas.quitSDL(window, renderer);

    texture = painter.loadTexture("image/h3.bmp");
    painter.clearWithBgColor(WHITE_COLOR);
    painter.createImage(texture);
    SDL_RenderPresent(renderer);

    if (canvas.havePressed()) cout << "Click on sence 2"<<endl; else canvas.quitSDL(window, renderer);
    for (int level=1; level<=2; level++) {
        memset(visit,0,sizeof(visit));
        int res = -1;
        for (int i=1; i<=12; i++) {
            int image_index = rand() % 15 + 1;
            //int a = rand() % 15 + 1;
            cout << image_index << endl;
            image_dir = 1;
            painter.showImage(image_dir, image_index);
            SDL_Delay(1000);
            SDL_Event e;
            if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (!visit[image_index]) res = 0; else res = 1;
                cout << "dlkfjsldkfjsl;dkjf"<<res;
            }
            else if (visit[image_index]) res = 0; else visit[image_index] = 1;
            if (res!=-1) {
                painter.showResult(res);
                if (canvas.havePressed()) cout << "Click on sence 3"<<endl; else canvas.quitSDL(window, renderer);
                break;
            }
        }
    }

    /*
    SDL_Surface *imageSurface = NULL;
    SDL_Surface *windowSurface = NULL;


    windowSurface = SDL_GetWindowSurface( window );

    SDL_Event windowEvent;

    imageSurface = SDL_LoadBMP( "h3.bmp" );
    if( imageSurface == NULL )
    {
        std::cout << "SDL could not load image! SDL Error: " << SDL_GetError( ) << std::endl;
    }

    while ( true )
    {
        if ( SDL_PollEvent( &windowEvent ) )
        {
            if ( SDL_QUIT == windowEvent.type )
            {
                break;
            }
        }

        SDL_BlitSurface( imageSurface, NULL, windowSurface, NULL );

        //Update the surface
        SDL_UpdateWindowSurface( window );
    }

    SDL_FreeSurface( imageSurface );
    SDL_FreeSurface( windowSurface );

    imageSurface = NULL;
    windowSurface = NULL;
    */

    canvas.waitUntilKeyPressedToCloseWindow();


    SDL_DestroyTexture(texture);
    canvas.quitSDL(window, renderer);
}
