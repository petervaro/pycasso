// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//             File: shaders/fragment/shape_rounded_rectangle.fs              //
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

// OpenGL Shading Language Version 1.50
#version 150 core

uniform vec2  dimensions;
uniform vec4  radiuses;

/*  0-----1
    |     |  -> radiuses
    |     |
    3-----2  */

void shape(in vec2 vertices, out float alpha)
{
    // Top-left, Top-right, Bottom-right, Bottom-left
    vec2  tl, tr, br, bl;

    // Center of corner arcs
    tl = vec2( radiuses[0],                 dimensions[1] - radiuses[0] );
    tr = vec2( dimensions[0] - radiuses[1], dimensions[1] - radiuses[1] );
    br = vec2( dimensions[0] - radiuses[2], radiuses[2]                 );
    bl = vec2( radiuses[3],                 radiuses[3]                 );

    // vec2 coord = clamp(vertices, tl);

    // If Top-left
    if (vertices.x < tl.x && vertices.y > tl.y)
    {
        alpha = 1.f - smoothstep(radiuses[0] - .0075f, radiuses[0], distance(tl, vertices.xy));
    }
    // If Top-right
    else if (vertices.x > tr.x && vertices.y > tr.y)
    {
        alpha = 1.f - smoothstep(radiuses[1] - .0075f, radiuses[1], distance(tr, vertices.xy));
    }
    // If Bottom-right
    else if (vertices.x > br.x && vertices.y < br.y)
    {
        alpha = 1.f - smoothstep(radiuses[2] - .0075f, radiuses[2], distance(br, vertices.xy));
    }
    // If Bottom-left
    else if (vertices.x < bl.x && vertices.y < bl.y)
    {
        alpha = 1.f - smoothstep(radiuses[3] - .0075f, radiuses[3], distance(bl, vertices.xy));
    }
    // If straight edge
    else
    {
        alpha = 1.f;
    }
}