// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//               File: shaders/fragment/fill_linear_gradient.fs               //
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

// TODO: make variable count of stops and colors
//       http://stackoverflow.com/questions/8099979/glsl-c-arrays-of-uniforms

uniform mat2  color_rotation;
uniform vec4  color_base;
uniform vec4  color_stop;
uniform float color_base_location;
uniform float color_stop_location;

void fill(in vec2 vertices, out vec4 color)
{
    // Linear gradient parameter
    float t = ((color_rotation*vertices).y - color_base_location) /
              (color_stop_location - color_base_location);

    // Calculate gradient color value
    color = mix(color_base, color_stop, t);
}