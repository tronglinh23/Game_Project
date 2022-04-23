#include "SupportObject.hpp"

SupportObject::SupportObject(){

}
SupportObject::~SupportObject(){

}
void SupportObject::Remove_support_Object(const int& x_border){
    rect_.x = x_border + 200 + (rand() % 200);
    rect_.y = rand() % (SCREEN_HEIGHT + 400);
    if(rect_.y >= SCREEN_HEIGHT - 50){
        rect_.y *= 5.0/10;
    }
}
void SupportObject::Hand_Support_Move(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    if(rect_.x < 0){
        Remove_support_Object(x_border);
    }
}
void SupportObject::Handle_life_support_Move(){
    rect_.x -= x_val_;
    if(rect_.x < 0){
        rect_.x = SCREEN_WIDTH;
        x_val_ = 0;
    }
}
