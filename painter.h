#ifndef PAINTER_H_INCLUDED
#define PAINTER_H_INCLUDED

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 800

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

const SDL_Color DEFAULT_COLOR = BLACK_COLOR;

class Painter
{
    float x;
    float y;
    float angle;
    int width = SCREEN_WIDTH;
    int height = SCREEN_HEIGHT;
    SDL_Color color;
    SDL_Renderer* renderer;
public:
    Painter(SDL_Window* window, SDL_Renderer* renderer);

    void setColor(SDL_Color color);
    SDL_Color getColor() const { return color; }
    void clearWithBgColor(SDL_Color color);

    void setPosition(float x, float y);

    SDL_Texture* loadTexture( std::string path );
    bool createImage( SDL_Texture* texture );
    void showResult(int x);
    void showImage(int a, int b );
    void showSence1();
    void showSence2();
    std::string toString(int x);
    bool createImageWithRect( SDL_Texture* texture, SDL_Rect& rect1, SDL_Rect& rect2);

};

#endif // PAINTER_H_INCLUDED
