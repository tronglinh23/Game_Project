#pragma once
#include "BaseObject.hpp"
#include "Common_function.hpp"

const int EXP_WIDTH = 165;
const int EXP_HEIGHT = 165;

class ExplosionObject:public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();
    void set_clip();
    void set_frame(const int& fr) {frame_ = fr;}
    void RenderEx(SDL_Renderer* des,const SDL_Rect* CLIP);

private:
    int frame_;
    SDL_Rect Clip_[4];
};