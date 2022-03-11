#pragma once
#include "BaseObject.hpp"
#include "Common_function.hpp"
#include "AmoObject.hpp"
#include <vector>
#include <time.h>
#define WIDTH_MAIN_OBJECT 77
#define HEIGHT_MAIN_OBJECT 52
class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void HandMove();
    void SetAmoList(std::vector<AmoObject*> amo_list) {p_amo_list_ = amo_list;}
    std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}
private:
    float x_val_;
    float y_val_;
    
    std::vector<AmoObject*> p_amo_list_;
};
