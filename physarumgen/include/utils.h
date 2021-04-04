#pragma once

#include <cmath>

#define PI 3.14159265

/* TODO Maybe use template here */
struct s_ui_vec2
{
    unsigned int x;
    unsigned int y;
};
bool operator==(const s_ui_vec2& lhs, const s_ui_vec2& rhs);
bool operator!=(const s_ui_vec2& lhs, const s_ui_vec2& rhs);

struct s_f_vec2
{
    float x;
    float y;
};
bool operator==(const s_f_vec2& lhs, const s_f_vec2& rhs);
bool operator!=(const s_f_vec2& lhs, const s_f_vec2& rhs);

bool random_bool();
float random_angle();