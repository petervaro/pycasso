/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                          File: include/session.h                           **
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

#ifndef _PYCASSO_SESSION_H_326777659243943_
#define _PYCASSO_SESSION_H_326777659243943_

/* Include standard headers */
#include <stddef.h>   /* size_t */
#include <stdbool.h>  /* bool */

/*----------------------------------------------------------------------------*/
typedef struct pycasso_session_session pycasso_session_Session;

/*----------------------------------------------------------------------------*/
extern bool
pycasso_session_Session_new(pycasso_session_Session **session);
/*----------------------------------------------------------------------------*/
extern bool
pycasso_session_Session_run(pycasso_session_Session *session,
                            void (*function)(pycasso_session_Session*));
/*----------------------------------------------------------------------------*/
extern bool
pycasso_session_Session_del(pycasso_session_Session *session);
/*----------------------------------------------------------------------------*/
extern bool
pycasso_session_Session_add_instances(pycasso_session_Session *session,
                                      unsigned int bit_mask,
                                      size_t arche_vertices_count,
                                      const float *arche_vertices,
                                      size_t instances_count,
                                      size_t property_count,
                                      size_t *property_components_count,
                                      const float **properties,
                                      size_t *index);

#endif /* _PYCASSO_SESSION_H_326777659243943_ */
