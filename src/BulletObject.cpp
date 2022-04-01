#include "BulletObject.hpp"

BulletObject::BulletObject(){
    rect_.x = 0;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    amo_type_ = NONE;
}
BulletObject::~BulletObject(){

}

void BulletObject::HandleMoveFromRighttoLeft(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    if(rect_.x < 0){
        is_move_ = false;
    }
}

void BulletObject::HandleMove(const int& x_border, const int& y_border){
    rect_.x += x_val_; // dan ban huong thang ------------ . Co the them rect_y de dan bay xuong duoi hoac len tren
    if(rect_.x > x_border)
    {
        is_move_ = false;
    }
}

void BulletObject::HandleInputAction(SDL_Event){

}

