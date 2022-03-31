#include "Text_object.hpp"

TextObject::TextObject(){
    rect_.x = 500;
    rect_.y = 10;
    text_color_.r = 0;
    text_color_.g = 0;
    text_color_.b = 0;
    texture_ = NULL;
    
}
TextObject::~TextObject(){

}

void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue){
    SDL_Color color =  {red,green,blue};
    text_color_ = color;
}

void TextObject::loadFromRenderedText(TTF_Font* font, SDL_Renderer* des){
    SDL_Surface* load_surface = TTF_RenderText_Solid(font,text_.c_str(),text_color_);
    if(load_surface == NULL)
    {
        std::cout << "Unable to render text surface! SDL_ttf Error: %s\n" << TTF_GetError();
    }
    else
    {
        //Create texture from surface pixels
        texture_ = SDL_CreateTextureFromSurface(des, load_surface);
        if(texture_ == NULL){
            std::cout << "Unable to create texture from rendered text! SDL Error: %s\n" << SDL_GetError();
        }
        else{
            width_ = load_surface->w;
            height_ = load_surface->h;
        }

    }
    SDL_FreeSurface(load_surface);
}
void TextObject::Free(){
    if(texture_!= NULL){
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void TextObject::RenderText(SDL_Renderer* screen, int xpos, int ypos, 
                    SDL_Rect* clip /*= NULL */, double angle /*= 0.0 */,
                    SDL_Point* center /*= NULL*/, SDL_RendererFlip flip /*= SDL_FLIP_NONE */)
{
    SDL_Rect renderquad = {xpos,ypos,width_,height_};
    if(clip != NULL){
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }
    SDL_RenderCopyEx(screen, texture_, clip, &renderquad, angle, center,flip); 
}