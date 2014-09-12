/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                         File: include/_TMP_cshm.h                          **
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

#ifndef _TMP_CSHM_H_7777345746868554_
#define _TMP_CSHM_H_7777345746868554_

/* NOTE: TEMPORARY MACROS to work with the WIP static hash map object */

static bool
__cshm_compare_str_keys(const void *str1,
                        const void *str2,
                        size_t size)
{
    return !strncmp(str1, str2, size);
}

/* TEMPORARY MACROS to work with the WIP static hash map object */
#define _concat_underscore(token1, token2) token1##_##token2
#define concat_underscore(token1, token2) _concat_underscore(token1, token2)
#define HASH_MAP cutils_cshm_StaticHashMap_void_ptr_and_void_ptr
#define METHOD(func)  concat_underscore(HASH_MAP, func)
#define SUPPORT(type) concat_underscore(HASH_MAP, type)
#define SUPPORT_METHOD(type, func) concat_underscore(HASH_MAP, type##_##func)
#define COMPARE_KEYS __cshm_compare_str_keys

#endif /* _TMP_CSHM_H_7777345746868554_ */

/*
HASH_MAP *quad_color_vs_inputs;
METHOD(new)(&quad_color_vs_inputs, 128);


#define IN_PROJECTION_MAT      "projection_mat"
#define IN_VIEW_MAT            "view_mat"
#define IN_MODEL_MAT           "model_mat"
#define IN_VERTEX_COORDINATES  "vertex_coordinates"
#define IN_TEXTURE_COORDINATES "texture_coordinates"
#define IN_DIMENSIONS          "dimensions"
#define IN_RADIUSES            "radiuses"
#define IN_TEXTURE_SAMPLER     "texture_sampler"
#define IN_COLOR_BASE_POSITION "color_base_position"
#define IN_COLOR_STOP_POSITION "color_stop_position"
#define IN_COLOR_BASE_LOCATION "color_base_location"
#define IN_COLOR_STOP_LOCATION "color_stop_location"
#define IN_COLOR_ROTATION      "color_rotation"
#define IN_COLOR_POSITION      "color_position"

const char *input_names[] = {IN_PROJECTION_MAT,
                             IN_VIEW_MAT,
                             IN_MODEL_MAT,
                             IN_VERTEX_COORDINATES,
                             IN_TEXTURE_COORDINATES,
                             IN_DIMENSIONS,
                             IN_RADIUSES,
                             IN_TEXTURE_SAMPLER,
                             IN_COLOR_BASE_POSITION,
                             IN_COLOR_STOP_POSITION,
                             IN_COLOR_BASE_LOCATION,
                             IN_COLOR_STOP_LOCATION,
                             IN_COLOR_ROTATION,
                             IN_COLOR_POSITION};

const size_t input_name_sizes[] = {sizeof IN_PROJECTION_MAT,
                                   sizeof IN_VIEW_MAT,
                                   sizeof IN_MODEL_MAT,
                                   sizeof IN_VERTEX_COORDINATES,
                                   sizeof IN_TEXTURE_COORDINATES,
                                   sizeof IN_DIMENSIONS,
                                   sizeof IN_RADIUSES,
                                   sizeof IN_TEXTURE_SAMPLER,
                                   sizeof IN_COLOR_BASE_POSITION,
                                   sizeof IN_COLOR_STOP_POSITION,
                                   sizeof IN_COLOR_BASE_LOCATION,
                                   sizeof IN_COLOR_STOP_LOCATION,
                                   sizeof IN_COLOR_ROTATION,
                                   sizeof IN_COLOR_POSITION};

for (size_t i=0; i<(sizeof inputs / sizeof(char*)); i++)
    METHOD(add)(shader_input_layout_positions, COMPARE_KEYS,
                input_name_sizes[i], sizeof(size_t),
                input_names[i], &i));

*(size_t*)METHOD(get)(shader_input_layout_positions, COMPARE_KEYS,
                      sizeof IN_PROJECTION_MAT, IN_PROJECTION_MAT);
*/