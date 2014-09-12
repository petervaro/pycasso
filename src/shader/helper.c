/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                         File: src/shader/helper.c                          **
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
#include <stdlib.h>   /* malloc(), free() */
#include <stdbool.h>  /* bool, true, false */
#include <stdio.h>    /* FILE, size_t, snprintf(),
                         fopen(), fseek(), ftell(), fread(), fclose() */

/* Include OpenGL/GLEW headers */
#include <GL/glew.h>

/* Include cutils headers */
#include <cutils/call.h>

/*----------------------------------------------------------------------------*/
bool
pycasso_shader_helper_create_and_compile_shader(GLuint *shader_id,
                                                const GLchar *shader_source,
                                                GLenum shader_type)
{
    GLuint _shader_id = glCreateShader(shader_type);
    glShaderSource(_shader_id, 1, (const GLchar **)&shader_source, NULL);
    glCompileShader(_shader_id);

    /* Check if compilation was successful */
    GLint is_compiled;
    glGetShaderiv(_shader_id, GL_COMPILE_STATUS, &is_compiled);
    if (!is_compiled)
    {
        #undef  EXCEPTION_FMT
        #define EXCEPTION_FMT "OpenGL Error, shader compilation: %s"

        /* Get OpenGL info log */
        GLint log_len;
        glGetShaderiv(_shader_id, GL_INFO_LOG_LENGTH, &log_len);
        char info_log[log_len];
        glGetShaderInfoLog(_shader_id, log_len, NULL, info_log);

        /* Format proper exception message */
        char exc_msg[(log_len += sizeof EXCEPTION_FMT)];
        snprintf(exc_msg, log_len, EXCEPTION_FMT, info_log);

        /* Pass the error message to the exception handler */
        raise(exc_msg, log_len);

        /* Clean up */
        glDeleteShader(_shader_id);

        /* Set shader and return as failure */
        *shader_id = 0;
        return false;
    }

    /* Set shader */
    *shader_id = _shader_id;
    return true;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_helper_create_and_compile_shader_from_file(GLuint *shader_id,
                                                          const char *file_path,
                                                          GLenum shader_type)
{
    /* Exception raiser flags */
    bool exception_from_allocation = false;

    /* Open source file */
    FILE *shader_file = fopen(file_path, "rb");
    if (!shader_file) goto Exception_From_Opening_File;

    /* Get length of file */
    fseek(shader_file, 0l, SEEK_END);
    size_t file_size = ftell(shader_file);
    fseek(shader_file, 0l, SEEK_SET);

    /* Create string buffer for source of shader */
    GLchar *shader_source = malloc((file_size + 1) * sizeof(GLchar));
    if (!shader_source) goto Exception_From_Allocation;

    /* Read the source of the shader and store it in the buffer */
    fread(shader_source, file_size, 1, shader_file);
    shader_source[file_size] = '\0';

    /* Create and compile shader */
    bool check = pycasso_shader_helper_create_and_compile_shader(shader_id,
                                                                 shader_source,
                                                                 shader_type);
    /* Clean up */
    free(shader_source);
    fclose(shader_file);

    /* Return state of creation and compilation */
    return check;

    /* If string buffer for source of shader failed to allocate */
    Exception_From_Allocation:
        #undef  EXCEPTION_MESSAGE
        #define EXCEPTION_MESSAGE "Allocation of shader's source failed"
        raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);
        exception_from_allocation = true;

    /* If something went wrong during opening the source file */
    Exception_From_Opening_File:
        if (!exception_from_allocation)
        {
            #undef  EXCEPTION_FMT
            #define EXCEPTION_FMT "File cannot be opened: %s"

            /* Format proper exception message */
            size_t msg_len = sizeof EXCEPTION_FMT + strlen(file_path);
            char exc_msg[msg_len];
            snprintf(exc_msg, msg_len, EXCEPTION_FMT, file_path);

            /* Pass the error message to the exception handler */
            raise(exc_msg, msg_len);
        }

        /* Clean up */
        fclose(shader_file);

        /* Set shader and return as failure */
        *shader_id = 0;
        return false;
}



/*----------------------------------------------------------------------------*/
void
pycasso_shader_helper_delete_shaders(size_t shader_id_count,
                                     GLuint *shader_ids)
{
    /* Detach shaders */
    for (size_t i=0; i<shader_id_count; i++)
        glDeleteShader(shader_ids[i]);
}



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_helper_create_and_link_program(GLuint *program_id,
                                              const GLuint main_vertex_shader_id,
                                              size_t shader_count,
                                              const GLuint *shaders)
{
    /* Create program */
    GLuint _program_id = glCreateProgram();
    debug("program-id: %d", _program_id);

    /* Attach main vertex shader */
    glAttachShader(_program_id, main_vertex_shader_id);

    /* Attach shaders */
    size_t i;
    for (i=0; i<shader_count; i++)
        glAttachShader(_program_id, shaders[i]);

    /* Link program */
    glLinkProgram(_program_id);

    /* Check if linking was successful */
    GLint is_linked;
    glGetProgramiv(_program_id, GL_LINK_STATUS, &is_linked);
    if (!is_linked)
    {
        #undef  EXCEPTION_FMT
        #define EXCEPTION_FMT "OpenGL Error, shader program linking: %s"

        /* Get OpenGL info log */
        GLint log_len;
        glGetProgramiv(_program_id, GL_INFO_LOG_LENGTH, &log_len);
        char info_log[log_len];
        glGetProgramInfoLog(_program_id, log_len, NULL, info_log);

        /* Format proper exception message */
        char exc_msg[(log_len += sizeof EXCEPTION_FMT)];
        snprintf(exc_msg, log_len, EXCEPTION_FMT, info_log);

        /* Pass the error message to the exception handler */
        raise(exc_msg, log_len);

        /* Clean up */
        for (i=0; i<shader_count; i++)
            glDetachShader(_program_id, shaders[i]);
        glDeleteProgram(_program_id);

        /* Set program and return as failure */
        *program_id = 0;
        return false;
    }

    /* Set program */
    *program_id = _program_id;
    return true;
}



/*----------------------------------------------------------------------------*/
void
pycasso_shader_helper_unload_and_delete_program(GLuint program_id,
                                                size_t shader_id_count,
                                                GLuint *shader_ids)
{
    /* Detach shaders */
    for (size_t i=0; i<shader_id_count; i++)
        glDetachShader(program_id, shader_ids[i]);
    /* Delete program from the GPU */
    glDeleteProgram(program_id);
}
