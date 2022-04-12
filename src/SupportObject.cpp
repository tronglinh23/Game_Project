#include "SupportObject.hpp"

SupportObject::SupportObject(){

}
SupportObject::~SupportObject(){

}
void SupportObject::Hand_Support_Move(const int& x_border, const int& y_border){
    rect_.x -= x_val_;
    if(rect_.x < 0){
        rect_.x = SCREEN_WIDTH;
        rect_.y = SCREEN_HEIGHT/3;
    }
}
