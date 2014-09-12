// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                     File: include/_DEL_geo/rectangle.h                     //
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

#ifndef _PYCASSO_GEO_RECTANGLE_H_
#define _PYCASSO_GEO_RECTANGLE_H_

/*----------------------------------------------------------------------------*/
pycasso_RoundedRectangle *
pycasso_geo_rectangle_textured_init(pycasso_StaticResources *resources,
                                    GLfloat x,
                                    GLfloat y,
                                    GLfloat width,
                                    GLfloat height,
                                    const char *texture_path,
                                    GLfloat corner_radiuses[4]);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
pycasso_RoundedRectangle *
pycasso_geo_rectangle_colored_init(pycasso_StaticResources *resources,
                                   GLfloat x,
                                   GLfloat y,
                                   GLfloat width,
                                   GLfloat height,
                                   GLfloat color_angle,
                                   GLfloat color_base[4],
                                   GLfloat color_stop[4],
                                   GLfloat color_base_location,
                                   GLfloat color_stop_location,
                                   GLfloat corner_radiuses[4]);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_rectangle_delete(pycasso_RoundedRectangle *rectangle);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_rectangle_projection(pycasso_RoundedRectangle *rectangle,
                                 mat4x4 projection_matrix);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_rectangle_draw(pycasso_RoundedRectangle *rectangle);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_rectangle_dimension(pycasso_RoundedRectangle *rectangle,
                                GLfloat width,
                                GLfloat height);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_rectangle_position(pycasso_RoundedRectangle *rectangle,
                               GLfloat x,
                               GLfloat y);
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void
pycasso_geo_rectangle_texture(pycasso_RoundedRectangle *rectangle,
                              const char *texture_path);
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void
pycasso_geo_rectangle_color_base(pycasso_RoundedRectangle *rectangle,
                                 GLfloat new_color_array[4]);
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void
pycasso_geo_rectangle_color_stop(pycasso_RoundedRectangle *rectangle,
                                 GLfloat new_color_array[4]);
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void
pycasso_geo_rectangle_color_base_location(pycasso_RoundedRectangle *rectangle,
                                          GLfloat new_color_location);
/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
void
pycasso_geo_rectangle_color_stop_location(pycasso_RoundedRectangle *rectangle,
                                          GLfloat new_color_location);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_rectangle_color_angle(pycasso_RoundedRectangle *rectangle,
                                  GLfloat new_color_angle);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_rectangle_corner_radiuses(pycasso_RoundedRectangle *rectangle,
                                      GLfloat new_corner_radiuses[4]);

#endif
