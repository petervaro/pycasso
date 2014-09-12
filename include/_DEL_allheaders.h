// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                      File: include/_DEL_allheaders.h                       //
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

#ifndef _PYCASSO_ALL_HEADERS_H_
#define _PYCASSO_ALL_HEADERS_H_

// Third party headers
// #include <Python/Python.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// #include <IL/il.h>
#include "linmath/linmath.h"

// Pycasso headers
#include "types.h"        // This has to be the first one
#include "admin.h"
#include "texture.h"
#include "geo/types.h"
#include "geo/grid.h"
#include "geo/rectangle.h"
#include "utils/color.h"
#include "utils/calc.h"
#include "utils/fps.h"
#include "window.h"
#include "shaders.h"
#include "init.h"        // This has to be the last one

// Debugging
#define DEBUG 1
// #include "debug.h"

#endif
