#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "time.h"
#include "Common_function.hpp"
#include "BaseObject.hpp"
#include "MainObject.hpp"
#include "ThreatObject.hpp"
#include "BulletObject.hpp"
#include "ExplosionObject.hpp"
#include "PlayerPower.hpp"
#include "Text_Object.hpp"
#include "SupportObject.hpp"
#include <fstream>
// Init Background
void InitBackground(BaseObject &background){
    bool ret = background.LoadIMG(pics_background.c_str(),renderer);
    if(ret == false) logSDLError(std::cout, "Create Background", true);
    background.setSize(WIDTH_BACKGROUND,HEIGHT_BACKGROUND);
}
// Init MainObject
void InitMainObject(MainObject &p_mainobject){
    bool ret = p_mainobject.LoadIMG("res/file anh/spaceship02_fix.png",renderer);
    p_mainobject.SetRect(mainobject_Pos_X_Start,mainobject_Pos_Y_Start); // vi tri xuat hien
    p_mainobject.setSize(WIDTH_MAIN_OBJECT,HEIGHT_MAIN_OBJECT);
    p_mainobject.Set_x_step_y_step(Speed_deafault_mainobject_x, Speed_deafault_mainobject_Y);
    p_mainobject.Set_x_val_y_val_default();
    if(ret == false) logSDLError(std::cout, "Create Mainobject", true);
}
// INIT AUDIO
void Init_Audio()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) logSDLError(std::cout,"CREATE AUDIO",true);
    // Initialize img
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init( imgFlags ) & imgFlags) ) logSDLError(std::cout,"SDL_image could not initialize",true);
        //Initialize SDL_mixer
    if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) logSDLError(std::cout,"SDL_mixer could not initialize",true);
    
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
    if( Mix_PlayingMusic() == 0)
    {
        //Play the music
        Mix_VolumeMusic(30);
        Mix_PlayMusic(gMusic, -1 );
    }
}
// Load Text
void InitText(){
    if( TTF_Init() == -1 ) logSDLError(std::cout,"SDL_ttf could not initialize! SDL_ttf ",true);
    g_font_text = TTF_OpenFont(font_mark_game.c_str(),size_mark);
    menu_font_text = TTF_OpenFont(font_menu_game.c_str(),size_menu_text);
    Subtr_mark = TTF_OpenFont(subtr_mark_text.c_str(),size_subtr_mark_text);
    if(!g_font_text && !menu_font_text && !Subtr_mark) logSDLError(std::cout,"Failed to load lazy font! SDL_ttf ",true);
}
// Init Support Object - planets
void Init_Support_Object(SupportObject * list_object){
    for(int sp_ob = 0 ; sp_ob < Amount_Support_Object; sp_ob++){
        SupportObject* list_spp = list_object + sp_ob;
        list_spp->LoadIMG(file_pics_support_object[rand() % amount_pics_path].c_str(), renderer);
        list_spp->setSize(size_x_pics_sp, size_y_pics_sp);
        int ran_num = rand() % (SCREEN_HEIGHT + 400);
        if(ran_num >= SCREEN_HEIGHT - 50) ran_num *= 5.0/10;
        list_spp->SetRect(SCREEN_WIDTH + sp_ob*50, ran_num);
        list_spp->Set_x_pos(3);
    }
}
// Init Items Support - speed , bullet, star
void Init_Items_Support_Object(SupportObject &life_suport, int speed_life){
    life_suport.SetRect(SCREEN_WIDTH , rand() % (SCREEN_HEIGHT - 100));
    life_suport.setSize(size_x_pics_increase_ability_sp, size_y_pics_increase_ability_sp);
    life_suport.Set_x_pos(speed_life);
}
// Random pics threats
std::string random_pics(){
    const std::string pics_threats[] = {"res/file anh/ship_enemy/Ship1.png", "res/file anh/ship_enemy/Ship2.png",
                                        "res/file anh/ship_enemy/Ship3.png", "res/file anh/ship_enemy/Ship4.png",
                                        "res/file anh/ship_enemy/Ship5.png", "res/file anh/ship_enemy/Ship6.png"};
    int ran = rand() % 6;
    return pics_threats[ran];
}
// Init ThreatObject
void Init_ThreatObject(ThreatObject *llist_threat, int amount_threats){
    for(int i = 0 ; i < amount_threats ; i++)
    {
        ThreatObject* p_threat = llist_threat + i;
        if(i == amount_threats - 1){
            p_threat->LoadIMG("res/file anh/ship_enemy/boss_ship_1.png", renderer);
            p_threat->setSize(WIDTH_THREAT_TANK, HEIGHT_THREAT_TANK);
            p_threat->Setlife_(life_tank_threat_object);
        }
        else{
            p_threat->LoadIMG(random_pics(),renderer);
            p_threat->setSize(WIDTH_THREAT,HEIGHT_THREAT);
            p_threat->Setlife_(life_threat_object);
        }
        int ran_num = rand() % (SCREEN_HEIGHT + 400);
        if(ran_num > SCREEN_HEIGHT - p_threat->GetRect().h) ran_num *= 5.0/10;
        p_threat->SetRect(SCREEN_WIDTH + i * 400,ran_num);
        p_threat->Set_x_val(Speed_Threat_default);
        p_threat->Upgrade_speed_Bullet();
        BulletObject* threat_bullet = new BulletObject();
        p_threat->init(threat_bullet,renderer);
    }
}
// Check focus button 
bool checkfocuswithrect(const int& x, const int& y, const SDL_Rect& rect){
    if( x >= rect.x && x < rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}
// Show Menu
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
                case SDL_QUIT: return 1;
                case SDL_MOUSEMOTION:{
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
                    break;
                }
                // if button down
                case SDL_MOUSEBUTTONDOWN:{
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
// Gameover
bool GameOver(const int& mark, int &highest_score ,const int& time){
    if(mark >= highest_score) highest_score = mark;
    BaseObject Gameover_menu;
    Gameover_menu.LoadIMG("res/file anh/panel-1.png",renderer);
    Gameover_menu.SetRect(x_pos_gameover, y_pos_gameover);
    const int MenuItems = 5;
    SDL_Rect pos_items[MenuItems];
    pos_items[0].x = x_pos_gameover + 80;
    pos_items[0].y = y_pos_gameover + 70;
    pos_items[1].x = x_pos_gameover + 80;
    pos_items[1].y = y_pos_gameover + 120;
    pos_items[2].x = x_pos_gameover + 80;
    pos_items[2].y = y_pos_gameover + 170;
    pos_items[3].x = x_pos_gameover + 175;
    pos_items[3].y = y_pos_gameover + 300;
    pos_items[4].x = x_pos_gameover + 80;
    pos_items[4].y = y_pos_gameover + 220;
    TextObject text_menu[MenuItems];
    text_menu[0].SetText("Game Over");
    text_menu[0].SetColor(color_gameover_R,color_gameover_G,color_gameover_B);
    text_menu[0].SetRect(pos_items[0].x, pos_items[0].y);
    text_menu[1].SetText("Your Score : " + std::to_string(mark));
    text_menu[1].SetColor(color_gameover_R,color_gameover_G,color_gameover_B);
    text_menu[1].SetRect(pos_items[1].x, pos_items[1].y);
    text_menu[2].SetText("Your Time : " + std::to_string(time));
    text_menu[2].SetColor(color_gameover_R,color_gameover_G,color_gameover_B);
    text_menu[2].SetRect(pos_items[2].x, pos_items[2].y);
    text_menu[3].SetText("PLAY AGAIN");
    text_menu[3].SetColor(color_gameover_R,color_gameover_G,color_gameover_B);
    text_menu[3].SetRect(pos_items[3].x, pos_items[3].y);
    text_menu[4].SetText("Highest Score : " + std::to_string(highest_score));
    text_menu[4].SetColor(color_gameover_R,color_gameover_G,color_gameover_B);
    text_menu[4].SetRect(pos_items[4].x, pos_items[4].y);

    SDL_Event event_options;
    event_options.key.keysym.sym = SDLK_a;
    int x, y;
    while(true){
        while(SDL_PollEvent(&event_options)){
                switch(event_options.type){
                    case SDL_QUIT: return true; break;
                    case SDL_MOUSEMOTION:{
                        // lay vi tri cua con chuot
                        x = event_options.motion.x;
                        y = event_options.motion.y;
                        // change colors
                        if(checkfocuswithrect(x,y,text_menu[3].GetRect()))
                            text_menu[3].SetColor(color_Change_ItemText_R, color_Change_ItemText_G, color_Change_ItemText_B); 
                        else
                            text_menu[3].SetColor(color_gameover_R,color_gameover_G,color_gameover_B);
                        break;
                    }
                    case SDL_MOUSEBUTTONDOWN:{
                        x = event_options.button.x;
                        y = event_options.button.y;
                        if(checkfocuswithrect(x,y,text_menu[3].GetRect())){
                            Mix_PlayChannel(0,g_sound_options_choose,0);
                            return false;
                        }
                        break;
                    }
                }
        }
        Gameover_menu.Render(renderer, NULL);
        for(int i = 0 ; i < MenuItems ; i++){
            text_menu[i].loadFromRenderedText(g_font_text,renderer);
            text_menu[i].RenderText(renderer,pos_items[i].x,pos_items[i].y);
        }
        SDL_RenderPresent(renderer);  
    }
    return false;     
}
// Show frames animation - Check Game Over
void ShowFrame_CheckGameOver(MainObject &main_, ExplosionObject* explod, TextObject &Subtr_mark_game,
                            PlayerPower &life_player, unsigned int &die_nums, unsigned int mark_value_game, 
                            unsigned int time, bool &is_quit, bool &is_playagain){
    Mix_PlayChannel(0,g_sound_explosion,0);
    main_.Set_x_step_y_step(Speed_deafault_mainobject_x, Speed_deafault_mainobject_Y); // set default speed
    amount_bullet_main_object = 1; // set default bullet
    for(int ex = 0 ; ex < number_frame_ ; ex++){
        int x_pos = main_.GetRect().x + main_.GetRect().w*0.5 - 0.5*EXP_WIDTH;
        int y_pos = main_.GetRect().y + main_.GetRect().w*0.5 - 0.5*EXP_HEIGHT;
        SDL_Delay(175);
        explod->set_frame(ex);
        explod->SetRect(x_pos,y_pos);
        explod->RenderEx(renderer,NULL);
        Subtr_mark_game.SetText("-10");
        Subtr_mark_game.loadFromRenderedText(Subtr_mark,renderer);
        Subtr_mark_game.RenderText(renderer, main_.GetRect().x + 50 , main_.GetRect().y - 50);
        SDL_RenderPresent(renderer);
    }
    SDL_Delay(500);
    if(die_nums <= 2){
        main_.SetRect(mainobject_Pos_X_Start,mainobject_Pos_Y_Start);
        life_player.Decrease();
        life_player.DisplayLife(renderer);
    }
    // Check game over
    else 
        if(GameOver(mark_value_game,highest_score,time)) is_quit = true;     
        else is_playagain = true;
    SDL_RenderPresent(renderer);
}
// Main
int main(int argc, char* argv[])
{
    std::fstream file ("highestscore.txt"); // take highest score
    file >> highest_score;
    srand(time(NULL));
    initSDL(window, renderer);
    Init_Audio();
    InitSound();
    // Init MainObject, Background
    BaseObject g_background;
    InitBackground(g_background);
    MainObject g_mainobject;
    InitMainObject(g_mainobject);

    // Init ThreatObject
    ThreatObject * p_threat_list = new ThreatObject[Amount_Threat];
    Init_ThreatObject(p_threat_list,Amount_Threat);
    
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderClear(renderer);
    // Init ExplosionObject
    ExplosionObject* EXP_main = new ExplosionObject;
    EXP_main->LoadIMG("res/file anh/merge_from_ofoct.png",renderer);
    EXP_main->set_clip();

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

    // Init support Object
    SupportObject* list_object_support = new SupportObject[Amount_Support_Object];
    Init_Support_Object(list_object_support);
    
    SupportObject life_object_support;
    life_object_support.LoadIMG("res/file anh/star_2.png", renderer);
    Init_Items_Support_Object(life_object_support, speed_life_support_default);

    SupportObject Speed_increase_support;
    Speed_increase_support.LoadIMG("res/file anh/speed_sp.png", renderer);
    Init_Items_Support_Object(Speed_increase_support, speed_life_support_default);

    SupportObject Bullet_increase_support;
    Bullet_increase_support.LoadIMG("res/file anh/bullet_sp.png", renderer);
    Init_Items_Support_Object(Bullet_increase_support, speed_life_support_default);

    //Show Menu
    BaseObject menu_show;
    int ret_menu = Show_Menu(renderer,menu_show, menu_font_text);
    if(ret_menu == 1) is_quit = true;
    unsigned int step_time_menu = SDL_GetTicks()/1000;
    // Path flow
    while(!is_quit){
        SDL_RenderClear(renderer);   
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                is_quit = true;
                break;
            }
            if(event.type == SDL_KEYDOWN){
                switch(event.key.keysym.sym){
                    case SDLK_ESCAPE:
                        time_menu_stop = time_game; // Time - Stop
                        ret_menu = Show_Menu(renderer,menu_show, menu_font_text);
                        if(ret_menu == 1) is_quit = true;
                        step_time_menu = SDL_GetTicks()/1000 - time_menu_stop;
                        break;
                    // Mainobject moves right , load new image
                    case SDLK_RIGHT: g_mainobject.LoadIMG("res/file anh/spaceship02_fix_2.png",renderer); break;
                    case SDLK_d: g_mainobject.LoadIMG("res/file anh/spaceship02_fix_2.png",renderer); break;
                    case SDLK_1:
                        //If there is no music playing
                        if( Mix_PlayingMusic() == 0 )
                        {
                            //Play the music
                            Mix_VolumeMusic(30);
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
                    default: break;
                }
            }
            else if(event.type == SDL_KEYUP){
                switch(event.key.keysym.sym){
                    case SDLK_RIGHT: g_mainobject.LoadIMG("res/file anh/spaceship02_fix.png",renderer); break;
                    case SDLK_d: g_mainobject.LoadIMG("res/file anh/spaceship02_fix.png",renderer); break;
                    default: break;
                }
            }
            g_mainobject.HandleInputAction(event,renderer,g_sound_bullet,gMusic);
        }
        // Render 1 background, run screen
        if(is_run_screen){
            bkgn_x -= speed_run_screen;
            if(bkgn_x <= - (WIDTH_BACKGROUND - SCREEN_WIDTH)){
                bkgn_x = 0 ;
            }
            g_background.SetRect(bkgn_x,0);
            g_background.Render(renderer,NULL);
        }
        // Handle mainobject
        g_mainobject.HandMove();
        g_mainobject.Render(renderer,NULL);
        g_mainobject.Set_Amount_Bullet(amount_bullet_main_object);
        g_mainobject.Display_bullet(renderer);
        // Render player life
        life_player.DisplayLife(renderer);

    //Handling game timelines
        // increase speed's threats, speed threat bullet
        for(int t = 0 ; t < Amount_Threat ; t++){
            ThreatObject* p_threat = (p_threat_list + t);
            p_threat->Set_x_val(Speed_Threat_default + time_game/12); 
            p_threat->Upgrade_speed_Bullet();
        }
        if(time_game > 5){
            for(int list_ob = 0 ; list_ob < Amount_Support_Object ; list_ob++){
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
                    Subtr_Mark_game.RenderText(renderer, g_mainobject.GetRect().x + 50 , g_mainobject.GetRect().y - 50);
                    Mix_PlayChannel(0,g_sound_eat_sp_object,0);
                }
            }
            // Speed - support      
            if(time_game % 29 == 0) Init_Items_Support_Object(Speed_increase_support, speed_life_support_default);
            Speed_increase_support.Handle_life_support_Move();
            Speed_increase_support.Render(renderer, NULL);
            if(Speed_increase_support.CheckCollision(Speed_increase_support.GetRect(), g_mainobject.GetRect()) ){
                Init_Items_Support_Object(Speed_increase_support, 0);
                g_mainobject.Upgrade_speed_mainobject(1);
                Mix_PlayChannel(0,g_sound_eat_sp_object,0);
            }
            if(time_game >= 10){
                // Star - increase life 
                if(time_game % 35 == 0) Init_Items_Support_Object(life_object_support, speed_life_support_default);
                life_object_support.Handle_life_support_Move();
                life_object_support.Render(renderer,NULL);
                bool check_collid_life_main = life_object_support.CheckCollision(life_object_support.GetRect(), g_mainobject.GetRect());
                if(check_collid_life_main && die_nums > 0){
                    die_nums--;
                    life_player.Increase();
                    life_player.DisplayLife(renderer);
                    Init_Items_Support_Object(life_object_support, 0);
                    Mix_PlayChannel(0,g_sound_eat_sp_object,0);
                    SDL_RenderPresent(renderer);
                }
            }
            // Bullet - support
            if(time_game >= 15){
                if(time_game % 39 == 0) Init_Items_Support_Object(Bullet_increase_support, speed_life_support_default);
                Bullet_increase_support.Handle_life_support_Move();
                Bullet_increase_support.Render(renderer, NULL);
                if(Bullet_increase_support.CheckCollision(Bullet_increase_support.GetRect(), g_mainobject.GetRect()) && amount_bullet_main_object < max_bullet_main){
                    Init_Items_Support_Object(Bullet_increase_support, 0);
                    amount_bullet_main_object++;
                    Mix_PlayChannel(0,g_sound_eat_sp_object,0);
                }
            }
        }
        // Run Threat
        for(int t = 0 ; t < Amount_Threat ; t++){
            ThreatObject* p_threat = (p_threat_list + t);
            p_threat->HandleMove(SCREEN_WIDTH,SCREEN_HEIGHT);
            p_threat->Render(renderer,NULL);
            p_threat->Makebullet(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);
            // Check Collision mainobject - threats
            bool check_col = p_threat->CheckCollision(g_mainobject.GetRect(),p_threat->GetRect());
            if(check_col){
                // After the collision, threats reset
                if(t == Amount_Threat - 1) p_threat->ResetThreat(SCREEN_WIDTH + t * 400, life_tank_threat_object); 
                else p_threat->ResetThreat(SCREEN_WIDTH + t * 400, life_threat_object);
                if(mark_value_game > 10) mark_value_game -= 10; // Collision - decrease points
                die_nums ++;
                ShowFrame_CheckGameOver(g_mainobject, EXP_main, Subtr_Mark_game,
                                        life_player, die_nums, mark_value_game, 
                                        time_game, is_quit, is_playagain);
            }
            // Handling threat's bullets on mainobject
            std::vector<BulletObject*> threat_bullet_list = p_threat->Get_bullet_list();
            for(int k = 0 ; k < threat_bullet_list.size(); k++){
                BulletObject* p_bullet = threat_bullet_list.at(k);
                if(p_bullet){
                    bool check_col = p_bullet->CheckCollision(p_bullet->GetRect(),g_mainobject.GetRect());
                    if(check_col == true){
                        if(mark_value_game > 10) mark_value_game -= 10;
                        p_threat->Removebullet_Threat(k);
                        die_nums++;
                        ShowFrame_CheckGameOver(g_mainobject, EXP_main, Subtr_Mark_game,
                                                life_player, die_nums, mark_value_game, 
                                                time_game, is_quit, is_playagain);
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
                            p_threat->Decrease_Life();
                            g_mainobject.Removebullet(stt,k); // delete mainobject's bullets
                            if(p_threat->Getlife_() == 0){
                                mark_value_game++; // Kill enemies - earn point
                                if(t == Amount_Threat - 1){
                                    p_threat->LoadIMG("res/file anh/ship_enemy/boss_ship_1.png", renderer);
                                    p_threat->setSize(WIDTH_THREAT_TANK, HEIGHT_THREAT_TANK);
                                    p_threat->ResetThreat(SCREEN_WIDTH + t * 400, life_tank_threat_object);
                                }
                                else{
                                    p_threat->LoadIMG(random_pics(),renderer);
                                    p_threat->setSize(WIDTH_THREAT,HEIGHT_THREAT);
                                    p_threat->ResetThreat(SCREEN_WIDTH + t * 400, life_threat_object);
                                }
                                Mix_PlayChannel(0,g_sound_explosion,0);
                            }
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
        time_game = SDL_GetTicks()/1000 - step_time_menu;
        std::string Time_present = val_time + std::to_string(time_game);
        Time_game.SetText(Time_present);
        Time_game.loadFromRenderedText(g_font_text,renderer);
        Time_game.RenderText(renderer, x_pos_render_time_text, y_pos_render_time_text);
        // Play Again
        if(is_playagain){
            // Delete All Bullets 
            for(int threats = 0 ; threats < Amount_Threat; threats++){
                ThreatObject* p_threat = (p_threat_list + threats);
                std::vector<BulletObject*> threat_bullet_list = p_threat->Get_bullet_list();
                for(int k = 0 ; k < threat_bullet_list.size(); k++){
                    BulletObject* p_bullet = threat_bullet_list.at(k);
                    if(p_bullet) p_threat->Remove_Bullet_(k);
                }
                for(int i = 0 ; i < amount_bullet_main_object ; i++){
                    std::vector<BulletObject*> bullet_list = g_mainobject.GetbulletList(i);
                    for(int k = 0 ; k < bullet_list.size(); k++) g_mainobject.Removebullet(i,k);
                }
            }
            //Init All Objects And Values
            Init_ThreatObject(p_threat_list,Amount_Threat);
            InitMainObject(g_mainobject);
            InitBackground(g_background);
            life_player.Init();
            Init_Support_Object(list_object_support);
            Init_Items_Support_Object(life_object_support, speed_life_support_default);
            Init_Items_Support_Object(Speed_increase_support, speed_life_support_default);
            Init_Items_Support_Object(Bullet_increase_support, speed_life_support_default);
            bkgn_x = 0;
            die_nums = 0;
            mark_value_game = 0;
            amount_bullet_main_object = 1;
            step_time_menu = SDL_GetTicks()/1000;
            is_playagain = false;
        } 
        SDL_RenderPresent(renderer);
    }
    std::ofstream highest_score_game ("highestscore.txt"); // change highest score
    highest_score_game << highest_score;
    highest_score_game.close();
    Time_game.Free();
    mark_game.Free();
    delete [] p_threat_list;
    delete [] list_object_support;
    delete [] EXP_main;
    quitSDL(window, renderer);
    return 0;
}