/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                       File: include/geo/rectangle.h                        **
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

#ifndef _PYCASSO_GEO_RECTANGLE_H_13940166087240458_
#define _PYCASSO_GEO_RECTANGLE_H_13940166087240458_

/* Include standard headers */
#include <stdbool.h>  /* bool */

/* Include internal pycasso headers */
#include <pycasso/session.h>

typedef struct {} pycasso_geo_rectangle_Rectangle;

/*----------------------------------------------------------------------------*/
extern bool
pycasso_geo_rectangle_Rectangle_new(pycasso_geo_rectangle_Rectangle **rectangle,
                                    pycasso_session_Session *session);

#endif /* _PYCASSO_GEO_RECTANGLE_H_13940166087240458_ */
