// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                       File: include/_DEL_geo/types.h                       //
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

#ifndef _PYCASSO_GEO_TYPES_H_
#define _PYCASSO_GEO_TYPES_H_

/*----------------------------------------------------------------------------*/
typedef struct pycasso_grid
{
    // Pointer to the linked-list
    // item it is stored "in"
    pycasso_GeometryInstance *instance;

    // Store pointer to resources
    pycasso_StaticResources *resources;

    // Shader program
    pycasso_ShaderProgram *program;

    // Abstract properties
    GLfloat h_space;
    GLfloat v_space;
    GLfloat color[4];

    // OpenGL properties
    GLuint vertex_array;
    GLuint vertex_buffer;
    GLuint element_buffer;

    // Matrix
    mat4x4 view_matrix;
    mat4x4 model_matrix;

    // PerPixel scaling factor
    GLfloat factor;

} pycasso_Grid;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct pycasso_rectangle
{
    // Pointer to the linked-list
    // item it is stored "in"
    pycasso_GeometryInstance *instance;

    // Store pointer to resources
    pycasso_StaticResources *resources;

    // Shader program
    pycasso_ShaderProgram *program;

    // Abstract properties
    GLfloat x;
    GLfloat y;
    GLfloat width;
    GLfloat height;
    GLfloat color_angle;
    GLfloat color_base[4];
    GLfloat color_stop[4];
    GLfloat color_base_location;
    GLfloat color_stop_location;
    GLfloat corner_radiuses[4];

    // OpenGL properties
    GLuint vertex_array;
    GLuint vertex_buffer;
    GLuint element_buffer;

    // Matrix
    mat4x4 view_matrix;
    mat4x4 model_matrix;

    GLfloat color_rotation_matrix[4];

    // PerPixel scaling factor
    GLfloat factor;

} pycasso_Rectangle;

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
typedef struct pycasso_rounded_rectangle
{
    // Pointer to the linked-list
    // item it is stored "in"
    pycasso_GeometryInstance *instance;

    // Store pointer to resources
    pycasso_StaticResources *resources;

    // Shader program
    pycasso_ShaderProgram *program;

    // Abstract properties
    GLfloat x;
    GLfloat y;
    GLfloat width;
    GLfloat height;
    GLfloat color_angle;
    GLfloat color_base[4];
    GLfloat color_stop[4];
    GLfloat color_base_location;
    GLfloat color_stop_location;
    GLfloat corner_radiuses[4];

    // OpenGL properties
    GLuint vertex_array;
    GLuint vertex_buffer;
    GLuint element_buffer;

    // Matrix
    mat4x4 view_matrix;
    mat4x4 model_matrix;

    GLfloat color_rotation_matrix[4];

    // PerPixel scaling factor
    GLfloat factor;

} pycasso_RoundedRectangle;

#endif
