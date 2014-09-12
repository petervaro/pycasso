/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                         File: src/geo/rectangle.c                          **
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
#include <stddef.h>   /* size_t */
#include <stdlib.h>   /* malloc() */
#include <stdbool.h>  /* bool, true, false */

/* Include internal pycasso headers */
#include "include/globalconst.h"
#include "include/session.h"

/*----------------------------------------------------------------------------*/
typedef struct
{
    size_t index;
} pycasso_geo_rectangle_Rectangle;



/*----------------------------------------------------------------------------*/
static const float ARCHE_VERTICES[] =
{
    -0.5f, -0.5f,
    -0.5f, +0.5f,
    +0.5f, +0.5f,
    +0.5f, -0.5f,
};



/*----------------------------------------------------------------------------*/
bool
pycasso_geo_rectangle_Rectangle_new(pycasso_geo_rectangle_Rectangle **rectangle,
                                    pycasso_session_Session *session)
{
    /* Create rectangle object */
    pycasso_geo_rectangle_Rectangle *_rectangle =
        malloc(sizeof(pycasso_geo_rectangle_Rectangle));
    if (!_rectangle)
    {
        /* Set rectangle and indicating failure */
        *rectangle = NULL;
        return false;
    }

    /* TODO: the number of properties and their component counts are already
             stored in their shader-properties (as inputs), so when the bit-mask
             is passed, the values are already have the kind of information it
             needs to "unpack" the passed property values (offset and color in
             this case). If it were python, this would probably be a dict
             instead of the bit-mask, the key would be the shader ID, and the
             values would be the actual values of the properties of the inputs
             of the given shadow. Design a better data-flow here !!! */
    pycasso_session_Session_add_instances(session,
           /* Bit ID of shader-program */ QUAD_COLOR | RECTANGLE | SOLID_COLOR,
           /* Number of arche vertices */ 4,
              /* Arche vertices (data) */ ARCHE_VERTICES,
           /* Number of new rectangles */ 1,
                     /* Property count */ 1,
           /* Property component count */ (size_t[]){4},
                              /* Color */ (const float*[]){(float[]){1.f, 1.f, 1.f, 1.f}},
                  /* Index of instance */ &_rectangle->index);

    /* NOTE: Probably the whole shader/inputs/properties/values should be a
             single packet, something like:

             typedef struct
             {
                 ... shader_id;
                 size_t property_count;
                 struct
                 {
                     ... property_id;
                     size_t component_count;
                     float values[];
                 } properties[];
             } ShaderPacket; */

    /* Set rectangle and return indicating success */
    *rectangle = _rectangle;
    return true;
}
/*
bool
pycasso_geo_rectangle_Rectangle_del(pycasso_geo_rectangle_Rectangle *rectangle)
{
    return true;
}

bool
pycasso_geo_rectangle_Rectangle_pos(pycasso_geo_rectangle_Rectangle *rectangle,
                                    float x,
                                    float y)
{
    return true;
}

bool
pycasso_geo_rectangle_Rectangle_pos_x(pycasso_geo_rectangle_Rectangle *rectangle,
                                      float x)
{
    return true;
}

bool
pycasso_geo_rectangle_Rectangle_pos_y(pycasso_geo_rectangle_Rectangle *rectangle,
                                      float y)
{
    return true;
}

bool
pycasso_geo_rectangle_Rectangle_dim(pycasso_geo_rectangle_Rectangle *rectangle,
                                    float width,
                                    float height)
{
    return true;
}

bool
pycasso_geo_rectangle_Rectangle_dim_width(pycasso_geo_rectangle_Rectangle *rectangle,
                                          float width)
{
    return true;
}

bool
pycasso_geo_rectangle_Rectangle_dim_height(pycasso_geo_rectangle_Rectangle *rectangle,
                                           float height)
{
    return true;
}

bool
pycasso_geo_rectangle_Rectangle_fill(pycasso_geo_rectangle_Rectangle *rectangle,
                                     pycasso_geo_Fill fill_type,
                                     float color_angle,
                                     size_t color_stop_count,
                                     const char **color_stop_values,
                                     float *color_stop_positions)
{
    return true;
}
*/
