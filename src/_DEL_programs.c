// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                         File: src/_DEL_programs.c                          //
//                                                                            //
//  For more information about the project, visit <http://www.pycasso.org>.   //
//                       Copyright (C) 2014 Peter Varo                        //
//                                                                            //
//  This program is free software: you can redistribute it and/or modify it   //
//   under the terms of the GNU General Public License as published by the    //
//       Free Software Foundation, either version 3 of the License, or        //
//                    (at your option) any later version.                     //
//                                                                            //
//    This program is distributed in the hope that it will be useful, but     //
//         WITHOUT ANY WARRANTY; without even the implied warranty of         //
//            MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.            //
//            See the GNU General Public License for more details.            //
//                                                                            //
//     You should have received a copy of the GNU General Public License      //
//     along with this program, most likely a file in the root directory,     //
//        called 'LICENSE'. If not, see <http://www.gnu.org/licenses>.        //
//                                                                            //
//////////////////////////////////////////////////////////////////////// INFO //

// Include standrad headers
#include <stdio.h>   // printf()
#include <stdlib.h>  // malloc(), free(), exit(), EXIT_FAILURE

// Include pycasso headers
#include "../../include/allheaders.h"
#include "../../include/debug.h"


/*----------------------------------------------------------------------------*/
static inline int
_pycasso_programs_load_solid_color_rectangle(GLuint quad_vs,
                                             GLuint main_fs,
                                             GLuint shape_fs,
                                             GLuint fill_fs)
{
    return 0;
}


/*----------------------------------------------------------------------------*/
void
pycasso_programs_load_programs(pycasso_StaticResources *resources, ...)
{
    // Load and store vertex shader resources
    pycasso_VertShaders *vs = malloc(sizeof(pycasso_VertShaders));
    const char *vs_type_name = "pycasso_VertShaders";
    if (!vs)
    {
        printf("Couldn't allocated memory for '%s'.\n", vs_type_name);
        goto Error_Allocating_Storage_For_Shaders;
    }
    const char *vs_shaders_paths[] = {
        PYCASSO_SHADER_PATH PYCASSO_VERTEX_PATH "quad_color.vs",
        PYCASSO_SHADER_PATH PYCASSO_VERTEX_PATH "quad_texture.vs",
        PYCASSO_SHADER_PATH PYCASSO_VERTEX_PATH "sys_grid.vs",
    };
    pycasso_shaders_load_and_compile_shaders(vs,
                                             sizeof(pycasso_VertShaders)/sizeof(GLuint),
                                             vs_shaders_paths,
                                             sizeof(vs_shaders_paths)/sizeof(char*),
                                             vs_type_name,
                                             GL_VERTEX_SHADER);

    // Load and store color fill shader resources
    pycasso_FragShaders *fs = malloc(sizeof(pycasso_FragShaders));
    const char *fs_type_name = "pycasso_FragShaders";
    if (!fs)
    {
        printf("Couldn't allocated memory for '%s'.\n", fs_type_name);
        goto Error_Allocating_Storage_For_Shaders;
    }
    const char* fs_shaders_paths[] = {
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_solid_color.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_linear_gradient.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_radial_gradient.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_conical_gradient.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_texture.fs",

        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "shape_rectangle.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "shape_rounded_rectangle.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "shape_circle.fs",

        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "main.fs",

        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "sys_grid.fs",
    };
    pycasso_shaders_load_and_compile_shaders(fs,
                                             sizeof(pycasso_FragShaders)/sizeof(GLuint),
                                             fs_shaders_paths,
                                             sizeof(fs_shaders_paths)/sizeof(char*),
                                             fs_type_name,
                                             GL_FRAGMENT_SHADER);




    _pycasso_programs_load_solid_color_rectangle(vs, fs);
    return;

    Error_Allocating_Storage_For_Shaders:
        exit(EXIT_FAILURE);
}

