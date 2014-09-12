// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                         File: src/_DEL_geo/rect.c                          //
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
#include <stdlib.h>  // malloc(), free(), exit()

// Include pycasso headers
#include "../../include/allheaders.h"
#include "../../include/debug.h"


/*----------------------------------------------------------------------------*/
pycasso_Rectangle *
pycasso_geo_rect_init(pycasso_StaticResources *resources)
{
    // Create rectangle instance
    pycasso_Rectangle *rectangle = malloc(sizeof(pycasso_Rectangle));
    if (!rectangle)
    {
        printf("Couldn't allocated memory for a new rectangle\n");
        exit(EXIT_FAILURE);
    }

    // Create instance struct
    pycasso_GeometryInstance *instance = pycasso_admin_init_instance(resources);
    instance->type = PYCASSO_GEO_RECTANGLE;
    instance->geometry = rectangle;

    // Store essential management pointers
    rectangle->resources = resources;
    rectangle->instance  = instance;

    return rectangle;
}

/*----------------------------------------------------------------------------*/
void
pycasso_geo_rect_delete(pycasso_Rectangle *rectangle)
{
    free(rectangle);
    return;
}

/*----------------------------------------------------------------------------*/
void
pycasso_geo_rect_draw(pycasso_Rectangle *rectangle)
{
    return;
}

/*----------------------------------------------------------------------------*/
#define RECT_NUM_SHADERS 4
void
pycasso_geo_rect_init_color(pycasso_StaticResources *resources)
{
    // Create and store textured rectangle shader program
    GLuint program_id;
    GLuint shaders[] = {resources->vs->textured,
                        resources->fs->main_fs,
                        resources->fs->shape_rectangle_fs,
                        resources->fs->fill_solid_color_fs};
    pycasso_shaders_create_and_load_program(&program_id, RECT_NUM_SHADERS, shaders);
    // Create a program struct
    pycasso_ShaderProgram *program = malloc(sizeof(pycasso_ShaderProgram));
    if (!program)
    {
        printf("Couldn't allocated memory for a new program of rectangle\n");
        exit(EXIT_FAILURE);
    }
    // Set id
    program->id = program_id;
    // Get and set locations of the matrices
    program->projection_matrix_location = glGetUniformLocation(program_id, "projection_mat");
    program->view_matrix_location = glGetUniformLocation(program_id, "view_mat");
    program->model_matrix_location = glGetUniformLocation(program_id, "model_mat");
    // Get and set location of vertices and textures
    program->position_location = glGetAttribLocation(program_id, "vertex_coordinates");
    program->texture_location  = glGetAttribLocation(program_id, "texture_coordinates");
    // Store attached shaders
    program->num_of_shaders = RECT_NUM_SHADERS;
    program->shaders = (GLuint *)malloc(program->num_of_shaders * sizeof(GLuint));
    if (!program->shaders)
    {
        printf("Couldn't allocated memory for shader IDs of rectangle\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<RECT_NUM_SHADERS; i++) program->shaders[i] = shaders[i];

    // Store the newly created program
    rectangle->program = program;

    // Start using the program
    glUseProgram(program->id);

    // Create arrays and buffers
    glGenVertexArrays(1, &rectangle->vertex_array);
    glGenBuffers(1, &rectangle->vertex_buffer);
    glGenBuffers(1, &rectangle->element_buffer);

    // Set view and model matrix
    mat4x4_identity(rectangle->view_matrix);   // World space -> Camera space
    mat4x4_identity(rectangle->model_matrix);  // Local space -> World space

    // Use VAO
    glBindVertexArray(rectangle->vertex_array);
    glEnableVertexAttribArray(program->position_location);
    glEnableVertexAttribArray(program->texture_location);
    glBindVertexArray(0);

    // Set properties of instance
    pycasso_geo_rectangle_dimension(rectangle, width, height);
    pycasso_geo_rectangle_position(rectangle, x, y);
    pycasso_geo_rectangle_texture(rectangle, texture_path);
    pycasso_geo_rectangle_corner_radiuses(rectangle, corner_radiuses);

    // Bind fragment data output
    glBindFragDataLocation(program->id, 0, "fragment");
    // Clean up
    glUseProgram(0); // Don't use any program
}

/*----------------------------------------------------------------------------*/
void
pycasso_geo_rect_init_texture(void)
{
    return;
}
