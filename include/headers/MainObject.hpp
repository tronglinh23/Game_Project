#pragma once
#include "BaseObject.hpp"
#include "Common_function.hpp"
#include "BulletObject.hpp"
#include <vector>
#include <time.h>
#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52

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
    void SetAmoList(std::vector<BulletObject*> amo_list) {p_amo_list_ = amo_list;}
    std::vector<BulletObject*> GetAmoList() const {return p_amo_list_;}
    
    void Display_Amo(SDL_Renderer* des);
    void RemoveAmo(const int& x);
private:
    float x_val_;
    float y_val_;
    
    std::vector<BulletObject*> p_amo_list_;
};
