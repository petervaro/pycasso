/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                      File: include/shader/resources.h                      **
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

#ifndef _PYCASSO_SHADER_RESOURCES_H_8745874155338696_
#define _PYCASSO_SHADER_RESOURCES_H_8745874155338696_

/* Include standard headers */
#include <stddef.h>  /* size_t */

/* Include OpenGL/GLEW headers */
#include <GL/glew.h> /* GLfloat */

/*----------------------------------------------------------------------------*/
typedef struct pycasso_shader_resources_primitives pycasso_shader_resources_Primitives;

/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_resources_Primitives_new(pycasso_shader_resources_Primitives **resources);
/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_resources_Primitives_del(pycasso_shader_resources_Primitives *resources);
/*----------------------------------------------------------------------------*/
extern bool
pycasso_shader_resources_Primitives_add(pycasso_shader_resources_Primitives *resources,
                                        unsigned int bit_id,
                                        const size_t arche_vertices_count,
                                        const GLfloat *arche_vertices,
                                        const size_t instance_count,
                                        const size_t property_count,
                                        const size_t *property_components_count,
                                        const GLfloat **properties,
                                        size_t *index);
/*----------------------------------------------------------------------------*/
void
pycasso_shader_resources_Primitives_draw_all(pycasso_shader_resources_Primitives *primitives);

#endif /* _PYCASSO_SHADER_RESOURCES_H_8745874155338696_ */
