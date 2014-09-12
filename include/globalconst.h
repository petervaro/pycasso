/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                        File: include/globalconst.h                         **
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

#ifndef _PYCASSO_GLOBAL_CONSTANTS_H_3084587937539387_
#define _PYCASSO_GLOBAL_CONSTANTS_H_3084587937539387_

#define NO_BIT_ID         0x0000

#define QUAD_COLOR        0x0001
#define QUAD_TEXTURE      0x0002
#define SYS_GRID          0x0004
#define CIRCLE            0x0008
#define RECTANGLE         0x0010
#define ROUNDED_RECTANGLE 0x0020
#define SOLID_COLOR       0x0040
#define TEXTURE           0x0080
#define LINEAR_GRADIENT   0x0100
#define RADIAL_GRADIENT   0x0200
#define CONICAL_GRADIENT  0x0400

 /* L = 0x0800,
    M = 0x1000,
    N = 0x2000,
    O = 0x4000,
    P = 0x8000 */

/* API Ideas:

    new(session, &rect);
    pos(rect, 10.f, 10.f);
    dim(rect, 200.f, 120.f);

    fill(rect, SOLID_COLOR, "#ff00ff");
    fill(rect, TEXTURE, "texture.png");
    fill(rect, LINEAR_GRADIENT, 2, (char*[]){"#ff00ff", "#00ffff"});
    fill(rect, RADIAL_GRADIENT, 3, ((char*[]){"#ff00ff", "#ffff00", "#00ffff"}),
                                   ((GLfloat[]){0.f, .5f, 1.f}))

    show(rect);
    hide(rect);

    front(rect);
    back(rect);

    del(rect);

    color()
    texture()
    linear()
    radial()
    conical()

    new() */

#endif /* _PYCASSO_GLOBAL_CONSTANTS_H_3084587937539387_ */