#pragma once
#include "Common_function.hpp"
#include "BaseObject.hpp"
#include <SDL2/SDL_ttf.h>
#include <string>
class TextObject : public BaseObject
{
public:
    TextObject();
    ~TextObject();
    void SetText(const std::string& text){text_ = text;}
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void loadFromRenderedText(TTF_Font* font, SDL_Renderer* des);
    void RenderText(SDL_Renderer* screen, int xpos, int ypos, 
                    SDL_Rect* clip = NULL,double angle = 0.0,
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    void Free();
    int GetWidth() const {return width_;}
    int GetHeight() const {return height_;}
    std::string GetText() const {return text_;}
private:
    std::string text_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
};