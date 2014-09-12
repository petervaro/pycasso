// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                         File: src/_DEL_geo/grid.c                          //
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

// Include standard headers
#include <stdlib.h>    // malloc() free()
#include <stdbool.h>   // false
#include <math.h>      // fmax()
// Include pycasso headers
#include "../../include/allheaders.h"
#include "../../include/debug.h"

/*----------------------------------------------------------------------------*/
pycasso_Grid *
pycasso_geo_grid_init(pycasso_StaticResources *resources,
                      GLfloat h_space,
                      GLfloat v_space,
                      GLfloat color[4])
{
    // Create grid instance
    pycasso_Grid *grid = malloc(sizeof(pycasso_Grid));
    if (!grid)
    {
        printf("Couldn't allocated memory for a new grid\n");
        exit(EXIT_FAILURE);
    }

    // Create instance struct
    pycasso_GeometryInstance *instance = pycasso_admin_init_instance(resources);
    instance->type = PYCASSO_GEO_GRID;
    instance->geometry = grid;

    // Store essential management pointers
    grid->resources = resources;
    grid->instance  = instance;

    // Create and store colored grid shader program
    GLuint program_id;
    GLuint shaders[] = {resources->vertex_shaders->grid,
                        resources->shaders->grid};
    pycasso_shaders_create_and_load_program(&program_id, 2, shaders);

    // Create a program struct
    pycasso_ShaderProgram *program = malloc(sizeof(pycasso_ShaderProgram));
    if (!program)
    {
        printf("Couldn't allocated memory for a new program of grid\n");
        exit(EXIT_FAILURE);
    }
    // Set id
    program->id = program_id;
    // Get and set locations of the matrices
    program->projection_matrix_location = glGetUniformLocation(program_id, "projection_mat");
    program->view_matrix_location = glGetUniformLocation(program_id, "view_mat");
    program->model_matrix_location = glGetUniformLocation(program_id, "model_mat");
    // Get and set location of vertices
    program->position_location = glGetAttribLocation(program_id, "vertex_coordinates");
    // Store attached shaders
    program->num_of_shaders = 2;
    program->shaders = (GLuint *)malloc(program->num_of_shaders * sizeof(GLuint));
    if (!program->shaders)
    {
        printf("Couldn't allocated memory for shader IDs of grid\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<2; i++) program->shaders[i] = shaders[i];

    // Store the newly created program
    grid->program = program;
    // Start using the program
    glUseProgram(program->id);

    // Create arrays and buffers
    glGenVertexArrays(1, &grid->vertex_array);
    glGenBuffers(1, &grid->vertex_buffer);
    glGenBuffers(1, &grid->element_buffer);
    // Set view matrix
    mat4x4_identity(grid->view_matrix);   // World space -> Camera space
    mat4x4_identity(grid->model_matrix);

    // Use VAO
    glBindVertexArray(grid->vertex_array);
    glEnableVertexAttribArray(program->position_location);
    glBindVertexArray(0);
    // Set properties of instance
    pycasso_geo_grid_position_and_dimensions(grid, 0.f, 0.f);
    pycasso_geo_grid_spaces(grid, h_space, v_space);
    pycasso_geo_grid_color(grid, color);
    // Bind fragment data output
    glBindFragDataLocation(program->id, 0, "fragment");
    // Clean up
    glUseProgram(0); // Don't use any program
    // Return new instance
    return grid;
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_grid_delete(pycasso_Grid *grid)
{
    // Detach shaders, free shader storage, delete program, free program
    pycasso_shaders_unload_and_delete_program(grid->program);

    // Delete buffers
    glDeleteBuffers(1, &grid->vertex_buffer);
    glDeleteBuffers(1, &grid->element_buffer);
    glDeleteVertexArrays(1, &grid->vertex_array);

    // Delete grid from resources
    pycasso_admin_delete_instance(grid->instance,
                                  grid->resources);
    // Clean up
    free(grid);
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_grid_draw(pycasso_Grid *grid,
                      GLfloat width,
                      GLfloat height)
{
    // Update view_port dimensions
    pycasso_geo_grid_update_dimensions(grid, width, height);
    pycasso_geo_grid_spaces(grid, grid->h_space, grid->v_space);

    // Get program and use it
    glUseProgram(grid->program->id);

    // Send projection matrix
    glUniformMatrix4fv(grid->program->projection_matrix_location,
                       1,
                       false,
                       (GLfloat *)grid->resources->projection_matrix);

    // Make buffer objects current, draw them
    glBindVertexArray(grid->vertex_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid->element_buffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

    // Cleanup
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind
    glBindVertexArray(0); //unbind
    glUseProgram(0);
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_grid_update_dimensions(pycasso_Grid *grid,
                                   GLfloat width,
                                   GLfloat height)
{
    // Normalize value to [0.f .. 1.f]
    width  = fabs(width);
    height = fabs(height);
    GLfloat max = fmax(width, height);
    GLfloat w = width/max;
    GLfloat h = height/max;

    // Update OpenGL values
    GLfloat buffer_data[] = {  w, h,     // A
                               0, h,     // B
                               0, 0,     // C
                               w, 0  };  // D

    // Start using program
    glUseProgram(grid->program->id);
    // Set VAO
    glBindVertexArray(grid->vertex_array); // Make it current
    glBindBuffer(GL_ARRAY_BUFFER, grid->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(grid->program->position_location,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          2*sizeof(GLfloat),
                          (GLvoid *)NULL);

    // Calculate and send view matrix
    mat4x4_ortho(grid->view_matrix,
     /* Left */  -1.f/max,
    /* Right */  +1.f/max,
   /* Bottom */  -1.f/max,
      /* Top */  +1.f/max,
     /* Near */  -1.f,
      /* Far */  +1.f);
    glUniformMatrix4fv(grid->program->view_matrix_location,
                       1,
                       false,
                       (GLfloat *)grid->view_matrix);

    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VAO
    glBindVertexArray(0); //unbind VAO
    glUseProgram(0); // Don't use any program

    grid->factor = max;
}

/*----------------------------------------------------------------------------*/
void
pycasso_geo_grid_position_and_dimensions(pycasso_Grid *grid,
                                         GLfloat width,
                                         GLfloat height)
{
    // Set up VAO and view matrix
    pycasso_geo_grid_update_dimensions(grid, width, height);

    GLushort index_data[] = {  0, 1, 2,     // A -> B -> C
                               0, 2, 3  };  // A -> C -> D
    // Start using program
    glUseProgram(grid->program->id);

    // Set VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, grid->element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

    // Send model matrix
    glUniformMatrix4fv(grid->program->model_matrix_location,
                       1,
                       false,
                       (GLfloat *)grid->model_matrix);

    // Clean up
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind VBO
    glUseProgram(0); // Don't use any program
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_grid_color(pycasso_Grid *grid,
                       GLfloat color[4])
{
    glUseProgram(grid->program->id);
    // Set gradient base color and it's location
    glUniform4f(glGetUniformLocation(grid->program->id, "color"),
                color[0],
                color[1],
                color[2],
                color[3]);
    // Store values in instance
    for (int i=0; i<4; i++) grid->color[i] = color[i];
    // Clean up
    glUseProgram(0);
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_grid_spaces(pycasso_Grid *grid,
                        GLfloat h_space,
                        GLfloat v_space)
{
    GLfloat h = h_space/grid->factor;
    GLfloat v = v_space/grid->factor;
    glUseProgram(grid->program->id);
    // Set gradient base color and it's location
    glUniform2f(glGetUniformLocation(grid->program->id, "spaces"), h, v);
    // Store values in instance
    grid->h_space = h_space;
    grid->v_space = v_space;
    // Clean up
    glUseProgram(0);
}
