#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "Common_function.hpp"
#include "BaseObject.hpp"
#include "MainObject.hpp"
#include "ThreatObject.hpp"
#include "time.h"

void logSDLError(std::ostream& os, const std::string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

const std::string WINDOW_TITLE = "SDL2 _ GAME CPP";


void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) logSDLError(std::cout, "CreateWindow", true); // window == nullptr

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | 
                                              SDL_RENDERER_PRESENTVSYNC);
\

    if (!renderer) logSDLError(std::cout, "CreateRenderer", true);  // renderer == nullptr

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


bool LoadBackground(BaseObject &background){
    bool ret = background.LoadIMG("res/space.png",renderer);
    background.setSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    if(ret == false) return false;
    return true;
}

bool LoadMainObject(MainObject &p_mainobject){
    bool ret = p_mainobject.LoadIMG("res/airship.png",renderer);
    p_mainobject.SetRect(100,200);
    p_mainobject.setSize(WIDTH_MAIN_OBJECT,HEIGHT_MAIN_OBJECT);
    if(ret == false) return false;
    return true;
}

// Main
int main(int argc, char* argv[])
{
    srand(5);
    initSDL(window, renderer);
    // Init MainObject
    BaseObject g_background;
    MainObject g_mainobject;
    if(LoadBackground(g_background) == false) return -1;
    if(LoadMainObject(g_mainobject) == false) return -1;
    SDL_Rect mainobject = g_mainobject.GetRect();
    ThreatObject * p_threat_list = new ThreatObject[Amount_Threat];
    for(int i = 0 ; i < Amount_Threat ; i++)
    {
        ThreatObject* p_threat = p_threat_list + i;
        p_threat->LoadIMG("res/af1.png",renderer);
        int ran_num = rand() % (SCREEN_HEIGHT + 400);
        std::cout << ran_num << " "; 
        if(ran_num > SCREEN_HEIGHT - 200) ran_num *= 5.0/10;
        p_threat->SetRect(SCREEN_WIDTH + i * 400,ran_num);
        p_threat->Set_x_val(6);

        AmoObject* threat_amo = new AmoObject();
        p_threat->init(threat_amo,renderer);
    }


    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);

    bool is_quit = false;
    while(!is_quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                is_quit = true;
                break;
            }
            g_mainobject.HandleInputAction(event,renderer);
        }

        g_background.Render(renderer,NULL);
        g_mainobject.HandMove();
        g_mainobject.Render(renderer,NULL);
        for(int i = 0 ; i < g_mainobject.GetAmoList().size(); i++){
            std::vector<AmoObject*> amo_list = g_mainobject.GetAmoList(); 
            // tao ra mot cai list để chứa các viên đạn , bắn ra một cách liên tục
            AmoObject* p_amo = amo_list.at(i); // xét từ vị trí viên đầu tiên
            if(p_amo != NULL){
                if(p_amo->get_is_move_()){
                    p_amo->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT); // KHi gap vat can thi xoa vien dan
                    p_amo->Render(renderer,NULL);
                }
                // khi gap vat can thi get_is_move = false -> lệnh else thực hiện và xóa đi viên đạn đấy, 
                else{
                    if(p_amo != NULL){
                        amo_list.erase(amo_list.begin() + i); 
                        // thao tác bắn sẽ được xóa khỏi mảng => từ đó hàm amo_list được khởi tạo lại và mất đi thao tác vừa rồi
                        g_mainobject.SetAmoList(amo_list); // SetAmolist mới , để amo_list = g_mainobject.GetAmoList() được thay đổi 
                        delete p_amo; // delete để k bị thất thoát bộ nhớ
                        p_amo = NULL;
                    }
                }
            }
        }
        // run Threat
        for(int t = 0 ; t < Amount_Threat ; t++){
            ThreatObject* p_threat = (p_threat_list + t);
            p_threat->Render(renderer,NULL);
            p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            p_threat->MakeAmo(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
        }
        SDL_RenderPresent(renderer);
    }
    delete [] p_threat_list;
    quitSDL(window, renderer);
    return 0;
}



