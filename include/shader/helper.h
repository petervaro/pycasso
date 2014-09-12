/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                       File: include/shader/helper.h                        **
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

#ifndef _PYCASSO_SHADER_HELPER_H_2694980957620303_
#define _PYCASSO_SHADER_HELPER_H_2694980957620303_

/* Include standard headers */
#include <stdio.h>    /* size_t */
#include <stdbool.h>  /* bool, true, false */

/* Include OpenGL/GLEW headers */
#include <GL/glew.h>

/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_helper_create_and_compile_shader(GLuint *shader_id,
                                                const GLchar *shader_source,
                                                GLenum shader_type);

/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_helper_create_and_compile_shader_from_file(GLuint *shader_id,
                                                          const char *file_path,
                                                          GLenum shader_type);

/*----------------------------------------------------------------------------*/
extern void
pycasso_shader_helper_delete_shaders(size_t shader_id_count,
                                     GLuint *shader_ids);

/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_helper_create_and_link_program(GLuint *program_id,
                                              const GLuint main_vertex_shader_id,
                                              size_t shader_count,
                                              const GLuint *shaders);

/*----------------------------------------------------------------------------*/
extern void
pycasso_shader_helper_unload_and_delete_program(GLuint program_id,
                                                size_t shader_id_count,
                                                GLuint *shader_ids);

#endif /* _PYCASSO_SHADER_HELPER_H_2694980957620303_ */
