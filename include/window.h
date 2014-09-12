/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                           File: include/window.h                           **
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

#ifndef _PYCASSO_WINDOW_H_13121843944067568_
#define _PYCASSO_WINDOW_H_13121843944067568_

/* Include standard headers */
#include <stddef.h>   /* size_t */
#include <stdbool.h>  /* bool */

/*----------------------------------------------------------------------------*/
typedef struct pycasso_window_window pycasso_window_Window;

/*----------------------------------------------------------------------------*/
extern bool
pycasso_window_Window_new(pycasso_window_Window **window,
                          size_t width,
                          size_t height,
                          const char *title);

/*----------------------------------------------------------------------------*/
extern bool
pycasso_window_Window_del(pycasso_window_Window *window);

/*----------------------------------------------------------------------------*/
extern bool
pycasso_window_Window_closed(pycasso_window_Window *window);

/*----------------------------------------------------------------------------*/
extern void
pycasso_window_Window_on_end_loop(pycasso_window_Window *window);

#endif /* _PYCASSO_WINDOW_H_13121843944067568_ */
