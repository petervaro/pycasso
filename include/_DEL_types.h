// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                         File: include/_DEL_types.h                         //
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

#ifndef _PYCASSO_TYPES_H_
#define _PYCASSO_TYPES_H_

/*----------------------------------------------------------------------------*/
typedef struct pycasso_frag_shaders
{
    // Fill shaders
    GLuint fill_solid_color_fs;
    GLuint fill_linear_gradient_fs;
    GLuint fill_radial_gradient_fs;
    GLuint fill_conical_gradient_fs;
    GLuint fill_texture_fs;

    // Shape shaders
    GLuint shape_rectangle_fs;
    GLuint shape_rounded_rectangle_fs;
    GLuint shape_circle_fs;

    // Main (manager) shader
    GLuint main_fs;

    // Other / System shaders
    GLuint grid;

} pycasso_FragShaders;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct pycasso_vert_shaders
{
    // Geometry
    GLuint colored;
    GLuint textured;

    // System
    GLuint grid;

} pycasso_VertShaders;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct pycasso_shader_program
{
    // ID of program
    GLuint id;

    // Matrix uniform locations
    GLuint projection_matrix_location;
    GLuint view_matrix_location;
    GLuint model_matrix_location;

    // Vertex location
    GLuint position_location;
    GLuint texture_location;

    // Attached shaders
    GLuint *shaders;
    size_t num_of_shaders;

} pycasso_ShaderProgram;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef enum
{
    PYCASSO_GEO_EMPTY = 0,
    PYCASSO_GEO_GRID,
    PYCASSO_GEO_RECTANGLE,
    PYCASSO_GEO_ROUNDED_RECTANGLE,
    PYCASSO_GEO_CIRCLE,
    PYCASSO_GEO_TRIANGLE

} pycasso_geometry_t;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct pycasso_geometry_instance
{
    // Administration
    struct pycasso_geometry_instance *prev_instance;  // Previous item in linked-list
    struct pycasso_geometry_instance *next_instance;  // Next item in linked-list

    pycasso_geometry_t type;
    void *geometry;

} pycasso_GeometryInstance;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct pycasso_static_resources
{
    GLFWwindow *window;

    mat4x4 projection_matrix;

    pycasso_FragShaders *fs;
    pycasso_VertShaders *vs;

    pycasso_GeometryInstance *last_instance;   // Last item in linked list

} pycasso_StaticResources;

#endif
