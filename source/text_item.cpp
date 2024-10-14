#include "text_item.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>

TextMenuItem::TextMenuItem(SDL_Color color, SDL_Color hoverColor, std::string text, std::string hoverText, GamingAlign align, GamingAlign hoverAlign, int padding, int hoverPadding, TTF_Font *font, SDL_Renderer *renderer) : align(align), hoverAlign(hoverAlign), padding(padding), hoverPadding(hoverPadding)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to create surface: " << TTF_GetError() << std::endl;
        // TODO any way to signify error so that the part that's loading can terminate?
    }

    mTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!mTexture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);

    SDL_Surface *hoverSurface = TTF_RenderText_Solid(font, hoverText.c_str(), hoverColor);
    if (!surface) {
        std::cerr << "Failed to create hover surface: " << TTF_GetError() << std::endl;
    }

    mHoverTexture = SDL_CreateTextureFromSurface(renderer, hoverSurface);
    if (!mHoverTexture) {
        std::cerr << "Failed to create hover texture from hover surface: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(hoverSurface);

    SDL_QueryTexture(mTexture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
    SDL_QueryTexture(mHoverTexture, nullptr, nullptr, &mHoverTextureWidth, &mHoverTextureHeight);
}

TextMenuItem::~TextMenuItem()
{
    SDL_DestroyTexture(mTexture);
    SDL_DestroyTexture(mHoverTexture);
}

void TextMenuItem::draw(SDL_Renderer *renderer, int y, int windowWidth, int windowHeight, bool isHovered)
{
    SDL_Texture *texture = isHovered ? mHoverTexture : mTexture;
    int textureWidth = isHovered ? mHoverTextureWidth : mTextureWidth;
    int textureHeight = isHovered ? mHoverTextureHeight : mTextureHeight;
    GamingAlign realAlign = isHovered ? hoverAlign : align;
    int realPadding = isHovered ? hoverPadding : padding;

    int x;
    switch (realAlign) {
    case GamingAlign::Left:
        x = realPadding;
        break;
    case GamingAlign::Center:
        x = (windowWidth / 2) - textureWidth / 2;
        break;
    case GamingAlign::Right:
        x = windowWidth - textureWidth - realPadding;
        break;
    }

    SDL_Rect destRect = {x, y, textureWidth, textureHeight};

    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}
