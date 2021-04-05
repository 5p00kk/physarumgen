/*!
 \file
*/

#pragma once

#include <cmath>

#define PI 3.14159265

/* TODO Maybe use template for these vectors */

/*!
    \brief 2D unsigned int vector.
*/
struct s_ui_vec2
{
    unsigned int x;
    unsigned int y;
};
bool operator==(const s_ui_vec2& lhs, const s_ui_vec2& rhs);
bool operator!=(const s_ui_vec2& lhs, const s_ui_vec2& rhs);

/*!
    \brief 2D float vector.
*/
struct s_f_vec2
{
    float x;
    float y;
};
bool operator==(const s_f_vec2& lhs, const s_f_vec2& rhs);
bool operator!=(const s_f_vec2& lhs, const s_f_vec2& rhs);

/*!
    \brief Sample random boolean.
    \return Random boolean.
*/
bool random_bool();
/*!
    \brief Sample random angle.
    \return Float in [0-359] range with increment of 1.
*/
float random_angle();