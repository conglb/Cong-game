#include <cmath>
#include <cstdlib>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

#include "Painter.h"

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 800
#define IMAGE_HEIGHT 512
#define IMAGE_WIDTH 512
#define IMAGE_NEW_WIDTH 400
#define IMAGE_NEW_HEIGHT 400

using namespace std;

Painter::Painter(SDL_Window* window, SDL_Renderer* renderer_)
    : renderer(renderer_)
{
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0)
        SDL_GetWindowSize(window, &width, &height);
    setPosition(0, 0);
    setColor(WHITE_COLOR);
    clearWithBgColor(BLUE_COLOR);
}

void Painter::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Painter::setColor(SDL_Color color)
{
    this->color = color;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 0);
}

void Painter::clearWithBgColor(SDL_Color bgColor)
{
    SDL_Color curColor = color;
    setColor(bgColor);
    SDL_RenderClear(renderer);
    setColor(curColor);
}

string Painter::toString(int x)
{
    string res = "";
    while (x) {
        res = char(x % 10 + '0') + res;
        x /= 10;
    }
    return res;
}

SDL_Texture* Painter::loadTexture( string path )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

bool Painter::createImage( SDL_Texture* texture )
{
    if( texture == NULL ) return false;
    SDL_RenderCopy( renderer, texture, NULL, NULL );
    return true;
}

bool Painter::createImageWithRect( SDL_Texture* texture, SDL_Rect& rect1, SDL_Rect& rect2)
{
    if( texture == NULL ) return 0;
    SDL_RenderCopy( renderer, texture, &rect1, &rect2);
    return 1;
}

void Painter::showSence1()
{
    SDL_Texture* texture = loadTexture("image/BACK.png");
    clearWithBgColor(WHITE_COLOR);
    createImage(texture);
    SDL_RenderPresent(renderer);
}

void Painter::showSence2()
{
    SDL_Texture* texture;
    texture = loadTexture("image/h3.bmp");
    SDL_Rect rect1;
    SDL_Rect rect2;
    rect1.x = 0;
    rect1.y = 0;
    rect1.h = 110;
    rect1.w = 627;
    rect2.x = SCREEN_WIDTH/2 - 600/2;
    rect2.y = SCREEN_HEIGHT/2 - 200/2;
    rect2.h = 200;
    rect2.w = 600;
    clearWithBgColor(WHITE_COLOR);
    createImageWithRect(texture, rect1, rect2);
    SDL_RenderPresent(renderer);
}

void Painter::showImage(int a, int b )
{
    SDL_Texture* texture;
    string dir = toString(a);
    string file = toString(b);
    texture = loadTexture("image/" + dir + "/" + file + ".png");
    SDL_Rect rect1;
    SDL_Rect rect2;
    rect1.x = 0;
    rect1.y = 0;
    rect1.h = IMAGE_HEIGHT;
    rect1.w = IMAGE_WIDTH;
    rect2.x = SCREEN_WIDTH/2 - IMAGE_NEW_WIDTH/2;
    rect2.y = SCREEN_HEIGHT/2 - IMAGE_NEW_HEIGHT/2;
    rect2.h = IMAGE_NEW_HEIGHT;
    rect2.w = IMAGE_NEW_WIDTH;
    clearWithBgColor(WHITE_COLOR);
    createImageWithRect(texture, rect1, rect2);
    SDL_RenderPresent(renderer);
    cout << "SHOWING IMAGE "<<file<<endl;
}

void Painter::showResult(int x)
{
    switch (x) {
    case 1 :
        SDL_Texture* texture;
        texture = loadTexture("image/win.bmp");
        clearWithBgColor(WHITE_COLOR);
        createImage(texture);
        SDL_RenderPresent(renderer);
        cout << "SHOWING IMAGE WIN"<<endl;
        break;
    default :
        SDL_Texture* texture2;
        texture2 = loadTexture("image/loss.bmp");
        clearWithBgColor(WHITE_COLOR);
        createImage(texture2);
        SDL_RenderPresent(renderer);
        cout << "SHOWING IMAGE LOSS"<<endl;
    }
}
