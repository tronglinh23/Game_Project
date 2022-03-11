#include "BaseObject.hpp"
#include <iostream>

BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}
BaseObject::~BaseObject()
{
    Free();
}

bool BaseObject::LoadIMG(std::string path, SDL_Renderer* screen)
{
    SDL_Texture* new_texture = NULL;
    SDL_Surface* Load_Surface = IMG_Load(path.c_str());
    if(Load_Surface != NULL){
        // transparent background
        SDL_SetColorKey(Load_Surface,SDL_TRUE, SDL_MapRGB(Load_Surface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        new_texture = SDL_CreateTextureFromSurface(screen, Load_Surface);
        if(new_texture != NULL){
            rect_.w = Load_Surface->w;
            rect_.h = Load_Surface->h;
        }
        if(new_texture == NULL){
            std::cout << "Unable to create texture from " << path << " SDL ERROR : " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(Load_Surface);
    }
    else{
        std::cout << "Unable to load image " << path << " SDL_image ERROR: " << IMG_GetError() << std::endl;
    }
        
    p_object_ = new_texture;
    return p_object_ != NULL; //
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip){
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopy(des, p_object_,clip, &renderquad);
}


void BaseObject::Free(){
    if(p_object_ != NULL){
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}

