#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Entity.hpp"

class Renderwindow
{
public:
    Renderwindow(const char* p_title, int p_w, int p_h);
    void cleanup();
    SDL_Texture* LoadTexture(const char* file_path);
    void clear();
    void Render(Entity& platform);
    void display();
private:
    SDL_Window* window ;
    SDL_Renderer* renderer;
};
