#include "ExplosionObject.hpp"

ExplosionObject::ExplosionObject()
{
    frame_ = 0;
}
ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::set_clip()
{
    Clip_[0].x = 0;
    Clip_[0].y = 0;
    Clip_[0].w = EXP_WIDTH;
    Clip_[0].h = EXP_HEIGHT;

    Clip_[1].x = EXP_WIDTH;
    Clip_[1].y = 0;
    Clip_[1].w = EXP_WIDTH;
    Clip_[1].h = EXP_HEIGHT;

    Clip_[2].x = 2*EXP_WIDTH;
    Clip_[2].y = 0;
    Clip_[2].w = EXP_WIDTH;
    Clip_[2].h = EXP_HEIGHT;

    Clip_[3].x = 3*EXP_WIDTH;
    Clip_[3].y = 0;
    Clip_[3].w = EXP_WIDTH;
    Clip_[3].h = EXP_HEIGHT;

    Clip_[4].x = 4*EXP_WIDTH;
    Clip_[4].y = 0;
    Clip_[4].w = EXP_WIDTH;
    Clip_[4].h = EXP_HEIGHT;

    Clip_[5].x = 5*EXP_WIDTH;
    Clip_[5].y = 0;
    Clip_[5].w = EXP_WIDTH;
    Clip_[5].h = EXP_HEIGHT;

    Clip_[6].x = 6*EXP_WIDTH;
    Clip_[6].y = 0;
    Clip_[6].w = EXP_WIDTH;
    Clip_[6].h = EXP_HEIGHT;

    Clip_[7].x = 7*EXP_WIDTH;
    Clip_[7].y = 0;
    Clip_[7].w = EXP_WIDTH;
    Clip_[7].h = EXP_HEIGHT;

    Clip_[8].x = 8*EXP_WIDTH;
    Clip_[8].y = 0;
    Clip_[8].w = EXP_WIDTH;
    Clip_[8].h = EXP_HEIGHT;

    Clip_[9].x = 9*EXP_WIDTH;
    Clip_[9].y = 0;
    Clip_[9].w = EXP_WIDTH;
    Clip_[9].h = EXP_HEIGHT;
    
    Clip_[10].x = 10*EXP_WIDTH;
    Clip_[10].y = 0;
    Clip_[10].w = EXP_WIDTH;
    Clip_[10].h = EXP_HEIGHT;

}
void ExplosionObject::RenderEx(SDL_Renderer* des, SDL_Rect* current_clip){
    current_clip = &Clip_[frame_];
    SDL_Rect renderquad = {rect_.x, rect_.y, EXP_WIDTH, EXP_HEIGHT};
    SDL_RenderCopy(des, this->p_object_,current_clip, &renderquad);
}