#include "ExplosionObject.hpp"

ExplosionObject::ExplosionObject()
{

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
}
void ExplosionObject::RenderEx(SDL_Renderer* des,const SDL_Rect* CLIP){
    SDL_Rect renderquad = {rect_.x, rect_.y, EXP_WIDTH, EXP_HEIGHT};
    SDL_RenderCopy(des, p_object_,&Clip_[frame_], &renderquad);
}