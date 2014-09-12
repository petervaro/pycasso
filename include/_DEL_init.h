// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                         File: include/_DEL_init.h                          //
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

#ifndef _PYCASSO_INIT_H_
#define _PYCASSO_INIT_H_

/*----------------------------------------------------------------------------*/
void pycasso_init(pycasso_StaticResources *resources);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void pycasso_new(pycasso_StaticResources *resources);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void pycasso_destroy(pycasso_StaticResources *resources);

#endif