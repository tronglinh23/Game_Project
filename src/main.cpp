#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Common_function.hpp"
#include "BaseObject.hpp"
#include "MainObject.hpp"
#include "ThreatObject.hpp"
#include "BulletObject.hpp"
#include "time.h"
#include "ExplosionObject.hpp"
#include "PlayerPower.hpp"
#include "Text_Object.hpp"
#include "SupportObject.hpp"

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
    Mix_Quit();
    IMG_Quit();
	SDL_Quit();
}


bool LoadBackground(BaseObject &background){
    bool ret = background.LoadIMG(pics_background.c_str(),renderer);
    // for(int i = 0 ; i < n ; i++){
    //     ret = background[i].LoadIMG(pics_background[i].c_str(),renderer);
    //     if(ret == false) return false;
    //     background[i].setSize(WIDTH_BACKGROUND,HEIGHT_BACKGROUND);
    // }
    if(ret == false) return false;
    background.setSize(WIDTH_BACKGROUND,HEIGHT_BACKGROUND);
    return true;
}

bool LoadMainObject(MainObject &p_mainobject){
    bool ret = p_mainobject.LoadIMG("res/file anh/spaceship02_fix.png",renderer);
    p_mainobject.SetRect(mainobject_Pos_X_Start,mainobject_Pos_Y_Start); // vi tri xuat hien
    p_mainobject.setSize(WIDTH_MAIN_OBJECT,HEIGHT_MAIN_OBJECT);
    if(ret == false) return false;
    return true;
}
// de sau cai tien len 
std::string random_pics(){
    const std::string pics_threats[] = {"res/file anh/ship_enemy/Ship1.png", "res/file anh/ship_enemy/Ship2.png",
                                        "res/file anh/ship_enemy/Ship3.png", "res/file anh/ship_enemy/Ship4.png",
                                        "res/file anh/ship_enemy/Ship5.png", "res/file anh/ship_enemy/Ship6.png"};
    int ran = rand() % 6;
    return pics_threats[ran];
}
// INIT AUDIO
void Init()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        logSDLError(std::cout,"CREATE AUDIO",true);
    }
    // Initialize img
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        logSDLError(std::cout,"SDL_image could not initialize",true);
    }

        //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        logSDLError(std::cout,"SDL_mixer could not initialize",true);
    }
}

// Load Sound
void InitSound(){
    // Sound effect
    g_sound_bullet[0] = Mix_LoadWAV("res/sound/Gun+Silencer.wav");
    g_sound_bullet[1] = Mix_LoadWAV("res/sound/ES_Laser Gun Fire 11 - SFX Producer.mp3");
    g_sound_explosion = Mix_LoadWAV("res/sound/ES_Explosion Space 2 - SFX Producer.mp3");
    g_sound_options_choose = Mix_LoadWAV("res/sound/key.ogg");
    g_sound_eat_sp_object = Mix_LoadWAV("res/sound/potpickup.ogg");
    // Sound Game
    gMusic = Mix_LoadMUS("res/sound/ES_Letting Go of the Day - Hanna Lindgren.mp3");
    //Volume
    Mix_Volume(-1,40);
    // Check Excute
    if(g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || 
       g_sound_explosion == NULL || gMusic == NULL || 
       g_sound_eat_sp_object == NULL || g_sound_options_choose == NULL){
        logSDLError(std::cout,"MIX_LOADWAV SOUND could not initialize",true);
    }
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic(gMusic, -1 );
    }
}

// Load Text
void InitText(){
    if( TTF_Init() == -1 ) logSDLError(std::cout,"SDL_ttf could not initialize! SDL_ttf ",true);
    g_font_text = TTF_OpenFont(font_mark_game.c_str(),size_mark);
    menu_font_text = TTF_OpenFont(font_menu_game.c_str(),size_menu_text);
    menu_options_text_2 = TTF_OpenFont(font_menu_game.c_str(),size_text_menu_2);
    Subtr_mark = TTF_OpenFont(subtr_mark_text.c_str(),size_subtr_mark_text);
    if(!g_font_text && !menu_font_text && !menu_options_text_2 && !Subtr_mark) logSDLError(std::cout,"Failed to load lazy font! SDL_ttf ",true);
}

// ShowMenu
bool checkfocuswithrect(const int& x, const int& y, const SDL_Rect& rect){
    if( x >= rect.x && x < rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

// can sua
int Show_Menu(SDL_Renderer* des,BaseObject& Menu_show,TTF_Font* font_game_menu)
{
    bool ret = Menu_show.LoadIMG("res/file anh/background_4k.jpg",des);
    if(ret){
        Menu_show.setSize(SCREEN_WIDTH,SCREEN_HEIGHT);
    }
    // Title menu
    TextObject title_menu_game;
    title_menu_game.SetText(title);
    title_menu_game.SetColor(color_title_R,color_title_G,color_title_B);
    title_menu_game.SetRect(pos_title_x, pos_title_y);

    const int MenuItems = 2;
    SDL_Rect pos_items[MenuItems];
    pos_items[0].x = SCREEN_WIDTH/3.5;
    pos_items[0].y = 310;
    pos_items[1].x = SCREEN_WIDTH/3.5;
    pos_items[1].y = 385;
    
    TextObject text_menu[MenuItems];
    text_menu[0].SetText("Play game");
    text_menu[0].SetColor(color_ItemText_R,color_ItemText_G,color_ItemText_B);
    text_menu[0].SetRect(pos_items[0].x, pos_items[0].y);

    text_menu[1].SetText("Quit game");
    text_menu[1].SetColor(color_ItemText_R,color_ItemText_G,color_ItemText_B);
    text_menu[1].SetRect(pos_items[1].x, pos_items[1].y);

    SDL_Event menu_event;
    int xm = 0 , ym = 0;
    // vo han
    while(true){
        Menu_show.Render(des,NULL);
        for(int i = 0 ; i < MenuItems ; i++){
            text_menu[i].loadFromRenderedText(font_game_menu,des);

            text_menu[i].RenderText(des,pos_items[i].x,pos_items[i].y);

        }
        while(SDL_PollEvent(&menu_event)){
            switch(menu_event.type){

                case SDL_QUIT:
                    return 1;
                case SDL_MOUSEMOTION:
                {
                    // lay vi tri cua con chuot
                    xm = menu_event.motion.x;
                    ym = menu_event.motion.y;
                    // change colors
                    for(int i = 0 ; i < MenuItems; i++){
                        if(checkfocuswithrect(xm,ym,text_menu[i].GetRect())){
                            text_menu[i].SetColor(color_Change_ItemText_R, color_Change_ItemText_G, color_Change_ItemText_B);
                        }
                        else{
                            text_menu[i].SetColor(color_ItemText_R,color_ItemText_G,color_ItemText_B);
                        }
                    }

                    if(checkfocuswithrect(xm,ym,title_menu_game.GetRect())) 
                        title_menu_game.SetColor(color_title_change_R,color_title_change_G,color_title_change_B);
                    else 
                        title_menu_game.SetColor(color_title_R,color_title_G,color_title_B);

                    break;
                }
                // if button down
                case SDL_MOUSEBUTTONDOWN:
                {
                    xm = menu_event.button.x;
                    ym = menu_event.button.y;
                    for(int i = 0 ; i < MenuItems; i++){
                        if(checkfocuswithrect(xm,ym,text_menu[i].GetRect())){
                            Mix_PlayChannel(0,g_sound_options_choose,0);
                            return i;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
        title_menu_game.loadFromRenderedText(font_game_menu,des);
        title_menu_game.setSize(title_menu_game.GetRect().w ,title_menu_game.GetRect().h + 25);
        title_menu_game.RenderText(des,pos_title_x,pos_title_y);
        SDL_RenderPresent(des);
    }
    return 1;
}

// Init Support Object
void Init_Support_Object(SupportObject * list_object){
    int ran_num;
    for(int sp_ob = 0 ; sp_ob < Amount_Support_Object; sp_ob++){
        SupportObject* list_spp = list_object + sp_ob;
        list_spp->LoadIMG(file_pics_support_object[rand() % amount_pics_path].c_str(), renderer);
        list_spp->setSize(size_x_pics_sp, size_y_pics_sp);
        ran_num = rand() % (SCREEN_HEIGHT + 400);
        if(ran_num >= SCREEN_HEIGHT - 50) ran_num *= 5.0/10;
        list_spp->SetRect(SCREEN_WIDTH + sp_ob*50, ran_num);
        list_spp->Set_x_pos(3);
    }
}

void Init_life_Support_Object(SupportObject &life_suport, int speed_life){
    life_suport.SetRect(SCREEN_WIDTH , rand() % (SCREEN_HEIGHT - 100));
    life_suport.Set_x_pos(speed_life);
}

int Show_Menu_Options(){
    // return 0 : Continue
    // return 1 : Show menu
    // return 2 : Quit game
    
    bool time_pause = true;
    BaseObject Options_menu_background;
    Options_menu_background.LoadIMG("res/file anh/panel-5.png",renderer);
    Options_menu_background.setSize(400,200);
    Options_menu_background.SetRect(x_pos_menu_options, y_pos_menu_options);
    const int MenuItems = 2;
    SDL_Rect pos_items[MenuItems];
    pos_items[0].x = x_pos_menu_options + 80;
    pos_items[0].y = y_pos_menu_options + 50;
    pos_items[1].x = x_pos_menu_options + 80;
    pos_items[1].y = y_pos_menu_options + 100;
    TextObject text_menu[MenuItems];
    text_menu[0].SetText("CONTINUE");
    text_menu[0].SetColor(color_items_menu_2_R,color_items_menu_2_G,color_items_menu_2_B);
    text_menu[0].SetRect(pos_items[0].x, pos_items[0].y);

    text_menu[1].SetText("MENU");
    text_menu[1].SetColor(color_items_menu_2_R,color_items_menu_2_G,color_items_menu_2_B);
    text_menu[1].SetRect(pos_items[1].x, pos_items[1].y);
    int x = 0, y = 0;
    SDL_Event event_options;
    while(time_pause){
        Options_menu_background.Render(renderer,NULL);
        for(int i = 0 ; i < MenuItems ; i++){
            text_menu[i].loadFromRenderedText(menu_options_text_2,renderer);
            text_menu[i].RenderText(renderer,pos_items[i].x,pos_items[i].y);

        }    
        while(SDL_PollEvent(&event_options)){
            switch(event_options.type){
                case SDL_QUIT: return 2;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) return 0;
                case SDL_MOUSEMOTION:
                {
                    // lay vi tri cua con chuot
                    x = event_options.motion.x;
                    y = event_options.motion.y;
                    // change colors
                    for(int i = 0 ; i < MenuItems; i++){
                        if(checkfocuswithrect(x,y,text_menu[i].GetRect())){
                            text_menu[i].SetColor(color_Change_ItemText_R, color_Change_ItemText_G, color_Change_ItemText_B);
                        }
                        else
                            text_menu[i].SetColor(color_items_menu_2_R,color_items_menu_2_G,color_items_menu_2_B);
                    }
                    break;
                }
                // if button down
                case SDL_MOUSEBUTTONDOWN:
                {
                    x = event_options.button.x;
                    y = event_options.button.y;
                    for(int i = 0 ; i < MenuItems; i++){
                        if(checkfocuswithrect(x,y,text_menu[i].GetRect())){
                            Mix_PlayChannel(0,g_sound_options_choose,0);
                            return i;
                        }
                    }
                    break;
                }
                default:
                    break;
            }
        }
        SDL_RenderPresent(renderer);   
    }
    return 1;
}

// Main
int main(int argc, char* argv[])
{
    srand(time(NULL));
    initSDL(window, renderer);
    Init();
    InitSound();
    // Init MainObject, Background
    BaseObject g_background;
    MainObject g_mainobject;
    if(LoadBackground(g_background) == false) return -1;
    if(LoadMainObject(g_mainobject) == false) return -1;
    SDL_Rect mainobject = g_mainobject.GetRect();

    // Init ThreatObject
    ThreatObject * p_threat_list = new ThreatObject[Amount_Threat];

    for(int i = 0 ; i < Amount_Threat ; i++)
    {
        ThreatObject* p_threat = p_threat_list + i;
        p_threat->LoadIMG(random_pics(),renderer);
        p_threat->setSize(WIDTH_THREAT,HEIGHT_THREAT);
        int ran_num = rand() % (SCREEN_HEIGHT + 400);
        if(ran_num >= SCREEN_HEIGHT - 50) ran_num *= 5.0/10;
        p_threat->SetRect(SCREEN_WIDTH + i * 400,ran_num);
        p_threat->Set_x_val(Speed_Threat_default);

        BulletObject* threat_bullet = new BulletObject();
        p_threat->init(threat_bullet,renderer);
    }

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    // Init ExplosionObject
    ExplosionObject EXP_main;
    EXP_main.LoadIMG("res/file anh/merge_from_ofoct.png",renderer);
    EXP_main.set_clip();

    //Init mainobject's life power
    PlayerPower life_player;
    life_player.LoadIMG("res/file anh/star.png",renderer);
    life_player.setSize(45,45);
    life_player.Init();
    // Init TextObject
    InitText();
    TextObject mark_game;
    mark_game.SetColor(color_title_R,color_title_G,color_title_B);

    TextObject Time_game;
    Time_game.SetColor(color_title_R,color_title_G,color_title_B);

    TextObject Subtr_Mark_game;
    Subtr_Mark_game.SetColor(color_SubtrText_R,color_SubtrText_G,color_SubtrText_B);


    // Support Object
    SupportObject* list_object_support = new SupportObject[Amount_Support_Object];
    Init_Support_Object(list_object_support);
    
    SupportObject life_object_support;
    life_object_support.LoadIMG("res/file anh/star.png",renderer);
    life_object_support.setSize(50,50);
    Init_life_Support_Object(life_object_support, speed_life_support_default);

    //Path run
    int bkgn_x = 0;
    bool is_run_screen = true;
    bool is_quit = false;

    //Show Menu
    BaseObject menu_show;
    int ret_menu = Show_Menu(renderer,menu_show, menu_font_text);
    if(ret_menu == 1) is_quit = true;

    // Numbers of life ---- mark: kill threats
    unsigned int die_nums = 0;
    unsigned int mark_value_game = 0;
    unsigned int time = 0;
    unsigned int amount_bullet_main_object = 1;
    unsigned int time_menu_stop = 0;
    unsigned int step_time_menu = SDL_GetTicks()/1000;
    // Path flow
    while(!is_quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                is_quit = true;
                break;
            }
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:{
                        time_menu_stop = time;
                        int result_path = Show_Menu_Options();
                        if(result_path == 0){
                        }
                        else if(result_path == 2) is_quit = true;
                        else{
                            ret_menu = Show_Menu(renderer,menu_show, menu_font_text);
                            if(ret_menu == 1) is_quit = true;
                        }
                        step_time_menu = SDL_GetTicks()/1000 - time_menu_stop;
                        break;
                    }
                    // mainobject moves right , load new image
                    case SDLK_RIGHT:{
                        g_mainobject.LoadIMG("res/file anh/spaceship02_fix_2.png",renderer);
                        break;
                    }
                    case SDLK_d:{
                        g_mainobject.LoadIMG("res/file anh/spaceship02_fix_2.png",renderer);
                        break;
                    }    
                    default: break;
                }
            }
            else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym){
                    case SDLK_RIGHT:{
                        g_mainobject.LoadIMG("res/file anh/spaceship02_fix.png",renderer);
                        break;
                    }
                    case SDLK_d:{
                        g_mainobject.LoadIMG("res/file anh/spaceship02_fix.png",renderer);
                        break;
                    }
                    default: break;
                }
            }
            g_mainobject.HandleInputAction(event,renderer,g_sound_bullet,gMusic);

        }
        // Render many backgrounds
        // bkgn_x -= 2;
        // g_background[0].SetRect(bkgn_x,0);
        // g_background[0].Render(renderer,NULL);
        // g_background[1].SetRect(bkgn_x + SCREEN_WIDTH,0);
        // g_background[1].Render(renderer,NULL);
        // g_background[2].SetRect(bkgn_x + 2 * SCREEN_WIDTH,0);
        // g_background[2].Render(renderer,NULL);
        // g_background[3].SetRect(bkgn_x + 3 * SCREEN_WIDTH,0);
        // g_background[3].Render(renderer,NULL);
        // if(bkgn_x <= -(amount_pics_background - 1)  * SCREEN_WIDTH) bkgn_x = 0;

        // Render 1 background
        if(is_run_screen){
            bkgn_x -= speed_run_screen;
            if(bkgn_x <= - (WIDTH_BACKGROUND - SCREEN_WIDTH)){
                bkgn_x = 0 ;
            }
            g_background.SetRect(bkgn_x,0);
            g_background.Render(renderer,NULL);
        }
        else{
            g_background.SetRect(bkgn_x,0);
            g_background.Render(renderer,NULL);
        }

        //render player life
        life_player.DisplayLife(renderer);

        //Handling game timelines
        if(time > 5)
        {
            for(int list_ob = 0 ; list_ob < Amount_Support_Object ; list_ob++) 
            {
                SupportObject* ob_sp = list_object_support + list_ob;
                ob_sp->Hand_Support_Move(SCREEN_WIDTH,SCREEN_HEIGHT);
                ob_sp->Render(renderer,NULL);
                // Check collision support_ob and mainob
                bool crashing = ob_sp->CheckCollision(ob_sp->GetRect(),g_mainobject.GetRect());
                if(crashing){
                    mark_value_game += 5;
                    ob_sp->LoadIMG(file_pics_support_object[rand() % amount_pics_path].c_str(), renderer);
                    ob_sp->setSize(size_x_pics_sp, size_y_pics_sp);
                    ob_sp->Remove_support_Object(SCREEN_WIDTH);
                    Subtr_Mark_game.SetText("+5");
                    Subtr_Mark_game.loadFromRenderedText(Subtr_mark,renderer);
                    Subtr_Mark_game.RenderText(renderer, g_mainobject.GetRect().x + 35 , g_mainobject.GetRect().y - 35);
                    Mix_PlayChannel(0,g_sound_eat_sp_object,0);
                }
            }
        }
        
        if(time >= 10){
            // increase speed's threats, speed threat bullet
            for(int t = 0 ; t < Amount_Threat ; t++){
                ThreatObject* p_threat = (p_threat_list + t);
                p_threat->Set_x_val(Speed_Threat_default + time/20); 
                p_threat->Upgrade_speed_Bullet();
            }
            // Star - increase life 
            life_object_support.Handle_life_support_Move();
            life_object_support.Render(renderer,NULL);
            bool check_collid_life_main = life_object_support.CheckCollision(life_object_support.GetRect(), g_mainobject.GetRect());
            if(check_collid_life_main && die_nums > 0){
                die_nums--;
                life_player.Increase();
                life_player.DisplayLife(renderer);
                Init_life_Support_Object(life_object_support, 0);
                Mix_PlayChannel(0,g_sound_eat_sp_object,0);
                SDL_RenderPresent(renderer);
                
            }

            if(time % 30 == 0) Init_life_Support_Object(life_object_support, speed_life_support_default);
        }
        
        // Handle mainobject
        g_mainobject.HandMove();
        g_mainobject.Render(renderer,NULL);
        g_mainobject.Set_Amount_Bullet(amount_bullet_main_object);
        g_mainobject.Display_bullet(renderer);

        // Run Threat
        for(int t = 0 ; t < Amount_Threat ; t++){
            ThreatObject* p_threat = (p_threat_list + t);
            p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            p_threat->Render(renderer,NULL);
            p_threat->Makebullet(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
            // Check Collision mainobject - threats
            bool check_col = p_threat->CheckCollision(g_mainobject.GetRect(),p_threat->GetRect());
            // CAN DC FIX explosion
            if(check_col){
                for(int ex = 0 ; ex < number_frame_ ; ex++){
                    int x_pos = g_mainobject.GetRect().x + g_mainobject.GetRect().w*0.5 - 0.5*EXP_WIDTH;
                    int y_pos = g_mainobject.GetRect().y + g_mainobject.GetRect().w*0.5 - 0.5*EXP_HEIGHT;
                    SDL_Delay(75);
                    EXP_main.set_frame(ex);
                    EXP_main.SetRect(x_pos,y_pos);
                    EXP_main.RenderEx(renderer,NULL);
                    SDL_RenderPresent(renderer);
                    Subtr_Mark_game.SetText("-5");
                    Subtr_Mark_game.loadFromRenderedText(Subtr_mark,renderer);
                    Subtr_Mark_game.RenderText(renderer, g_mainobject.GetRect().x + 35 , g_mainobject.GetRect().y - 35);
                }
                if(mark_value_game > 5) mark_value_game -= 5; // Collision - decrease points

                Mix_PlayChannel(0,g_sound_explosion,0);
                
                p_threat->ResetThreat(SCREEN_WIDTH + t * 400); // After the collision, threat reset
                die_nums ++;
                if(die_nums <= 2){
                    SDL_Delay(500);
                    g_mainobject.SetRect(mainobject_Pos_X_Start,mainobject_Pos_Y_Start);
                    life_player.Decrease();
                    life_player.DisplayLife(renderer);
                    SDL_RenderPresent(renderer);
                }
                // Check game over
                else{
                    if(MessageBox(NULL,"GAME OVER","INFO",MB_OK) == IDOK){
                        delete [] p_threat_list;
                        quitSDL(window, renderer);
                        Time_game.Free();
                        mark_game.Free();
                        return 0;
                    }
                }
            }
            // Handling threat's bullets on mainobject
            std::vector<BulletObject*> threat_bullet_list = p_threat->Get_bullet_list();
            for(int k = 0 ; k < threat_bullet_list.size(); k++){
                BulletObject* p_bullet = threat_bullet_list.at(k);
                if(p_bullet){
                    bool check_col = p_bullet->CheckCollision(p_bullet->GetRect(),g_mainobject.GetRect());
                    if(check_col == true){
                        p_threat->Removebullet_Threat(k);
                        
                        Subtr_Mark_game.SetText("-1");
                        Subtr_Mark_game.loadFromRenderedText(Subtr_mark,renderer);
                        Subtr_Mark_game.RenderText(renderer, g_mainobject.GetRect().x + 35 , g_mainobject.GetRect().y - 35);
            
                        if(mark_value_game > 0 ) mark_value_game--; // bullet collsion - decrease points
                                                                        
                    }

                }
            }
            // Handling mainobject's bullets on threats
            for(int stt = 0 ; stt < amount_bullet_main_object ; stt++){
                std::vector<BulletObject*> bullet_list = g_mainobject.GetbulletList(stt);
                for(int k = 0 ; k < bullet_list.size(); k++){
                    BulletObject* p_bullet = bullet_list.at(k);
                    if(p_bullet){
                        bool ret_col = p_bullet->CheckCollision(p_bullet->GetRect(),p_threat->GetRect());
                        if(ret_col){
                            mark_value_game++; // Kill enemies - earn point
                            p_threat->LoadIMG(random_pics(),renderer);
                            p_threat->setSize(WIDTH_THREAT,HEIGHT_THREAT);
                            p_threat->ResetThreat(SCREEN_WIDTH + t * 400);
                            g_mainobject.Removebullet(stt,k); // delete mainobject's bullets
                            Mix_PlayChannel(0,g_sound_explosion,0);
                        }
                    }
                }
            }
            
        }
        // Render mark_Text 
        std::string val_str_mark = text + std::to_string(mark_value_game);
        mark_game.SetText(val_str_mark);
        mark_game.loadFromRenderedText(g_font_text,renderer);
        mark_game.RenderText(renderer, x_pos_render_mark_text, y_pos_render_mark_text);

        // Render time_text
        time = SDL_GetTicks()/1000 - step_time_menu;
        std::string Time_present = val_time + std::to_string(time);
        Time_game.SetText(Time_present);
        Time_game.loadFromRenderedText(g_font_text,renderer);
        Time_game.RenderText(renderer, x_pos_render_time_text, y_pos_render_time_text);

        SDL_RenderPresent(renderer);

    }
    Time_game.Free();
    mark_game.Free();
    delete [] p_threat_list;
    quitSDL(window, renderer);
    return 0;
}


