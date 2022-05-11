#include "BulletObject.hpp"

BulletObject::BulletObject(){
    rect_.x = 0;
    rect_.y = 0;
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = NONE;
    bullet_type_game_ = 0;
}
BulletObject::~BulletObject(){

}

void BulletObject::HandleMoveFromRighttoLeft(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    if(rect_.x < 0){
        is_move_ = false;
    }
}

void BulletObject::HandleMove(const int& x_border, const int& y_border, const int& k){
    if(bullet_type_game_ == 1 && bullet_type_ == LASER_2){ // dan ban toe 
        if(k == 2) {
            rect_.x += x_val_;
            rect_.y += x_val_/8;
            if(rect_.x > x_border || rect_.y > y_border) is_move_ = false;
        }
        else if(k == 1){
            rect_.x += x_val_;
            if(rect_.x > x_border)
            {
                is_move_ = false;
            }
            if(rect_.x > x_border || rect_.y  < 0 ) is_move_ = false;   
        }
        else if(k == 0){
            rect_.x += x_val_;
            rect_.y -= x_val_/8;
        }
    }
    else{
        rect_.x += x_val_; // dan ban huong thang ------------ . Co the them rect_y de dan bay xuong duoi hoac len tren
        if(rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
}

void BulletObject::HandleInputAction(SDL_Event){

}

