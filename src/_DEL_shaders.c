// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                          File: src/_DEL_shaders.c                          //
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

// Include stadard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Include pycasso headers
#include "../include/allheaders.h"
#include "../include/debug.h"

/*----------------------------------------------------------------------------*/
void
pycasso_shaders_create_shader_from_file(GLuint *shader_id,
                                        GLchar *file_path,
                                        GLenum shader_type)
{
    FILE    *shader_file;
    GLchar  *string_buffer;
    size_t  file_size;

    // Create a file pointer and open file_path to read
    // and handle if file cannot be opened
    shader_file = fopen(file_path, "rb");
    if (!shader_file)
    {
        fclose(shader_file);
        printf("File cannot be opened: '%s'\n", file_path);
        *shader_id = 0;
        return;
    }

    // Get file length"
    fseek(shader_file, 0L, SEEK_END);
    file_size = ftell(shader_file);
    fseek(shader_file, 0L, SEEK_SET);

    // Allocate string buffer and read file to buffer
    string_buffer = malloc((file_size + 1)*sizeof(GLchar));
    if (!string_buffer)
    {
        printf("Couldn't allocated memory for shader string buffer.\n");
        fclose(shader_file);
        *shader_id = 0;
        return;
    }
    fread((void *)string_buffer, file_size, 1, shader_file);
    string_buffer[file_size] = 0; // null-terminate string
    // Get shader_id, pass shader source, compile it
    *shader_id = glCreateShader(shader_type);
    glShaderSource(*shader_id, 1, (const GLchar **)&string_buffer, NULL);
    glCompileShader(*shader_id);

    // If there was a problem during the compilation
    GLint is_compiled;
    glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &is_compiled);
    if (!is_compiled)
    {
        printf("Shader failed to compile: '%s'\n", file_path);
        // Get debugging information
        GLint info_log_length;
        glGetShaderiv(*shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar *info_log = malloc(info_log_length*sizeof(GLchar));
        glGetShaderInfoLog(*shader_id, info_log_length, NULL, info_log);
        printf("%s\n", info_log);
        // Clean up
        fclose(shader_file);
        glDeleteShader(*shader_id);
        free(info_log);
        free(string_buffer);
        *shader_id = 0;
        return;
    }

    // Clean up by closing the file and freeing the buffer
    fclose(shader_file);
    free(string_buffer);
}


/*----------------------------------------------------------------------------*/
void
pycasso_shaders_load_and_compile_shaders(void *shader_storage,
                                         int size_of_shader_storage,
                                         const char **shader_paths,
                                         int size_of_shader_paths,
                                         const char *struct_type_name,
                                         GLenum shader_type)
{
    // If the size of the
    if (size_of_shader_storage != size_of_shader_paths)
    {
        printf("The size of the '%s' struct is not identical "
               "to the size of the shader paths array\n", struct_type_name);
        exit(EXIT_FAILURE);
    }
    // Load shaders from files and store
    // their IDs provided by OpenGL
    GLuint id;
    for (int i=0; i < size_of_shader_paths; i++)
    {
        pycasso_shaders_create_shader_from_file(&id,
                                                (GLchar *)shader_paths[i],
                                                shader_type);
        *(GLuint *)(shader_storage + i*sizeof(GLuint)) = id;
    }
}


/*----------------------------------------------------------------------------*/
void
pycasso_shaders_unload_and_delete_shaders(void *shaders_storage)
{
    // Delete shaders in storage
    for (int i=0; i < sizeof(*shaders_storage)/sizeof(GLuint); i++)
        glDeleteShader(*(GLuint *)(shaders_storage + i*sizeof(GLuint)));
}


/*----------------------------------------------------------------------------*/
void
pycasso_shaders_create_and_load_program(GLuint *program_id,
                                        GLuint num_of_shaders,
                                        GLuint shaders[])
{
    // Create new program and get program ID
    *program_id = glCreateProgram();

    // Attach all the shaders passed
    for (int i=0; i < num_of_shaders; i++) glAttachShader(*program_id, shaders[i]);

    // Link shader program
    glLinkProgram(*program_id);

    // If there was a problem during the linking
    GLint is_linked;
    glGetProgramiv(*program_id, GL_LINK_STATUS, &is_linked);
    if (!is_linked)
    {
        printf("Shader program linking failed.\n");
        // Get debugging informations
        GLint info_log_length;
        glGetProgramiv(*program_id, GL_INFO_LOG_LENGTH, &info_log_length);
        GLchar *info_log = malloc(info_log_length*sizeof(GLchar));
        glGetProgramInfoLog(*program_id, info_log_length, NULL, info_log);
        printf("%s\n", info_log);
        // Clean up
        for (int i=0; i < num_of_shaders; i++) glDetachShader(*program_id, shaders[i]);
        glDeleteProgram(*program_id);
        free(info_log);
        *program_id = 0;
        return;
    }
}


/*----------------------------------------------------------------------------*/
void
pycasso_shaders_unload_and_delete_program(pycasso_ShaderProgram *program)
{
    // Detach shaders from program and delete array holding shaders IDs
    for (int i=0; i < program->num_of_shaders; i++)
        glDetachShader(program->id, program->shaders[i]);
    free(program->shaders);

    // Delete program and
    glDisableVertexAttribArray(program->position_location);
    //glBindTexture(GL_TEXTURE_2D, (GLuint)NULL);

    // Delete program from GPU and its struct from memory
    glDeleteProgram(program->id);
    free(program);
}
