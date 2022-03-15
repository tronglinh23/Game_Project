
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
                y_val_ -= HEIGHT_MAIN_OBJECT/6;
                break;
            case SDLK_DOWN:
                y_val_ +=  HEIGHT_MAIN_OBJECT/6;
                break;
            case SDLK_RIGHT:
                x_val_ += WIDTH_MAIN_OBJECT/6;
                std::cout << x_val_ << " ";
                break;
            case SDLK_LEFT:
                x_val_ -= WIDTH_MAIN_OBJECT/6;
                std::cout << x_val_ << " ";
                break;
        }
    }
    else if(events.type == SDL_KEYUP){
        switch(events.key.keysym.sym)
        {
            case SDLK_UP:
                y_val_ += HEIGHT_MAIN_OBJECT/6;
                break;
            case SDLK_DOWN:
                y_val_ -=  HEIGHT_MAIN_OBJECT/6;
                break;
            case SDLK_RIGHT:
                x_val_ -= WIDTH_MAIN_OBJECT/6;
                std::cout << x_val_ << " ";
                break;
            case SDLK_LEFT:
                x_val_ += WIDTH_MAIN_OBJECT/6;
                std::cout << x_val_ << " ";
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
        p_amo->Set_x_val(20); // xet toc do vien dan cua mainobject
        p_amo_list_.push_back(p_amo); // mot loat cac vien dan k phai ban rieng le
    }
    else if(events.type == SDL_MOUSEBUTTONUP){

    }
    else{
        ;
    }
}
void MainObject::Display_Amo(SDL_Renderer* des){
    for(int i = 0 ; i < p_amo_list_.size(); i++){
        // tao ra mot cai list để chứa các viên đạn , bắn ra một cách liên tục
        AmoObject* p_amo = p_amo_list_.at(i); // xét từ vị trí viên đầu tiên
        if(p_amo != NULL){
            if(p_amo->get_is_move_()){
                p_amo->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT); // KHi gap vat can thi xoa vien dan
                p_amo->Render(des,NULL);
            }
            // khi gap vat can thi get_is_move = false -> lệnh else thực hiện và xóa đi viên đạn đấy, 
            else{
                if(p_amo != NULL){
                    p_amo_list_.erase(p_amo_list_.begin() + i); 
                    // thao tác bắn sẽ được xóa khỏi mảng => từ đó hàm amo_list được khởi tạo lại và mất đi thao tác vừa rồi
                    delete p_amo; // delete để k bị thất thoát bộ nhớ
                    p_amo = NULL;
                }
            }
        }
    }
}

void MainObject::HandMove(){
    rect_.x += x_val_;
    if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH) rect_.x -= x_val_;
    rect_.y += y_val_;
    if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT - Under_Limit_Threat) rect_.y -= y_val_;
    
}
void MainObject::RemoveAmo(const int& x){  
    if(x < p_amo_list_.size()){
        AmoObject* p_amo = p_amo_list_.at(x);
        p_amo_list_.erase(p_amo_list_.begin() + x);
        if(p_amo != NULL){
            delete p_amo;
            p_amo = NULL;
        }
    }
}


