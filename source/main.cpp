#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "config_loader.hpp"

int main(int argc, char **argv)
{
    int windowWidth, windowHeight;

    // initialize sdl
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
	return 1;
    }

    // make the window
    SDL_Window *window = SDL_CreateWindow("super GAMING menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 3, 3, SDL_WINDOW_BORDERLESS);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
	return 1;
    }

    // make the renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
	return 1;
    }

    // enable transparency
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // intiialize text stuff
    if (TTF_Init() != 0) {
        std::cerr << "Failed to initialize SDL_ttf: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // open liberation sans
    // TODO get font from config / use default font if not in config
    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/liberation-sans/LiberationSans-Regular.ttf", 24);
    if (!font) {
        std::cerr << "Failed to open font: " << TTF_GetError() << std::endl;
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // initialize image support for every image type imaginable
    int imgInitFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_AVIF | IMG_INIT_JXL;
    if (!(IMG_Init(imgInitFlags) & imgInitFlags)) {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        TTF_CloseFont(font);
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    std::string configFileName;

    // if there's an argument then try using that
    if (argc >= 2) {
        configFileName = argv[1];
    } else {
        // TODO cross-platform
        configFileName = "~/.config/super-GAMING-menu/config.json";
    }

    Menu menu = loadConfig(configFileName, font, renderer, &windowWidth, &windowHeight);

    SDL_SetWindowSize(window, windowWidth, windowHeight);

    SDL_Rect clearRect = {0, 0, windowWidth, windowHeight};

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_KEYDOWN) {
                menu.onKeyDown(event.key.keysym.sym);
            } else if (event.type == SDL_MOUSEMOTION) {
                menu.onMouseMove(event.motion.x, event.motion.y);
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                menu.onMouseDown(event.button.button);
            }
        }

        if (menu.shouldQuit()) {
            running = false;
            break;
        }

        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 12, 12, 34, 255);
        SDL_RenderFillRect(renderer, &clearRect);

        menu.draw(renderer, windowWidth, windowHeight);

        SDL_RenderPresent(renderer);
    }

    IMG_Quit();

    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
