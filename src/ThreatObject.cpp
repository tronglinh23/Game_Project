#include "ThreatObject.hpp"

ThreatObject::ThreatObject(){
    x_val_ = 0;
    y_val_ = 0;
    rect_.x = SCREEN_WIDTH;
    rect_.y = SCREEN_HEIGHT* 0.5;
    rect_.w = WIDTH_THREAT;
    rect_.h = HEIGHT_THREAT;
    life_ = 1;
}

ThreatObject::~ThreatObject(){
    if(p_bullet_list_.size() > 0){
        for (int i = 0; i < p_bullet_list_.size(); i++)
        {
            BulletObject* p_bullet = p_bullet_list_.at(i);
            if(p_bullet != NULL){
                delete p_bullet;
                p_bullet = NULL;
            }
        }
        p_bullet_list_.clear();
    }
}
void ThreatObject::init(BulletObject* P_bullet,SDL_Renderer* screen){
    if(P_bullet != NULL){
        bool ret = P_bullet->LoadIMG("res/file anh/bullet/Bullet1.png",screen);
        if(ret){
            P_bullet->set_is_move_(true);
            P_bullet->SetWidthHeight(WIDTH_BULLET_THREAT,HEIGHT_BULLET_THREAT);
            P_bullet->SetRect(rect_.x - 5, rect_.y + rect_.h * 0.5);
            P_bullet->Set_x_val(x_val_ + 3); // toc do dan ban cua threat
            p_bullet_list_.push_back(P_bullet);
        }
    }
}
void ThreatObject::Upgrade_speed_Bullet(){
    for(int i = 0 ; i < p_bullet_list_.size(); i++){
        BulletObject* P_bullet = p_bullet_list_.at(i);
        P_bullet->Set_x_val(x_val_ + 3);
    }
    
}

void ThreatObject::Makebullet(SDL_Renderer* des, const int& x_limit , const int& y_limit)
{
    for (int i = 0; i < p_bullet_list_.size(); i++)
    {
        BulletObject * obs_bullet = p_bullet_list_.at(i);
        if(obs_bullet){
            if(obs_bullet->get_is_move_()){
                obs_bullet->Render(des,NULL);
                obs_bullet->HandleMoveFromRighttoLeft(SCREEN_WIDTH,SCREEN_HEIGHT);

            }
            else{
                // de dan dc ban ra mot cach lien tuc;
                obs_bullet->set_is_move_(true);
                obs_bullet->SetRect(rect_.x  - 5, rect_.y + rect_.h * 0.5);
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
        if(rect_.y >= SCREEN_HEIGHT - 50){
            rect_.y *= 5.0/10;
            // std::cout << rect_.y << " ";
        }
    }
}

void ThreatObject::ResetThreat(const int& xborder, const int& life){
    rect_.x = xborder;
    rect_.y = rand() % (SCREEN_HEIGHT + 400);
    if(rect_.y >= SCREEN_HEIGHT - rect_.h){
        rect_.y *= 5.0/10;
    }
    for(int i = 0 ; i < p_bullet_list_.size();i++){
        BulletObject* p_bullet = p_bullet_list_.at(i);
        if(p_bullet) Resetbullet(p_bullet);
    }
    Setlife_(life);
}

void ThreatObject::Resetbullet(BulletObject* p_bullet){
    p_bullet->SetRect(rect_.x - 5, rect_.y + rect_.h * 0.7);
} 

void ThreatObject::Removebullet_Threat(const int& k){
    if(k < p_bullet_list_.size()){
        BulletObject* p_bullet = p_bullet_list_.at(k);
        Resetbullet(p_bullet);
    }
}

void ThreatObject::Decrease_Life(){
    life_--;
}