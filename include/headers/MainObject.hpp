#pragma once
#include "BaseObject.hpp"
#include "Common_function.hpp"
#include "BulletObject.hpp"
#include <vector>
#include <time.h>
#define WIDTH_MAIN_OBJECT 70
#define HEIGHT_MAIN_OBJECT 60

const int x_step = WIDTH_MAIN_OBJECT/7;
const int y_step = HEIGHT_MAIN_OBJECT/6;
const int Under_Limit_Threat = 100;
class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bulletsound[2], Mix_Music* gMusic_);
    void HandMove();
    void SetAmoList(std::vector<BulletObject*> amo_list, const int& stt) {p_amo_list_[stt] = amo_list;}
    std::vector<BulletObject*> GetAmoList(const int& stt) const {return p_amo_list_[stt];}
    
    void Display_Amo(SDL_Renderer* des);
    void RemoveAmo(const int& stt,const int& x);
    void Set_Amount_Bullet(const int& amount_bullet){amount_bullet_ = amount_bullet;}
private:
    float x_val_;
    float y_val_;
    int amount_bullet_;
    std::vector<BulletObject*> p_amo_list_[3];
};
