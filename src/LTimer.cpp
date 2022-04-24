#include "LTimer.hpp"

Ltimer::Ltimer(){
    start_tick_ = 0;
    pause_stick_ = 0;
    is_paused_ = false;
    is_started_ = false;
}

Ltimer::~Ltimer(){

}

void Ltimer::start(){
    is_started_ = true;
    is_paused_ = false;
    start_tick_ = SDL_GetTicks();
    pause_stick_ = 0;
}

void Ltimer::stop(){
    is_started_ = false;
    is_paused_ = false;
    // clear all values
    start_tick_ = 0;
    pause_stick_ = 0;
}

void Ltimer::pause(){
    if(is_started_ && !is_paused_){
        is_paused_ = true;
        pause_stick_ = SDL_GetTicks() - start_tick_;
        start_tick_ = 0;
    }
}

void Ltimer::unpause(){
    if(is_started_ && is_paused_){
        is_paused_ = false;
        start_tick_ = SDL_GetTicks() - pause_stick_;
        pause_stick_ = 0;
    }
}

int Ltimer::get_tick(){
    Uint32 time = 0;

    if(is_started_){
        if(is_paused_){
            time = pause_stick_;
        }
        else{
            time = SDL_GetTicks() - start_tick_;
        }
    }
    return time;
}
