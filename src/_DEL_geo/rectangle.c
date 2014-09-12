// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                       File: src/_DEL_geo/rectangle.c                       //
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
#include <string.h>    // memcpy()
#include <math.h>      // fmax()

// Include pycasso headers
#include "../../include/allheaders.h"
#include "../../include/debug.h"


#define RRECT_NUM_OF_SHADERS 4



//     1) REFACTOR this RECTANGLE, to be easier to use (texture + color)
//     2) _pycasso_geo_rectangle_projection(mat4x4 projection_matrix);
//     3) Create circle, polygon, triangle, bezier



/*----------------------------------------------------------------------------*/
static inline pycasso_RoundedRectangle *
_pycasso_geo_rectangle_init(pycasso_StaticResources *resources)
{
    // Create rectangle instance
    pycasso_RoundedRectangle *rectangle = malloc(sizeof(pycasso_RoundedRectangle));
    if (!rectangle)
    {
        printf("Couldn't allocated memory for a new rectangle\n");
        exit(EXIT_FAILURE);
    }

    // Create instance struct
    pycasso_GeometryInstance *instance = pycasso_admin_init_instance(resources);
    instance->type = PYCASSO_GEO_ROUNDED_RECTANGLE;
    instance->geometry = rectangle;

    // Store essential management pointers
    rectangle->resources = resources;
    rectangle->instance  = instance;

    // Return new instance
    return rectangle;
}


/*----------------------------------------------------------------------------*/
pycasso_RoundedRectangle *
pycasso_geo_rectangle_textured_init(pycasso_StaticResources *resources,
                                    GLfloat x,
                                    GLfloat y,
                                    GLfloat width,
                                    GLfloat height,
                                    const char *texture_path,
                                    GLfloat corner_radiuses[4])
{
    // Create rectangle struct and store it
    pycasso_RoundedRectangle *rectangle;
    rectangle = _pycasso_geo_rectangle_init(resources);

    // Create and store textured rectangle shader program
    GLuint program_id;
    GLuint shaders[] = {resources->vs->textured,
                        resources->fs->main_fs,
                        resources->fs->shape_rounded_rectangle_fs,
                        resources->fs->fill_texture_fs};
    pycasso_shaders_create_and_load_program(&program_id, RRECT_NUM_OF_SHADERS, shaders);
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
    program->num_of_shaders = RRECT_NUM_OF_SHADERS;
    program->shaders = (GLuint *)malloc(program->num_of_shaders * sizeof(GLuint));
    if (!program->shaders)
    {
        printf("Couldn't allocated memory for shader IDs of rectangle\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<RRECT_NUM_OF_SHADERS; i++) program->shaders[i] = shaders[i];

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

    // Return new instance
    return rectangle;
}


/*----------------------------------------------------------------------------*/
pycasso_RoundedRectangle *
pycasso_geo_rectangle_colored_init(pycasso_StaticResources *resources,
                                   GLfloat x,
                                   GLfloat y,
                                   GLfloat width,
                                   GLfloat height,
                                   GLfloat color_angle,
                                   GLfloat color_base[4],
                                   GLfloat color_stop[4],
                                   GLfloat color_base_location,
                                   GLfloat color_stop_location,
                                   GLfloat corner_radiuses[4])
{
    // Create rectangle struct and store it
    pycasso_RoundedRectangle *rectangle;
    rectangle = _pycasso_geo_rectangle_init(resources);

    // Create and store colored rectangle shader program
    GLuint program_id;
    GLuint shaders[] = {resources->vs->colored,
                        resources->fs->main_fs,
                        resources->fs->shape_rounded_rectangle_fs,
                        resources->fs->fill_linear_gradient_fs};
    pycasso_shaders_create_and_load_program(&program_id, RRECT_NUM_OF_SHADERS, shaders);

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
    program->texture_location  = 0;
    // Store attached shaders
    program->num_of_shaders = RRECT_NUM_OF_SHADERS;
    program->shaders = (GLuint *)malloc(program->num_of_shaders * sizeof(GLuint));
    if (!program->shaders)
    {
        printf("Couldn't allocated memory for shader IDs of rectangle\n");
        exit(EXIT_FAILURE);
    }
    // Store shader IDs in the program struct
    for (int i=0; i < RRECT_NUM_OF_SHADERS; i++) program->shaders[i] = shaders[i];

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
    glBindVertexArray(0);

    // Set properties of instance
    pycasso_geo_rectangle_dimension(rectangle, width, height);
    pycasso_geo_rectangle_position(rectangle, x, y);
    pycasso_geo_rectangle_color_base(rectangle, color_base);
    pycasso_geo_rectangle_color_stop(rectangle, color_stop);
    pycasso_geo_rectangle_color_base_location(rectangle, color_base_location);
    pycasso_geo_rectangle_color_stop_location(rectangle, color_stop_location);
    pycasso_geo_rectangle_color_angle(rectangle, color_angle);
    pycasso_geo_rectangle_corner_radiuses(rectangle, corner_radiuses);

    // Bind fragment data output
    glBindFragDataLocation(program->id, 0, "fragment");
    // Clean up
    glUseProgram(0); // Don't use any program

    // Return new instance
    return rectangle;
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_rectangle_delete(pycasso_RoundedRectangle *rectangle)
{
    // Detach shaders, free shader storage, delete program, free program
    pycasso_shaders_unload_and_delete_program(rectangle->program);

    // Delete buffers
    //glDeleteTextures(1, &rectangle->texture);
    glDeleteBuffers(1, &rectangle->vertex_buffer);
    glDeleteBuffers(1, &rectangle->element_buffer);
    glDeleteVertexArrays(1, &rectangle->vertex_array);

    // Delete rectangle from resources
    pycasso_admin_delete_instance(rectangle->instance,
                                  rectangle->resources);
    // Clean up
    free(rectangle);
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_rectangle_projection(pycasso_RoundedRectangle *rectangle,
                                 mat4x4 projection_matrix)
{
    // Get program and use it
    glUseProgram(rectangle->program->id);
    // Send projection matrix
    glUniformMatrix4fv(rectangle->program->projection_matrix_location,
                       1,
                       false,
                       (GLfloat *)projection_matrix);
    // Cleanup
    glUseProgram(0);
}

/*----------------------------------------------------------------------------*/
void
pycasso_geo_rectangle_draw(pycasso_RoundedRectangle *rectangle)
{
    // Get program and use it
    glUseProgram(rectangle->program->id);

    // Make buffer objects current, draw them
    glBindVertexArray(rectangle->vertex_array);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle->element_buffer);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, NULL);

    // Cleanup
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind
    glBindVertexArray(0); //unbind
    glUseProgram(0);
}


/*----------------------------------------------------------------------------*/
static inline void
_pycasso_geo_rectangle_textured_dimension(pycasso_RoundedRectangle *rectangle,
                                          GLfloat width,
                                          GLfloat height)
{
    // Normalize value to [0.f .. 1.f]
    width  = fabs(width);
    height = fabs(height);
    GLfloat max = fmax(width, height);
    GLfloat w = width/max;
    GLfloat h = height/max;

    /*  D---A
        |  /|
        | / |
        |/  |
        C---B  */

    // Update OpenGL values   | vertices | texture |
    GLfloat buffer_data[] = {    w,   h,   1.f, 1.f,     // A
                               0.f,   h,   0.f, 1.f,     // B
                               0.f, 0.f,   0.f, 0.f,     // C
                                 w, 0.f,   1.f, 0.f  };  // D

    GLushort index_data[] = {  0, 1, 2,     // A -> B -> C
                               0, 2, 3  };  // A -> C -> D

    // Start using program
    glUseProgram(rectangle->program->id);
    // Set VAO
    glBindVertexArray(rectangle->vertex_array); // Make it current
    glBindBuffer(GL_ARRAY_BUFFER, rectangle->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(rectangle->program->position_location,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          4*sizeof(GLfloat),
                          (GLvoid *)(0 * sizeof(GLfloat)));

    glVertexAttribPointer(rectangle->program->texture_location,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          4*sizeof(GLfloat),
                          (GLvoid *)(2 * sizeof(GLfloat)));
    // Set VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle->element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

    // Send data
    glUniform2f(glGetUniformLocation(rectangle->program->id, "dimensions"), w, h);

    // Calculate and send view matrix
    mat4x4_ortho(rectangle->view_matrix,
     /* Left */  -1.f/max,
    /* Right */  +1.f/max,
   /* Bottom */  -1.f/max,
      /* Top */  +1.f/max,
     /* Near */  -1.f,
      /* Far */  +1.f);
    glUniformMatrix4fv(rectangle->program->view_matrix_location,
                       1,
                       false,
                       (GLfloat *)rectangle->view_matrix);

    // Clean up
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO
    glBindVertexArray(0); //unbind VAO
    glUseProgram(0); // Don't use any program

    // Store values in instance
    rectangle->width  = width;
    rectangle->height = height;
    rectangle->factor = max;
}

/*----------------------------------------------------------------------------*/
static inline void
_pycasso_geo_rectangle_colored_dimension(pycasso_RoundedRectangle *rectangle,
                                         GLfloat width,
                                         GLfloat height)
{
    // Normalize value to [0.f .. 1.f]
    width  = fabs(width);
    height = fabs(height);
    GLfloat max = fmax(width, height);
    GLfloat w = width/max;
    GLfloat h = height/max;

    /*  D---A
        |  /|
        | / |
        |/  |
        C---B  */

    // Update OpenGL values
    GLfloat buffer_data[] = {  w, h,     // A
                               0, h,     // B
                               0, 0,     // C
                               w, 0  };  // D

    GLushort index_data[] = {  0, 1, 2,     // A -> B -> C
                               0, 2, 3  };  // A -> C -> D

    // Start using program
    glUseProgram(rectangle->program->id);
    // Set VAO
    glBindVertexArray(rectangle->vertex_array); // Make it current
    glBindBuffer(GL_ARRAY_BUFFER, rectangle->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(rectangle->program->position_location,
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          2*sizeof(GLfloat),
                          (GLvoid *)NULL);
    // Set VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectangle->element_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

    // Send data
    glUniform2f(glGetUniformLocation(rectangle->program->id, "dimensions"), w, h);

    // Calculate and send view matrix
    mat4x4_ortho(rectangle->view_matrix,
     /* Left */  -1.f/max,
    /* Right */  +1.f/max,
   /* Bottom */  -1.f/max,
      /* Top */  +1.f/max,
     /* Near */  -1.f,
      /* Far */  +1.f);
    glUniformMatrix4fv(rectangle->program->view_matrix_location,
                       1,
                       false,
                       (GLfloat *)rectangle->view_matrix);

    // Clean up
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind VBO
    glBindVertexArray(0); //unbind VAO
    glUseProgram(0); // Don't use any program

    // Store values in instance
    rectangle->width  = width;
    rectangle->height = height;
    rectangle->factor = max;
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_rectangle_dimension(pycasso_RoundedRectangle *rectangle,
                                GLfloat width,
                                GLfloat height)
{
    // If rectangle is textured
    if (rectangle->program->texture_location)
        _pycasso_geo_rectangle_textured_dimension(rectangle, width, height);
    // If rectangle is color only
    else
        _pycasso_geo_rectangle_colored_dimension(rectangle, width, height);
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_rectangle_position(pycasso_RoundedRectangle *rectangle,
                               GLfloat x,
                               GLfloat y)
{
    // Calculate move and set model matrix
    mat4x4_translate(rectangle->model_matrix,
                     x/rectangle->factor,
                     y/rectangle->factor,
                     0.f);


    glUseProgram(rectangle->program->id);
    // Send model matrix
    glUniformMatrix4fv(rectangle->program->model_matrix_location,
                       1,
                       false,
                       (GLfloat *)rectangle->model_matrix);
    // Clean up
    glUseProgram(0); // Don't use any program
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_rectangle_texture(pycasso_RoundedRectangle *rectangle,
                              const char *texture_path)
{
    glUseProgram(rectangle->program->id);
    GLuint texture_id;
    pycasso_texture_load_image_to_texture(&texture_id,
                         /* File path */  texture_path,
                      /* Repeat Image */  false,
                         /* Soft Zoom */  true);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glUniform1i(glGetUniformLocation(rectangle->program->id, "texture_sampler"),
                0); //0 because GL_TEXTURE0
    // Clean up
    glUseProgram(0);
}


/*----------------------------------------------------------------------------*/
static inline void
_pycasso_geo_rectangle_color(GLuint program_id,
                             char *color_program_location,
                             GLfloat old_color_array[4],
                             GLfloat new_color_array[4])
{
    glUseProgram(program_id);
    // Set gradient base color and it's location
    glUniform4f(glGetUniformLocation(program_id, color_program_location),
                new_color_array[0],
                new_color_array[1],
                new_color_array[2],
                new_color_array[3]);
    // Store values in instance
    for (int i=0; i<4; i++) old_color_array[i] = new_color_array[i];
    // Clean up
    glUseProgram(0);
}


/*------------------------------------------------------------------------------
wrapper >> pycasso_geo_rectangle_color*/
void
pycasso_geo_rectangle_color_base(pycasso_RoundedRectangle *rectangle,
                                 GLfloat new_color_array[4])
{
        _pycasso_geo_rectangle_color(rectangle->program->id,
                                     "color_base",
                                     rectangle->color_base,
                                     new_color_array);
}


/*------------------------------------------------------------------------------
wrapper >> pycasso_geo_rectangle_color*/
void
pycasso_geo_rectangle_color_stop(pycasso_RoundedRectangle *rectangle,
                                 GLfloat new_color_array[4])
{
        _pycasso_geo_rectangle_color(rectangle->program->id,
                                     "color_stop",
                                     rectangle->color_stop,
                                     new_color_array);
}


/*----------------------------------------------------------------------------*/
static inline void
_pycasso_geo_rectangle_color_location(GLuint program_id,
                                      char *color_location_program_location,
                                      GLfloat *color_location,
                                      GLfloat new_color_location)
{
    // Get shader program and start to use it
    glUseProgram(program_id);
    // Set gradient base color and it's location
    glUniform1f(glGetUniformLocation(program_id, color_location_program_location),
                new_color_location);
    // Store values in instance
    *color_location = new_color_location;
    // Clean up
    glUseProgram(0);
}


/*------------------------------------------------------------------------------
wrapper >> pycasso_geo_rectangle_color_location*/
void
pycasso_geo_rectangle_color_base_location(pycasso_RoundedRectangle *rectangle,
                                          GLfloat new_color_location)
{
    _pycasso_geo_rectangle_color_location(rectangle->program->id,
                                          "color_base_location",
                                          &rectangle->color_base_location,
                                          new_color_location);
}


/*------------------------------------------------------------------------------
wrapper >> pycasso_geo_rectangle_color_location*/
void
pycasso_geo_rectangle_color_stop_location(pycasso_RoundedRectangle *rectangle,
                                          GLfloat new_color_location)
{
    _pycasso_geo_rectangle_color_location(rectangle->program->id,
                                          "color_stop_location",
                                          &rectangle->color_stop_location,
                                          new_color_location);
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_rectangle_color_angle(pycasso_RoundedRectangle *rectangle,
                                  GLfloat new_color_angle)
{
    // Get shader program and start to use it
    glUseProgram(rectangle->program->id);
    // Create rotation matrix
    GLfloat angle = RADIANS(new_color_angle);
    GLfloat sin_theta = sinf(angle);
    GLfloat cos_theta = cosf(angle);
    GLfloat rotation[] = { -sin_theta, +cos_theta,
                           +cos_theta, +sin_theta  };
    memcpy(&rectangle->color_rotation_matrix, &rotation, sizeof(GLfloat)*4);
    // Send values
    glUniformMatrix2fv(glGetUniformLocation(rectangle->program->id, "color_rotation"),
                       1,
                       false,
                       rectangle->color_rotation_matrix);
    // Store values in instance
    rectangle->color_angle = new_color_angle;
    // Clean up
    glUseProgram(0);
}


/*----------------------------------------------------------------------------*/
void
pycasso_geo_rectangle_corner_radiuses(pycasso_RoundedRectangle *rectangle,
                                      GLfloat new_corner_radiuses[4])
{
    GLfloat factor = rectangle->factor;
    // Get shader program and start to use it
    GLuint  program_id = rectangle->program->id;
    glUseProgram(program_id);
    // Send values
    glUniform4f(glGetUniformLocation(program_id, "radiuses"),
                new_corner_radiuses[0]/factor,
                new_corner_radiuses[1]/factor,
                new_corner_radiuses[2]/factor,
                new_corner_radiuses[3]/factor);
    // Store values in instance
    for (int i=0; i<4; i++) rectangle->corner_radiuses[i] = new_corner_radiuses[i];
    // Clean up
    glUseProgram(0);
}
