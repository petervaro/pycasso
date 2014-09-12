// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                           File: include/debug.h                            //
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

#ifndef _DEBUG_H_
#define _DEBUG_H_

/* Include standard headers */
#include <stdio.h>    /* size_t */
#include <string.h>   /* strncpy() */

/* Include OpenGL/GLEW headers */
#include <GL/glew.h>

/*----------------------------------------------------------------------------*/
/* #define debug(OUT) do { \
        if (DEBUG) \
            fprintf(stderr, "In file '%s', at line %d,\nin '%s' function:\n\t%s\n", \
                    __FILE__, __LINE__, __func__, OUT); \
    } while (0)

#define debugf(FORMAT, ...) do { \
        if (DEBUG) \
            fprintf(stderr, "In file '%s', at line %d,\nin '%s' function:\n\t" FORMAT "\n", \
                    __FILE__, __LINE__, __func__, __VA_ARGS__); \
    } while (0)

#define debuggl() do { \
        if (DEBUG) \
            fprintf(stderr, "In file '%s', at line %d,\nin '%s' function:\n\t%s\n", \
                    __FILE__, __LINE__, __func__, opengl_get_error(glGetError())); \
    } while (0)

#define debugmat4x4(MATRIX) do { \
        if (DEBUG) { \
            fprintf(stderr, "In file '%s', at line %d,\nin '%s' function:\n", \
                            __FILE__, __LINE__, __func__); \
            for (int i=0; i<4; i++) { \
                for (int j=0; j<4; j++) { \
                    fprintf(stderr, "%.2f ", MATRIX[i][j]); \
                } fprintf(stderr, "\n"); \
    }}} while (0)

#define debugmat2x2(MATRIX) do { \
        if (DEBUG) { \
            fprintf(stderr, "In file '%s', at line %d,\nin '%s' function:\n", \
                            __FILE__, __LINE__, __func__); \
            for (int i=0; i<2; i++) { \
                for (int j=0; j<2; j++) { \
                    fprintf(stderr, "%.2f ", MATRIX[i][j]); \
                } fprintf(stderr, "\n"); \
    }}} while (0) */

/*------------------------------------------------------------------------------
 * Get and clear OpenGL error buffer and
 * translate the error enums into string
 * Returns: the enum name as string
 * based on: https://www.opengl.org/wiki/OpenGL_Error
 */
static inline const char *
opengl_get_error(void)
{
    /* Get string representation of OpenGL error code */
    switch (glGetError())
    {
        case 0x0500: return "GL_INVALID_ENUM";
        case 0x0501: return "GL_INVALID_VALUE";
        case 0x0502: return "GL_INVALID_OPERATION";
        case 0x0503: return "GL_STACK_OVERFLOW";
        case 0x0504: return "GL_STACK_UNDERFLOW";
        case 0x0505: return "GL_OUT_OF_MEMORY";
        case 0x0506: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case 0x8031: return "GL_TABLE_TOO_LARGE";
            default: return "GL_NO_ERROR";
    }
}


/*------------------------------------------------------------------------------
 * Debug a shader program by printing out the
 * attached shaders' indices to the program
 */
/* static inline void
check_attached_shaders(GLuint program)
{
    GLsizei count = 0;
    GLuint shaders[] = {0, 0, 0, 0};
    glGetAttachedShaders(program, 4, &count, shaders);
    debuggl();
    printf("\tnumber of shaders: %d\n", count);
    for (int i=0; i < count; i++) printf("\tshader_id: %d\n", shaders[i]);
} */

#endif /* _DEBUG_H_ */
