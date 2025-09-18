#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring> // memset
#include <SDL.h>
#include "Graphics.h"
#include "Painter.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
Graphics canvas;
SDL_Texture* texture = NULL;

bool visit[100], image_index, image_dir, res;

int main(int argc, char** argv) {
    std::cout << "Have " << argc << " arguments:" << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }

    // Seed RNG
    std::srand(std::time(nullptr));

    // Init SDL
    canvas.initSDL(window, renderer);
    Painter painter(window, renderer);

    // Helper: check if window is still open by polling events
    auto windowStillOpen = []() -> bool {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) return false;
        }
        return true;
    };

    // Scene 1
    texture = painter.loadTexture("image/scene1.png");
    painter.clearWithBgColor(WHITE_COLOR);
    painter.createImage(texture);
    SDL_RenderPresent(renderer);

    // Wait for input or window close
    if (!canvas.havePressed()) {
        if (texture) SDL_DestroyTexture(texture);
        canvas.quitSDL(window, renderer);
        return 0;
    }

    // Scene 2
    if (texture) { SDL_DestroyTexture(texture); texture = nullptr; }
    painter.showSence2();
    /*
    texture = painter.loadTexture("image/h3.bmp");
    #painter.clearWithBgColor(WHITE_COLOR);
    #painter.createImage(texture);
    #SDL_RenderPresent(renderer);*/

    // Wait for input or window close
    if (!canvas.havePressed()) {
        if (texture) SDL_DestroyTexture(texture);
        canvas.quitSDL(window, renderer);
        return 0;
    }

    bool running = true;
    int point = 0;

    for (int level = 1; running && level <= 15; level++) {
        std::memset(visit, 0, sizeof(visit));
        int result = -1;

        for (int i = 1; running && i <= 12; i++) {
            int image_index = std::rand() % 15 + 1;
            std::cout << image_index << std::endl;
            image_dir = 1;

            // Show current image
            painter.showImage(image_dir, image_index);

            // Replace fixed delay with a loop that can detect window close and user input
            Uint32 start = SDL_GetTicks();
            bool inputCaptured = false;
            while (running && (SDL_GetTicks() - start < 1000)) {
                SDL_Event e;
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) { running = false; break; }
                    if (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN) {
                        result = visit[image_index] ? 1 : 0;
                        if (result) point++;
                        cout << "Round: " << level << " " << "Point: " << point << endl;
                        inputCaptured = true;
                        break;
                    }
                }
                if (!running || inputCaptured) break;
                SDL_Delay(10);
            }
            if (!running) break;

            if (!inputCaptured) {
                // No input during the display window: update visit or mark as repeated (loss)
                if (visit[image_index]) {
                    result = 0; // repeated -> loss
                } else {
                    visit[image_index] = 1;
                }
            }

            if (result != -1) {
                painter.showResult(result);
                // Wait for input to continue, but handle window close
                if (!canvas.havePressed()) {
                    running = false;
                }
                break;
            }
        }
    }

    if (running) {
        // Final wait; also exits if window is closed
        canvas.waitUntilKeyPressedToCloseWindow();
    }

    if (texture) SDL_DestroyTexture(texture);
    canvas.quitSDL(window, renderer);
    return 0;
}