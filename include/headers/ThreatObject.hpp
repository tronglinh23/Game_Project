#pragma once
#include "Common_function.hpp"
#include "BaseObject.hpp"
#include "BulletObject.hpp"
#include <vector>
#define WIDTH_THREAT 100
#define HEIGHT_THREAT 50
#define WIDTH_THREAT_TANK 125
#define HEIGHT_THREAT_TANK 170
class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();
    void init(BulletObject * p_bullet, SDL_Renderer* screen);
    void Upgrade_speed_Bullet();
    void Makebullet(SDL_Renderer* des, const int& x_limit , const int& y_limit); // KIEM TRA KHI NAO DEN CUOI MAP THI GET_IS_MOVE = FALSE;
    void HandleMove(const int& x_border, const int& y_border);
    void HandleInputAction(SDL_Event events);
    void Set_x_val(const int& val) {x_val_ = val;}
    int Get_x_val(){return x_val_;}
    void Set_y_val(const int& val) {y_val_ = val;}
    int Get_y_val(){return y_val_;}
    std::vector<BulletObject*> Get_bullet_list() {return p_bullet_list_;}
    void ResetThreat(const int& xborder, const int& life);
    void Resetbullet(BulletObject* p_bullet);
    void Removebullet_Threat(const int& k);
    void Setlife_(const int& amount_life) {life_ = amount_life;}
    int Getlife_(){return life_;}
    void Decrease_Life();
private:
    int x_val_;
    int y_val_;
    std::vector <BulletObject*> p_bullet_list_;
    int life_;
};