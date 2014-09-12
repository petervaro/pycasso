// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                       File: include/utils/_DEL_fps.h                       //
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

#ifndef _PYCASSO_UTILS_FPS_H_
#define _PYCASSO_UTILS_FPS_H_

#include <stdio.h>          // fprintf()

// TODO: At the moment in a single scope only the first appearence of
//       these functions will work. NOTE: If you want to use both printfps
//       and getfps at the same time, use the getfps function only, and pass
//       a getter function which can also implement the printing functionality

/*----------------------------------------------------------------------------*/
static inline void
getfps(double (*gettime)(void),
       void (*getter)(int, void*),
       void *data)
{
    static double old_time = 0.0;
    static double time_sum = 0.0;
    static float  interval = 1.f;
    static int    fpscount = 0;

    double new_time  = gettime();
    time_sum += new_time - old_time;
    old_time = new_time;
    fpscount++;

    if (time_sum > interval)
    {
        getter(fpscount, data);
        fpscount = 0;
        time_sum = 0;
    }
}


/*----------------------------------------------------------------------------*/
static inline void
__printfps_getter_func(int fps, void *data)
{
    fprintf(stdout, "FPS: %d\n", fps);
}


/*----------------------------------------------------------------------------*/
static inline void
printfps(double (*gettime)(void))
{
    getfps(gettime, __printfps_getter_func, NULL);
}

#endif
