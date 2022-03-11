
#pragma once
#include <windows.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
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
