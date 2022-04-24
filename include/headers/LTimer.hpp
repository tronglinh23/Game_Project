#pragma once
#include "Common_function.hpp"

class Ltimer
{
public:
    Ltimer();
    ~Ltimer();
    void start();
    void pause();
    void stop();
    void unpause();

    int get_tick();
    bool is_paused() {return is_paused_;}
    bool is_started() {return is_started_;}
    int Get_starttick() {return start_tick_;};
private:
    int start_tick_;
    int pause_stick_;

    bool is_paused_;
    bool is_started_;
};