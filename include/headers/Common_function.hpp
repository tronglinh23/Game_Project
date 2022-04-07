
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

// Font text - title
    // MenuText
    const int size_menu_text = 50;
        // title game
        
        static TTF_Font* menu_font_text = NULL;
        const std::string font_menu_game = "res/font/xeros_theorem.ttf";
        const std::string title = "Space Game";
        const int pos_title_x = SCREEN_WIDTH/3;
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
    const std::string font_mark_game = "res/font/comicate.ttf";
    const std::string text("Mark: ");
    const int size_mark = 30;

    //Time_Text
    const std::string val_time("Time: ");
    const int size_time = 30;
// Main Object
    const int mainobject_Pos_X_Start = 100;
    const int mainobject_Pos_Y_Start = 200;

// Explosion

// background
    // const int amount_pics_background = 4;
    // static const std::string pics_background[] = {"res/file anh/1.jpg",
    //                                               "res/file anh/2.jpg",
    //                                               "res/file anh/3.jpg",
    //                                               "res/file anh/4.jpg"};

    const std::string pics_background = "res/file anh/6569652.png";
    const int WIDTH_BACKGROUND = 4800;
    const int HEIGHT_BACKGROUND = 600;
// Init default
    static SDL_Window* window = NULL;
    static SDL_Renderer* renderer = NULL;
    static SDL_Event event;
//Amount of THREAT_OBJECT
    const int Amount_Threat = 4;


// transparent background
    const int COLOR_KEY_R = 0;
    const int COLOR_KEY_G = 255;
    const int COLOR_KEY_B = 255;

// AUDIO
    static Mix_Chunk* g_sound_bullet[2];
    static Mix_Chunk* g_sound_explosion = NULL;
    static Mix_Chunk* g_sound_ex_main = NULL;
    static Mix_Music *gMusic = NULL; // Sound game