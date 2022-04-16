
#include "MainObject.hpp"

MainObject::MainObject(){
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = WIDTH_MAIN_OBJECT;
    rect_.h = HEIGHT_MAIN_OBJECT;
    x_val_ = 0;
    y_val_ = 0;
    amount_bullet_ = 1;
}
MainObject::~MainObject(){
    
}

// xu li cac thao tac ban phim va chuot
void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* bullet[2], Mix_Music* gMusic){
    if(events.type == SDL_KEYDOWN){
        switch(events.key.keysym.sym)
        {
            //up
            case SDLK_UP:
                y_val_ = -y_step;
                break;
            case SDLK_w:
                y_val_ = -y_step;
                break;
            //down
            case SDLK_DOWN:
                y_val_ = y_step;
                break;
            case SDLK_s:
                y_val_ = y_step;
                break;
            //right
            case SDLK_RIGHT:
                x_val_ = x_step;
                break;
            case SDLK_d:
                x_val_ = x_step;
                break;
            //left
            case SDLK_LEFT:
                x_val_ = -x_step;
                break;
            case SDLK_a:
                x_val_ = -x_step;
                break;
            // turn on Music
            case SDLK_9:
            //If there is no music playing
                if( Mix_PlayingMusic() == 0 )
                {
                    //Play the music
                    Mix_PlayMusic(gMusic, -1 );
                }
                //If music is being played
                else
                {
                    //If the music is paused
                    if( Mix_PausedMusic() == 1 )
                    {
                        //Resume the music
                        Mix_ResumeMusic();
                    }
                    //If the music is playing
                    else
                    {
                        //Pause the music
                        Mix_PauseMusic();
                    }
                }
                break;
            case SDLK_0:
            //Stop the music
            Mix_HaltMusic();
            break;
        }
    }
    else if(events.type == SDL_KEYUP){
        switch(events.key.keysym.sym)
        {
            case SDLK_UP:
                y_val_ += y_step;
                break;
            case SDLK_w:
                y_val_ += y_step;
                break;
            
            case SDLK_DOWN:
                y_val_ -=  y_step;
                break;
            case SDLK_s:
                y_val_ -=  y_step;
                break;

            case SDLK_RIGHT:
                x_val_ -= x_step;
                break;
            case SDLK_d:
                x_val_ -= x_step;
                break;
            
            case SDLK_LEFT:
                x_val_ += x_step;
                break;
            case SDLK_a:
                x_val_ += x_step;
                break;
        }
    }
    else if(events.type == SDL_MOUSEBUTTONDOWN)
    {
        for(int i  = 0 ; i < amount_bullet_; i++){

            BulletObject* p_bullet = new BulletObject();
            if(events.button.button == SDL_BUTTON_LEFT){
                p_bullet->SetWidthHeight(WIDTH_LASER,HEIGHT_LASER);
                p_bullet->LoadIMG("res/file anh/bullet/Bullet6.png",screen);
                p_bullet->set_type(BulletObject::LASER);
                Mix_PlayChannel(-1,bullet[0],0);
            }
            else if(events.button.button == SDL_BUTTON_RIGHT){
                p_bullet->SetWidthHeight(WIDTH_BULLET_THREAT,HEIGHT_BULLET_THREAT);
                p_bullet->LoadIMG("res/file anh/bullet/Bullet2.png",screen);
                p_bullet->set_type(BulletObject::LASER_2);
                Mix_PlayChannel(-1,bullet[1],0);
            }
            p_bullet->SetRect(this->rect_.x + this->rect_.w  - 20 , this->rect_.y + this->rect_.h * 0.5 + i*10); // de lai de sua vi tri dan ban ra
            p_bullet->set_is_move_(true);
            p_bullet->Set_x_val(20); // xet toc do vien dan cua mainobject
            p_bullet_list_[i].push_back(p_bullet); // mot loat cac vien dan k phai ban rieng le
        }
    }
    else if(events.type == SDL_MOUSEBUTTONUP){

    }
    else{
        ;
    }
}
void MainObject::Display_bullet(SDL_Renderer* des){
    for(int stt = 0 ; stt < amount_bullet_; stt++){
        for(int i = 0 ; i < p_bullet_list_[stt].size(); i++){
            // tao ra mot cai list để chứa các viên đạn , bắn ra một cách liên tục
            BulletObject* p_bullet = p_bullet_list_[stt].at(i); // xét từ vị trí viên đầu tiên
            if(p_bullet != NULL){
                if(p_bullet->get_is_move_()){
                    p_bullet->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT); // KHi gap vat can thi xoa vien dan
                    p_bullet->Render(des,NULL);
                }
                // khi gap vat can thi get_is_move = false -> lệnh else thực hiện và xóa đi viên đạn đấy, 
                else{
                    if(p_bullet != NULL){
                        p_bullet_list_[stt].erase(p_bullet_list_[stt].begin() + i); 
                        // thao tác bắn sẽ được xóa khỏi mảng => từ đó hàm bullet_list được khởi tạo lại và mất đi thao tác vừa rồi
                        delete p_bullet; // delete để k bị thất thoát bộ nhớ
                        p_bullet = NULL;
                    }
                }
            }
        }
    }
}

void MainObject::HandMove(){
    if(x_val_ > x_step || x_val_ < -x_step) x_val_/=2;
     if(y_val_ > y_step || y_val_ < -y_step) y_val_/=2;
    rect_.x += x_val_;
    if(rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH) rect_.x -= x_val_;
    rect_.y += y_val_;
    if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT) rect_.y -= y_val_;
    
}
void MainObject::Removebullet(const int& stt,const int& x){  
    if(x < p_bullet_list_[stt].size()){
        BulletObject* p_bullet = p_bullet_list_[stt].at(x);
        p_bullet_list_[stt].erase(p_bullet_list_[stt].begin() + x);
        if(p_bullet != NULL){
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}


