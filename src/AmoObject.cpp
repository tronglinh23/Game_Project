#include "AmoObject.hpp"

AmoObject::AmoObject(){
    rect_.x = 0;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    amo_type_ = NONE;
}
AmoObject::~AmoObject(){

}

void AmoObject::HandleMoveFromRighttoLeft(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    if(rect_.x < 0){
        is_move_ = false;
    }
}

void AmoObject::HandleMove(const int& x_border, const int& y_border){
    rect_.x += x_val_; // dan ban huong thang ------------ . Co the them rect_y de dan bay xuong duoi hoac len tren
    if(rect_.x > x_border)
    {
        is_move_ = false;
    }
}

void AmoObject::HandleInputAction(SDL_Event){

}

