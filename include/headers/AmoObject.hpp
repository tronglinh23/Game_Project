#pragma once

#include "BaseObject.hpp"
#define WIDTH_LASER 35
#define HEIGHT_LASER 5

#define WIDTH_SPHERE 10
#define HEIGHT_SPHERE 10
class AmoObject : public BaseObject
{
public:
    enum AmmoType  // co 3 kieu loai dan de vao ham enum
    {
        NONE = 0,
        LASER = 1,
        SPHERE = 2
    };
    AmoObject();
    ~AmoObject();
    void HandleInputAction(SDL_Event event); // xu li cac buoc di chuyen
    // gioi han cua vien dan khi ban ra , them x_border voi y_border de tien xu li cac vat can khac => lam dan bien mat
    void HandleMove(const int& x_border, const int& y_border);  // LEFT TO RIGHT

    void HandleMoveFromRighttoLeft(const int& x_border, const int& y_border);
    
    int get_type() const {return amo_type_;}
    void set_type(const int &type) {amo_type_ = type;}

    bool get_is_move_() const {return is_move_;}
    void set_is_move_(bool move) {is_move_ = move;}
    // tuy loai dan ma kich co khac nhau phai goi them ham nay
    void SetWidthHeight(const int& width, const int& height) {rect_.w = width, rect_.y = height;}
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    int amo_type_;
};