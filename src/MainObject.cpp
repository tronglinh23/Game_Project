
#include "MainObject.hpp"

MainObject::MainObject(){
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_MAIN_OBJECT;
    rect_.h = HEIGHT_MAIN_OBJECT;
    x_val_ = 0;
    y_val_ = 0;
}
MainObject::~MainObject(){
    
}

// xu li cac thao tac ban phim va chuot
void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen){
    if(events.type == SDL_KEYDOWN){
        switch(events.key.keysym.sym)
        {
            case SDLK_UP:
                y_val_ -= HEIGHT_MAIN_OBJECT/4;
                break;
            case SDLK_DOWN:
                y_val_ +=  HEIGHT_MAIN_OBJECT/4;
                break;
            case SDLK_RIGHT:
                x_val_ += WIDTH_MAIN_OBJECT/4;
                break;
            case SDLK_LEFT:
                x_val_ -= WIDTH_MAIN_OBJECT/4;
                break;
        }
    }
    else if(events.type == SDL_KEYUP){
        switch(events.key.keysym.sym)
        {
            case SDLK_UP:
                y_val_ += HEIGHT_MAIN_OBJECT/4;
                break;
            case SDLK_DOWN:
                y_val_ -=  HEIGHT_MAIN_OBJECT/4;
                break;
            case SDLK_RIGHT:
                x_val_ -= WIDTH_MAIN_OBJECT/4;
                break;
            case SDLK_LEFT:
                x_val_ += WIDTH_MAIN_OBJECT/4;
                break;
        }
    }
    else if(events.type == SDL_MOUSEBUTTONDOWN)
    {

        AmoObject* p_amo = new AmoObject();
        if(events.button.button == SDL_BUTTON_LEFT){
            p_amo->SetWidthHeight(WIDTH_LASER,HEIGHT_LASER);
            p_amo->LoadIMG("res/laser.png",screen);
            p_amo->set_type(AmoObject::LASER);
        }
        else if(events.button.button == SDL_BUTTON_RIGHT){
            p_amo->SetWidthHeight(WIDTH_SPHERE,HEIGHT_SPHERE);
            p_amo->LoadIMG("res/sphere.png",screen);
            p_amo->set_type(AmoObject::SPHERE);
        }
        p_amo->SetRect(this->rect_.x + this->rect_.w  - 15 , this->rect_.y + this->rect_.h * 0.7);
        p_amo->set_is_move_(true);
        p_amo_list_.push_back(p_amo); // mot loat cac vien dan k phai ban rieng le
    }
    else if(events.type == SDL_MOUSEBUTTONUP){

    }
    else{
        ;
    }
}

void MainObject::HandMove(){
    rect_.x += x_val_;
    if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH) rect_.x -= x_val_;
    rect_.y += y_val_;
    if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - 100) rect_.y -= y_val_;

}


