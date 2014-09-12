/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                            File: include/api.h                             **
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

#ifndef _PYCASSO_API_H_4239000157417341_
#define _PYCASSO_API_H_4239000157417341_

/* Include OpenGL/GLEW headers */
#include <GL/glew.h>

/* Include cutils headers */
#include <cutils/carg.h>

/* Include pycasso headers */
#include <pycasso/rectangle.h>

/*----------------------------------------------------------------------------*/
/* Functions and methods called with default values */
#undef __pycasso_vargs_fill
#undef __pycasso_single_fill
#undef __pycasso_double_fill
#define __pycasso_single_fill(object, type, value) \
    __pycasso_generic_fill(object, type, 1, ..., NULL)
#define __pycasso_double_fill(object, type, count, value)
    __pycasso_generic_fill(object, type, count, value, ((GLfloat[]){0.f, 1.f}))
#define __pycasso_vargs_fill(...) cutils_carg_vargs(__VA_ARGS__)(6)(__VA_ARGS__, \
    __pycasso_generic_fill, __pycasso_generic_fill, __pycasso_double_fill, \
    __pycasso_single_fill, __pycasso_generic_fill, __pycasso_generic_fill)(__VA_ARGS__)


/*----------------------------------------------------------------------------*/
#ifndef PYCASSO_NAMESPACE /* Use unprefixed token names */

#undef new
#undef del
#undef pos
#undef pos_x
#undef pos_y
#undef dim
#undef dim_width
#undef dim_height
#undef fill

#define new(...) __pycasso_generic_new(__VA_ARGS__)
#define del(...) __pycasso_generic_del(__VA_ARGS__)
#define pos(...) __pycasso_generic_pos(__VA_ARGS__)
#define x(...) __pycasso_generic_x(__VA_ARGS__)
#define y(...) __pycasso_generic_y(__VA_ARGS__)
#define dim(...) __pycasso_generic_dim(__VA_ARGS__)
#define width(...) __pycasso_generic_width(__VA_ARGS__)
#define height(...) __pycasso_generic_height(__VA_ARGS__)
#define fill(...) __pycasso_vargs_fill(__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#else /* PYCASSO_NAMESPACE Use prefixed token names */

#undef pycasso_new
#undef pycasso_del
#undef pycasso_pos
#undef pycasso_pos_x
#undef pycasso_pos_y
#undef pycasso_dim
#undef pycasso_dim_width
#undef pycasso_dim_height
#undef pycasso_fill

#define pycasso_new(...) __pycasso_generic_new(__VA_ARGS__)
#define pycasso_del(...) __pycasso_generic_del(__VA_ARGS__)
#define pycasso_pos(...) __pycasso_generic_pos(__VA_ARGS__)
#define pycasso_x(...) __pycasso_generic_x(__VA_ARGS__)
#define pycasso_y(...) __pycasso_generic_y(__VA_ARGS__)
#define pycasso_dim(...) __pycasso_generic_dim(__VA_ARGS__)
#define pycasso_width(...) __pycasso_generic_width(__VA_ARGS__)
#define pycasso_height(...) __pycasso_generic_height(__VA_ARGS__)
#define pycasso_fill(...) __pycasso_vargs_fill(__VA_ARGS__)

#endif /* PYCASSO_NAMESPACE */

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_new
#define __pycasso_generic_new(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle**: pycasso_geo_rectangle_Rectangle_new)\
    (object,##__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_del
#define __pycasso_generic_del(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle*: pycasso_geo_rectangle_Rectangle_del)\
    (object,##__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_pos
#define __pycasso_generic_pos(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle*: pycasso_geo_rectangle_Rectangle_pos)\
    (object,##__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_pos_x
#define __pycasso_generic_x(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle*: pycasso_geo_rectangle_Rectangle_pos_x)\
    (object,##__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_pos_y
#define __pycasso_generic_y(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle*: pycasso_geo_rectangle_Rectangle_pos_y)\
    (object,##__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_dim
#define __pycasso_generic_dim(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle*: pycasso_geo_rectangle_Rectangle_dim)\
    (object,##__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_dim_width
#define __pycasso_generic_width(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle*: pycasso_geo_rectangle_Rectangle_dim_width)\
    (object,##__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_dim_height
#define __pycasso_generic_height(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle*: pycasso_geo_rectangle_Rectangle_dim_height)\
    (object,##__VA_ARGS__)

/*----------------------------------------------------------------------------*/
#undef __pycasso_generic_fill
#define __pycasso_generic_fill(object, ...) _Generic((object),\
    pycasso_geo_rectangle_Rectangle*: pycasso_geo_rectangle_Rectangle_fill)\
    (object,##__VA_ARGS__)

#endif /* _PYCASSO_API_H_4239000157417341_ */
