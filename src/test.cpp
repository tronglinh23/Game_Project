#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "Common_function.hpp"
#include "BaseObject.hpp"
#include "MainObject.hpp"
#include "ThreatObject.hpp"
#include "time.h"
#include "ExplosionObject.hpp"

void logSDLError(std::ostream& os, const std::string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer) 
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) logSDLError(std::cout, "CreateWindow", true); // window == nullptr

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

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
    bool ret = background.LoadIMG("res/bg4800.png",renderer);
    // background.setSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    if(ret == false) return false;
    return true;
}

bool LoadMainObject(MainObject &p_mainobject){
    bool ret = p_mainobject.LoadIMG("res/plane_fly.png",renderer);
    p_mainobject.SetRect(100,200); // vi tri xuat hien
    p_mainobject.setSize(WIDTH_MAIN_OBJECT,HEIGHT_MAIN_OBJECT);
    if(ret == false) return false;
    return true;
}

std::string random_pics(){
    const std::string pics_threats[] = {"res/Planets/Baren.png","res/Planets/Ice.png",
                            "res/Planets/Lava.png","res/Planets/Terran.png"};
    int ran = rand() % 4;
    return pics_threats[ran];
}
// Main
int main(int argc, char* argv[])
{
    srand(time(NULL));
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
        p_threat->LoadIMG(random_pics(),renderer);
        int ran_num = rand() % (SCREEN_HEIGHT + 400);
        if(ran_num > SCREEN_HEIGHT - 200) ran_num *= 5.0/10;
        p_threat->SetRect(SCREEN_WIDTH + i * 400,ran_num);
        p_threat->Set_x_val(6);

        AmoObject* threat_amo = new AmoObject();
        p_threat->init(threat_amo,renderer);
    }

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    // Init ExplosionObject
    ExplosionObject EXP_main;
    EXP_main.LoadIMG("res/exp_main.png",renderer);
    // EXP_main.SetRect(165,165);
    EXP_main.set_clip();
    //
    int bkgn_x = 0;
    bool is_run_screen = true;
    bool is_quit = false;

    
    // mau cua mainobject
    const int health = 1000;
    int remain = health;
    //
    while(!is_quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                is_quit = true;
                break;
            }
            g_mainobject.HandleInputAction(event,renderer);
        }
        
        // Load 2 tam anh lien tiep de cho cam tuong dang chay
        // g_background.SetRect(bkgn_x,0);
        // g_background.Render(renderer,NULL);
        // g_background.SetRect(bkgn_x + SCREEN_WIDTH,0);
        // g_background.Render(renderer,NULL);
        // if(bkgn_x <= -SCREEN_WIDTH) bkgn_x = 0;

        if(is_run_screen){
            bkgn_x -= 2;
            if(bkgn_x <= - (WIDTH_BACKGROUND - SCREEN_WIDTH)) is_run_screen = false; // den man hinh cuoi cung thi dung lai de danh boss
            g_background.SetRect(bkgn_x,0);
            g_background.Render(renderer,NULL);
        }
        else{
            g_background.SetRect(bkgn_x,0);
            g_background.Render(renderer,NULL);
        }
        g_mainobject.HandMove();
        g_mainobject.Render(renderer,NULL);
        g_mainobject.Display_Amo(renderer);
        // run Threat
        for(int t = 0 ; t < Amount_Threat ; t++){
            ThreatObject* p_threat = (p_threat_list + t);
            p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            p_threat->Render(renderer,NULL);
            p_threat->MakeAmo(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
            // kiem tra va cham
            bool check_col = p_threat->CheckCollision(g_mainobject.GetRect(),p_threat->GetRect());
            if(check_col){
                for(int ex = 0 ; ex < 4 ; ex++){
                    int x_pos = g_mainobject.GetRect().x + g_mainobject.GetRect().w*0.5 - 0.5*EXP_WIDTH;
                    int y_pos = g_mainobject.GetRect().y + g_mainobject.GetRect().w*0.5 - 0.5*EXP_HEIGHT;
                    EXP_main.set_frame(ex);
                    EXP_main.SetRect(x_pos,y_pos);
                    EXP_main.RenderEx(renderer,NULL);
                    SDL_Delay(100);
                    SDL_RenderPresent(renderer);
                }
                if(MessageBox(NULL,"GAME OVER","INFO",MB_OK) == IDOK){
                    delete [] p_threat_list;
                    quitSDL(window, renderer);
                    return 0;
                }
            }
            // xu li dan cua threat vao mainobject
            std::vector<AmoObject*> threat_amo_list = p_threat->Get_Amo_list();
            for(int k = 0 ; k < threat_amo_list.size(); k++){
                AmoObject* p_amo = threat_amo_list.at(k);
                if(p_amo){
                    bool check_col = p_amo->CheckCollision(p_amo->GetRect(),g_mainobject.GetRect());
                    if(check_col == true){
                        p_threat->RemoveAmo_Threat(k);
    
                        remain -= 200;
                        std::cout << remain << " ";
                    }
                    if(remain <= 0){   
                        std::cout << "Died";
                        return 0;
                    }
                }
            }
            // xu li va cham vien dan voi may bay
            std::vector<AmoObject*> amo_list = g_mainobject.GetAmoList();
            for(int k = 0 ; k < amo_list.size(); k++){
                AmoObject* p_amo = amo_list.at(k);
                if(p_amo){
                    bool ret_col = p_amo->CheckCollision(p_amo->GetRect(),p_threat->GetRect());
                    if(ret_col){
                        p_threat->ResetThreat(SCREEN_WIDTH + t * 400);
                        g_mainobject.RemoveAmo(k); // xoa vien dan cua mainobject
                    }
                }
            }
            
        }
        SDL_RenderPresent(renderer);
    }
    delete [] p_threat_list;
    quitSDL(window, renderer);
    return 0;
}



