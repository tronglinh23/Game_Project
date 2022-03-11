#pragma once
#include "Common_function.hpp"

// class BaseObject viet ra de su dung chung cung cac class khac , lap trinh huong doi tuong
class BaseObject
{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x , const int& y){rect_.x = x, rect_.y = y;} // vi tri muon hien thi tren cua so
    void setSize(const int& w , const int& h){rect_.w = w, rect_.h = h;}
    SDL_Rect GetRect() const {return rect_;} 
    SDL_Texture* GetTexture() const {return p_object_;}

    bool LoadIMG(std::string path, SDL_Renderer* screen); // loadimage de ve ra 
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL); // day len render 
    void Free();
protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
    
};