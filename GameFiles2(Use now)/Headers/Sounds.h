#pragma once
#include "include.h"
struct Sounds
{
    int k = 0;
    Music bgmusic;
    SoundBuffer buf1, buf2, buf3, buf4;
    Sound so, so2, so4, so5, so6, so7, so8, so9, so10, so11, so12, so13;
    void LoadMusic(int n);
    void music(int n);
    void change_option_Sound();
    void select_option_Sound();
    void falling_sound(int player);
    void clock_ring_sound();
    void hurry_up_sound();
    void Sweet_sound();
    void Good_sound();
    void gonna_fall(int player);
    void jump(int player);
    void gameover();
    void cheer();
    void rotation_sound(int player);

};