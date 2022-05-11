#include "PlayerPower.hpp"

PlayerPower::PlayerPower()
{

}
PlayerPower::~PlayerPower(){

}

void PlayerPower::AddPos(int const& xpos){
    pos_life_.push_back(xpos);
}

void PlayerPower::DisplayLife(SDL_Renderer* des){
    if(number_ == pos_life_.size())
    {
        for(int i = 0 ; i < pos_life_.size();i++){
            rect_.x = pos_life_.at(i);
            Render(des,NULL);
        }
    }
}
void PlayerPower::Init(){
    number_ = 3;
    if(pos_life_.size() > 0)
    {
        pos_life_.clear();
    }
    AddPos(20);
    AddPos(60);
    AddPos(100);
}
void PlayerPower::Decrease(){
    number_--;
    pos_life_.pop_back();
}

void PlayerPower::Increase(){
    number_++;
    if(number_ > 3) number_ = 3;
    else if(number_ == 3) AddPos(100);
    else if(number_ == 2) AddPos(60);
}