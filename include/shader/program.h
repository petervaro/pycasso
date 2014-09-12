/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                       File: include/shader/program.h                       **
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

#ifndef _PYCASSO_SHADER_PROGRAM_H_9280575618073685_
#define _PYCASSO_SHADER_PROGRAM_H_9280575618073685_

/* Include standard headers */
#include <stddef.h>   /* size_t */
#include <stdbool.h>  /* bool */

/* Include OpenGL/GLEW headers */
#include <GL/glew.h>  /* GLchar, GLuint, GLfloat */

/*----------------------------------------------------------------------------*/
typedef struct pycasso_shader_program_program pycasso_shader_program_Program;

/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_program_Program_new(pycasso_shader_program_Program **program,
                                   const unsigned int program_type_bit_mask,
                                   const GLchar *layout_output_name,
                                   const size_t layout_input_count,
                                   const GLchar **layout_input_names,
                                   const GLuint *layout_input_positions,
                                   const GLuint *layout_input_component_count,
                                   const size_t shader_count,
                                   const GLuint *shader_ids,
                                   const GLuint main_vertex_shader_id,
                                   const GLchar *main_vertex_shader_input_name,
                                   const GLuint main_vertex_shader_input_position,
                                   const GLuint main_vertex_shader_input_component_count,
                                   const size_t arche_vertices_count,
                                   const GLfloat *arche_vertices);
/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_program_Program_del(pycasso_shader_program_Program *program);
/*----------------------------------------------------------------------------*/
extern void
pycasso_shader_program_Program_append(pycasso_shader_program_Program *program,
                                      const size_t instance_count,
                                      const size_t properties_count,
                                      const size_t *property_components_count,
                                      const GLfloat **properties,
                                      size_t *start_index);
/*----------------------------------------------------------------------------*/
extern void
pycasso_shader_program_Program_draw(size_t index,
                                    pycasso_shader_program_Program *program);
/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_program_Program_compare(const void *bit_id,
                                       const void *program,
                                       size_t size);

#endif /* _PYCASSO_SHADER_PROGRAM_H_9280575618073685_ */
