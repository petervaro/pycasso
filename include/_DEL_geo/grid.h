// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                       File: include/_DEL_geo/grid.h                        //
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

#ifndef _PYCASSO_GEO_GRID_H_
#define _PYCASSO_GEO_GRID_H_

/*----------------------------------------------------------------------------*/
pycasso_Grid *
pycasso_geo_grid_init(pycasso_StaticResources *resources,
                      GLfloat h_space,
                      GLfloat v_space,
                      GLfloat color[4]);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_grid_delete(pycasso_Grid *grid);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_grid_draw(pycasso_Grid *grid,
                      GLfloat width,
                      GLfloat height);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_grid_update_dimensions(pycasso_Grid *grid,
                                   GLfloat width,
                                   GLfloat height);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_grid_position_and_dimensions(pycasso_Grid *grid,
                                         GLfloat width,
                                         GLfloat height);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_grid_color(pycasso_Grid *grid,
                       GLfloat color[4]);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_geo_grid_spaces(pycasso_Grid *grid,
                        GLfloat h_space,
                        GLfloat v_space);

#endif
