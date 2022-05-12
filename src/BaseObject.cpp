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
        else{
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

bool BaseObject::CheckCollision(const SDL_Rect &object1 ,const SDL_Rect &object2){
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;
    
    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;
    
    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
        return true;
        }
    }
    
    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
        return true;
        }
    }
    
    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
        return true;
        }
    }
    
    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
        return true;
        }
    }
    
    // Case 2: size object 1 > size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
        return true;
        }
    }
    
    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
        return true;
        }
    }
    
    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
        return true;
        }
    }
    
    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
        return true;
        }
    }
    
    // Case 3: size object 1 == size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }
    return false;
}