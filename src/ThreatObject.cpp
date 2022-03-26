#include "ThreatObject.hpp"

ThreatObject::ThreatObject(){
    x_val_ = 0;
    y_val_ = 0;
    rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT* 0.5;
    rect_.w = WIDTH_THREAT;
    rect_.h = HEIGHT_THREAT;
}

ThreatObject::~ThreatObject(){
    if(p_amo_list_.size() > 0){
        for (int i = 0; i < p_amo_list_.size(); i++)
        {
            AmoObject* p_amo = p_amo_list_.at(i);
            if(p_amo != NULL){
                delete p_amo;
                p_amo = NULL;
            }
        }
        p_amo_list_.clear();
    }
}
void ThreatObject::init(AmoObject* P_amo,SDL_Renderer* screen){
    if(P_amo != NULL){
        bool ret = P_amo->LoadIMG("res/sphere.png",screen);
        if(ret){
            P_amo->set_is_move_(true);
            P_amo->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
            P_amo->SetRect(rect_.x - 5, rect_.y + rect_.h * 0.7);
            P_amo->Set_x_val(8); // toc do dan ban cua threat
            p_amo_list_.push_back(P_amo);
        }
    }
}

void ThreatObject::MakeAmo(SDL_Renderer* des, const int& x_limit , const int& y_limit)
{
    for (int i = 0; i < p_amo_list_.size(); i++)
    {
        AmoObject * obs_amo = p_amo_list_.at(i);
        if(obs_amo){
            if(obs_amo->get_is_move_()){
                obs_amo->Render(des,NULL);
                obs_amo->HandleMoveFromRighttoLeft(SCREEN_WIDTH,SCREEN_HEIGHT);

            }
            else{
                // de dan dc ban ra mot cach lien tuc;
                obs_amo->set_is_move_(true);
                obs_amo->SetRect(rect_.x  - 5, rect_.y + rect_.h * 0.7);
            }
        }
        
    }
    
}

void ThreatObject::HandleMove(const int& x_border, const int& y_boder){
   
    rect_.x -= x_val_; // obstacle di chuyen
    if(rect_.x < 0) {
        rect_.x = SCREEN_WIDTH;
        rect_.y = rand() % (SCREEN_HEIGHT + 400);
        // std::cout << rect_.y << " "; 
        if(rect_.y > SCREEN_HEIGHT - 200){
            rect_.y *= 5.0/10;
            // std::cout << rect_.y << " ";
        }
    }
}

void ThreatObject::ResetThreat(const int& xborder){
    rect_.x = xborder;
    rect_.y = rand() % (SCREEN_HEIGHT + 400);
    if(rect_.y > SCREEN_HEIGHT - 200){
        rect_.y *= 5.0/10;
    }
    for(int i = 0 ; i < p_amo_list_.size();i++){
        AmoObject* p_amo = p_amo_list_.at(i);
        if(p_amo) ResetAmo(p_amo);
    }

}

void ThreatObject::ResetAmo(AmoObject* p_amo){
    p_amo->SetRect(rect_.x - 5, rect_.y + rect_.h * 0.7);
} 

void ThreatObject::RemoveAmo_Threat(const int& k){
    if(k < p_amo_list_.size()){
        AmoObject* p_amo = p_amo_list_.at(k);
        ResetAmo(p_amo);
    }
}