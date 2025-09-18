#include <cstring>
#include <cstdlib>
#include <ctime>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.h"
#include "Painter.h"
#include <SDL_mixer.h>

using namespace std;

Game::Game( SDL_Window* window, SDL_Renderer* renderer, Window& canvas, Painter& painter ) {
    srand(time(NULL));

    // Sence1 and Sence2's sound
    Mix_Chunk* sence2 = NULL;
    sence2 = Mix_LoadWAV( "sound/sence2.ogx" );
    if (sence2 == NULL)
	{
		cout << Mix_GetError();
	}
    if( Mix_PlayChannel( -1, sence2, -1 ) == -1 )
    {
        return;
    }

    // Sence1 here
    painter.showSence1();
    if (canvas.havePressed()) cout << "Click on sence 1"<<endl; else canvas.quitSDL(window, renderer);

    // Sence2 here
    painter.showSence2();
    if (canvas.havePressed()) cout << "Click on sence 2"<<endl; else canvas.quitSDL(window, renderer);

    Mix_Pause( -1 );
    Mix_Chunk* music = NULL , *winsound = NULL , *losssound = NULL ;
    music = Mix_LoadWAV( "sound/show.wav" );
    winsound = Mix_LoadWAV( "sound/win.wav" );
    losssound = Mix_LoadWAV( "sound/loss.mp3" );
    if (music == NULL || winsound == NULL || losssound == NULL)
	{
		cout << Mix_GetError();
	}
    // Slideshow here
    bool visit[22];
    for (int level=1; level<=15; level++) {
        memset(visit,0,sizeof(visit));
        int res = -1;
        for (int i=1; i<=12; i++) {
            int image_index = rand() % 15 + 1;
            //int image_index = rand() % 15 + 1;
            int image_dir = 1;
            painter.showImage(image_dir, image_index);
            if( Mix_PlayChannel( -1, music, 0 ) == -1 )
            {
                return;
            }
            canvas.haveClick(visit , image_index, res);
            if (res!=-1) {
                    if (res)
                    {
                        if( Mix_PlayChannel( -1, winsound, 0 ) == -1 )
                        {
                            return;
                        }
                    }
                    else
                    {
                        if( Mix_PlayChannel( -1, losssound, 0 ) == -1 )
                        {
                            return;
                        }
                    }
                    painter.showResult(res);
                    if (canvas.havePressed()) cout << "Click on sence 3"<<endl; else canvas.quitSDL(window, renderer);
                    break;
            }
            else
            if (visit[image_index]) {
                res = 0;
                if( Mix_PlayChannel( -1, losssound, 0 ) == -1 )
                {
                    return;
                }
                painter.showResult(res);
                if (canvas.havePressed()) cout << "Click on sence 3"<<endl; else canvas.quitSDL(window, renderer);
                break;
            }
                else visit[image_index] = 1;
        }
    }

}
