#pragma once
#include "BaseObject.hpp"
#include "Common_function.hpp"
#include "BulletObject.hpp"
#include <vector>
#include <time.h>
#define WIDTH_MAIN_OBJECT 110
#define HEIGHT_MAIN_OBJECT 50
const int Speed_deafault_mainobject_x =  WIDTH_MAIN_OBJECT/15;
const int Speed_deafault_mainobject_Y = HEIGHT_MAIN_OBJECT/7;
class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bulletsound[2], Mix_Music* gMusic_);
    void HandMove();
    void SetbulletList(std::vector<BulletObject*> bullet_list, const int& stt) {p_bullet_list_[stt] = bullet_list;}
    std::vector<BulletObject*> GetbulletList(const int& stt) const {return p_bullet_list_[stt];}
    
    void Display_bullet(SDL_Renderer* des);
    void Removebullet(const int& stt,const int& x);
    void Set_Amount_Bullet(const int& amount_bullet){amount_bullet_ = amount_bullet;}
    void Upgrade_speed_mainobject(const int& x){x_step += x , y_step += x;}
    void Set_x_step_y_step(const int& x_st, const int& y_st){x_step = x_st, y_step = y_st;}
private:
    int x_step;
    int y_step;
    float x_val_;
    float y_val_;
    int amount_bullet_;
    std::vector<BulletObject*> p_bullet_list_[max_bullet_main];
};
