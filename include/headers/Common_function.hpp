
#pragma once
#include <windows.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
// Window title
    const std::string WINDOW_TITLE = "SDL2 _ GAME CPP";
// Font text - title
    //Mark
    static std::string font_mark_game = "res/font/comicate.ttf";
    static std::string text("Mark: ");
    const int size_mark = 30;

    //Time_Text
    static std::string val_time("Time: ");
    const int size_time = 30;

// Main Object
    const int mainobject_Pos_X_Start = 100;
    const int mainobject_Pos_Y_Start = 200;

// Explosion

// background
    const int WIDTH_BACKGROUND = 4800;
    const int HEIGHT_BACKGROUND = 600;
// Init default
    static SDL_Window* window = NULL;
    static SDL_Renderer* renderer = NULL;
    static SDL_Event event;
//Amount of THREAT_OBJECT
    const int Amount_Threat = 3;
//Screen
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 600;
    const int SCREEN_BPP = 32;

// transparent background
    const int COLOR_KEY_R = 0;
    const int COLOR_KEY_G = 255;
    const int COLOR_KEY_B = 255;

// AUDIO
    static Mix_Chunk* g_sound_bullet[2];
    static Mix_Chunk* g_sound_explosion = NULL;
    static Mix_Chunk* g_sound_ex_main = NULL;
    static Mix_Music *gMusic = NULL; // Sound game