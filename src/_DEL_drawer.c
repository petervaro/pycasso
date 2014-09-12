/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                          File: src/_DEL_drawer.c                           **
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







/*----------------------------------------------------------------------------*/
typedef struct pycasso_drawer_shaders
{

} pycasso_drawer_Shaders;



/*----------------------------------------------------------------------------*/
bool
pycasso_drawer_Shaders_new(pycasso_drawer_Shaders *shaders)
{

    return true;
}

typedef GLfloat coord[3];
typedef GLfloat color[3];

some_func()
{
    #define INITIAL_COUNT 64

    /* Create array to store coordinates */
    DynamicArray_void_ptr *coords;
    if (!new(&coords, sizeof(coord), INITIAL_COUNT, NULL))
        return false;

    /* Create array to store color values */
    DynamicArray_void_ptr *colors;
    if (!new(&coords, sizeof(color), INITIAL_COUNT, NULL))
        return false;
}


_draw(pycasso_drawer_Shaders *shaders)
{
    /* Clear color => create background */
    static const GLfloat clear_color[] = {.46f, .71f, .67f, 1.f};
    glClearBufferfv(GL_COLOR, 0, clear_color);

    glDrawArraysInstanced(GL_TRIANGLE_FAN,
/* First index in buff */ 0,
 /* Number of vertices */ rsc->vertices_count,
/* Number of instances */ rsc->instance_count);
}
