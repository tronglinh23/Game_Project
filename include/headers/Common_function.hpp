
#pragma once
#include <windows.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
// Window title
    const std::string WINDOW_TITLE = "SDL2 _ SpaceGame";
//Screen
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_BPP = 32;
    const int speed_run_screen = 2;

// Font text - title
    // MenuText
    const int size_menu_text = 55;

        // title game    
        static TTF_Font* menu_font_text = NULL;
        const std::string font_menu_game = "res/font/xeros_theorem.ttf";
        const std::string title = "Save The Earth";
        const int pos_title_x = SCREEN_WIDTH/5;
        const int pos_title_y = 30;
        const int color_title_R = 0;
        const int color_title_G = 255;
        const int color_title_B = 255;
        const int color_title_change_R = 255;
        const int color_title_change_G = 255;
        const int color_title_change_B = 0;
        
        // Text Menu 1 : Play Game
        const int color_ItemText_R = 0;
        const int color_ItemText_G = 255;
        const int color_ItemText_B = 255;
        const int color_Change_ItemText_R = 255;
        const int color_Change_ItemText_G = 255;
        const int color_Change_ItemText_B = 0;

    //Mark
    static TTF_Font* g_font_text = NULL;
    const std::string font_mark_game = "res/font/V5PRC___.TTF";
    const std::string text("Mark: ");
    const int size_mark = 30;
    const int x_pos_render_mark_text = 500;
    const int y_pos_render_mark_text = 10;

    //Time_Text
    const std::string val_time("Time: ");
    const int size_time = 30;
    const int x_pos_render_time_text = SCREEN_WIDTH - 200;
    const int y_pos_render_time_text = 10;
    // Subtract mark text - collid
    static TTF_Font *Subtr_mark = NULL;
    const std::string subtr_mark_text = "res/font/Rabanera-outline-shadow.ttf";
    const int size_subtr_mark_text = 35;
    const int color_SubtrText_R = 0;
    const int color_SubtrText_G = 255;
    const int color_SubtrText_B = 30;

// Main Object
    const int mainobject_Pos_X_Start = 100;
    const int mainobject_Pos_Y_Start = 200;

// Explosion
    const int number_frame_ = 11;

// background
    const std::string pics_background = "res/file anh/6569652.png";
    const int WIDTH_BACKGROUND = 4800;
    const int HEIGHT_BACKGROUND = 600;

// Init default
    static SDL_Window* window = NULL;
    static SDL_Renderer* renderer = NULL;
    static SDL_Event event;

//Amount of THREAT_OBJECT
    const int Amount_Threat = 4;
    const int Speed_Threat_default = 6;

// transparent background
    const int COLOR_KEY_R = 0;
    const int COLOR_KEY_G = 255;
    const int COLOR_KEY_B = 255;

// AUDIO
    static Mix_Chunk* g_sound_bullet[2];
    static Mix_Chunk* g_sound_explosion = NULL;
    static Mix_Chunk* g_sound_ex_main = NULL;
    static Mix_Chunk* g_sound_eat_sp_object = NULL;
    static Mix_Chunk* g_sound_options_choose = NULL;
    static Mix_Music *gMusic = NULL; // Sound game
// Support Object
    const int Amount_Support_Object = 4;
    const std::string file_pics_support_object[] = {"res/Planets/planet1.png","res/Planets/planet2.png","res/Planets/planet3.png",
                                                    "res/Planets/planet4.png","res/Planets/planet5.png","res/Planets/planet6.png",
                                                    "res/Planets/planet7.png","res/Planets/planet10.png","res/Planets/planet11.png",
                                                    "res/Planets/planet12.png","res/Planets/planet13.png","res/Planets/planet14.png",
                                                    "res/Planets/planet15.png","res/Planets/planet16.png","res/Planets/planet17.png",
                                                    "res/Planets/planet18_0.png","res/Planets/planet19.png","res/Planets/planet20.png"};
    const int amount_pics_path = 18;    
    const int size_x_pics_sp = 45;
    const int size_y_pics_sp = 45;                
    // life_support_object
    const int speed_life_support_default = 10;


// Menu option 2
static TTF_Font *menu_options_text_2 = NULL;
const std::string font_menu_text = "res/font/V5PRC___.TTF";
const int size_text_menu_2 = 30;
const int x_pos_menu_options = SCREEN_WIDTH/4 + 80;
const int y_pos_menu_options = SCREEN_HEIGHT/4 + 30;
const int color_items_menu_2_R= 2;
const int color_items_menu_2_G = 25;
const int color_items_menu_2_B = 61;



// 
