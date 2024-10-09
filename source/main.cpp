#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include "gaming_launcher_lutris.hpp"
#include "gaming_types.hpp"
#include "separator_item.hpp"
#include "blank_item.hpp"
#include "launcher_item.hpp"
#include "menu.hpp"

int main(void)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
	return 1;
    }

    SDL_Window *window = SDL_CreateWindow("super GAMING menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 460, SDL_WINDOW_BORDERLESS);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
	return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
	return 1;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (TTF_Init() != 0) {
        std::cerr << "Failed to initialize SDL_ttf: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/liberation-sans/LiberationSans-Regular.ttf", 24);
    if (!font) {
        std::cerr << "Failed to open font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    GamingLauncherLutris th18Launcher("touhou-18-unconnected-marketeers");

    BlankItem blank;
    SeparatorMenuItem testSeparator({255, 0, 0, 255}, {255, 0, 0, 255}, 1, 3, 50, 50, GamingAlign::Left, GamingAlign::Right, 10, 30);
    LauncherMenuItem testLauncher({255, 255, 255, 255}, {50, 50, 255, 255}, "Launch Firefox", "Launch Firefox!!", GamingAlign::Left, GamingAlign::Left, 10, 15, font, renderer, &th18Launcher);

    Menu menu({&blank, &testSeparator, &testLauncher});

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                } else {
                    menu.onKeyDown(event.key.keysym.sym);
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                menu.onMouseMove(event.motion.x, event.motion.y);
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                menu.onMouseDown(event.button.button);
            }
        }

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 12, 12, 34, 255);
        SDL_Rect clearRect = {0, 0, 500, 460};
        SDL_RenderFillRect(renderer, &clearRect);

        menu.draw(renderer);

        SDL_RenderPresent(renderer);
    }

    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
