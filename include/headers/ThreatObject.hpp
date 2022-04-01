#pragma once
#include "Common_function.hpp"
#include "BaseObject.hpp"
#include "BulletObject.hpp"
#include <vector>
#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33
class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();
    void init(BulletObject * p_amo, SDL_Renderer* screen);
    void MakeAmo(SDL_Renderer* des, const int& x_limit , const int& y_limit); // KIEM TRA KHI NAO DEN CUOI MAP THI GET_IS_MOVE = FALSE;
    void HandleMove(const int& x_border, const int& y_border);
    void HandleInputAction(SDL_Event events);
    void Set_x_val(const int& val) {x_val_ = val;}
    int Get_x_val(){return x_val_;}
    void Set_y_val(const int& val) {y_val_ = val;}
    int Get_y_val(){return y_val_;}
    std::vector<BulletObject*> Get_Amo_list() {return p_amo_list_;}
    void ResetThreat(const int& xborder);
    void ResetAmo(BulletObject* p_amo);
    void RemoveAmo_Threat(const int& k);
private:
    int x_val_;
    int y_val_;
    std::vector <BulletObject*> p_amo_list_;
};