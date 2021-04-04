#pragma once

#include <cmath>

#define PI 3.14159265

/* TODO Maybe use template here */
struct s_ui_vec2
{
    unsigned int x;
    unsigned int y;
};

struct s_f_vec2
{
    float x;
    float y;
};

bool random_bool();
s_f_vec2 dest_position(float x, float y, float angle, float distance);