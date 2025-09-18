//
// Created by conglb on 18.09.25.
//

#ifndef CONG_GAME_GRAPHICS_H
#define CONG_GAME_GRAPHICS_H

#include <SDL.h>
#include <string>
#include <iosfwd>

using namespace std;

class Graphics {
public:
    // Log an SDL error message to the provided output stream.
    // If fatal is true, the function will call SDL_Quit() and terminate the process.
    void logSDLError(std::ostream& os, const std::string& msg, bool fatal = false);

    // Initialize SDL, create a window and a renderer.
    // On failure, this function terminates the process after logging the error.
    void initSDL(SDL_Window*& window, SDL_Renderer*& renderer);

    // Destroy the renderer and window, then quit SDL.
    void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

    // Block until a key is pressed or the window is closed.
    void waitUntilKeyPressedToCloseWindow();

    // Wait for either a key press or mouse click; return true if input occurred,
    // false if a quit event was received.
    bool havePressed();

    // Poll briefly for a key/mouse input and set 'res':
    // - res = 1 if visit[image_index] is true
    // - res = 0 if visit[image_index] is false
    // Returns immediately after detecting an input or when the short polling window ends.
    void haveClick(bool visit[], int image_index, int& res);
};


#endif //CONG_GAME_GRAPHICS_H