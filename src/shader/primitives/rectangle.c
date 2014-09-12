/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                  File: src/shader/primitives/rectangle.c                   **
**                                                                            **
**  For more information about the project, visit <http://www.pycasso.org>.   **
**                       Copyright (C) 2014 Peter Varo                        **
**                                                                            **
**  This program is free software: you can redistribute it and/or modify it   **
**   under the terms of the GNU General Public License as published by the    **
**       Free Software Foundation, either version 3 of the License, or        **
**                    (at your option) any later version.                     **
**                                                                            **
**    This program is distributed in the hope that it will be useful, but     **
**         WITHOUT ANY WARRANTY; without even the implied warranty of         **
**            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            **
**            See the GNU General Public License for more details.            **
**                                                                            **
**     You should have received a copy of the GNU General Public License      **
**     along with this program, most likely a file in the root directory,     **
**        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        **
**                                                                            **
************************************************************************ INFO */

/* Include standard headers */
#include <stdbool.h>  /* bool, true, false */

/* Include cutils headers */
#include <cutils/call.h>

/* Include internal pycasso headers */
#include "include/shader/primitive.h"

typedef struct pycasso_shader_primitive_Primitive pycasso_shader_primitives_Rectangle;



/*----------------------------------------------------------------------------*/
static const char *VERT_SHADER = "                           \
#version 150 core                                            \n\
                                                             \n\
// Inputs                                                    \n\
in vec3 coord;                                               \n\
in vec3 offset;                                              \n\
in vec3 color;                                               \n\
                                                             \n\
// Passing color value to fragment shader                    \n\
out Fragment                                                 \n\
{                                                            \n\
    vec3 color;                                              \n\
                                                             \n\
} fragment;                                                  \n\
                                                             \n\
void main()                                                  \n\
{                                                            \n\
    gl_Position = vec4(coord + offset, 1.0);                 \n\
    fragment.color = color;                                  \n\
}                                                            \n";



/*----------------------------------------------------------------------------*/
static const char *FRAG_SHADER = "                           \
#version 150 core                                            \n\
                                                             \n\
// Passed color value from vertex shader                     \n\
in Fragment                                                  \n\
{                                                            \n\
    vec3 color;                                              \n\
                                                             \n\
} fragment;                                                  \n\
                                                             \n\
// Outputs                                                   \n\
out vec4 frag_color;                                         \n\
                                                             \n\
void main()                                                  \n\
{                                                            \n\
    frag_color = vec4(fragment.color, 1.0);                  \n\
}                                                            \n";



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_primitives_Rectangle_new(pycasso_shader_primitives_Rectangle **rectangle)
{
    #define UNIT .15f
    static const GLfloat original_coords[] = {-1.f*UNIT, -1.f*UNIT, 0.f,
                                              -1.f*UNIT,  1.f*UNIT, 0.f,
                                               1.f*UNIT,  1.f*UNIT, 0.f,
                                               1.f*UNIT, -1.f*UNIT, 0.f};

    #define VERT_COUNT ((sizeof(original_coords) / sizeof(GLfloat)) / 2)
    /* Create shader primitive */
    if (!pycasso_shader_primitive_Primitive_new(
        (pycasso_shader_primitive_Primitive **)rectangle,
                                               VERT_SHADER,
                                               FRAG_SHADER,
                                               original_coords,
                                               VERT_COUNT))
    {
        #undef  EXCEPTION_MESSAGE
        #define EXCEPTION_MESSAGE "Rectangle: shader primitive creation failed"
        raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);
        return false;
    }
    return true;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_primitives_Rectangle_del(pycasso_shader_primitives_Rectangle *rectangle)
{
    return pycasso_shader_primitive_Primitive_del(
        (pycasso_shader_primitive_Primitive *)rectangle);
}



/*----------------------------------------------------------------------------*/
void
pycasso_shader_primitives_Rectangle_append(pycasso_shader_primitives_Rectangle *rectangle)
{
    /* NOTE: This is for test purpose only */
    pycasso_shader_primitive_Primitive_append(
        (pycasso_shader_primitive_Primitive *)rectangle,

        3,

        (GLfloat[]){ 0.f*UNIT,  0.f*UNIT,  0.1f,
                    -.5f*UNIT, -1.f*UNIT,  0.5f,
                     1.f*UNIT,  1.5f*UNIT, 0.25f},

        (GLfloat[]){1.f, 1.f, 1.f,
                    0.f, 1.f, 1.f,
                    1.f, 1.f, 0.f});
}



/*----------------------------------------------------------------------------*/
void
pycasso_shader_primitives_Rectangle_draw(pycasso_shader_primitives_Rectangle *rectangle)
{
    pycasso_shader_primitive_Primitive_draw(
        (pycasso_shader_primitive_Primitive *)rectangle);
}
