// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                        File: include/utils/color.h                         //
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

#ifndef _PYCASSO_UTILS_COLOR_H_
#define _PYCASSO_UTILS_COLOR_H_

#include <stdlib.h>  // strtol()

/*----------------------------------------------------------------------------*/
/* Converts hexadecimal string value and into 0..1 float values
 * and places the values into the f_rgb float array */
static inline void
pycasso_color_str_to_rgb(char *c_rgb, float f_rgb[4])
{
    int j = 0;
    for (int i=0; i < 6; i+=2)
    {
        char hex[] = {'0', 'x', c_rgb[i], c_rgb[i+1], '\0'};
        f_rgb[j++] = (float)strtol(hex, NULL, 16)/255.f;
    }
}

#endif
