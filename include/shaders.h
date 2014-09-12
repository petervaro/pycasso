// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                          File: include/shaders.h                           //
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

#ifndef _SHADERS_H_
#define _SHADERS_H_

#define PYCASSO_SHADER_PATH "shaders/"
#define PYCASSO_FRAGMENT_PATH "fragment/"
#define PYCASSO_VERTEX_PATH "vertex/"

/*----------------------------------------------------------------------------*/
void
pycasso_shaders_create_shader_from_file(GLuint *shader_id,
                                        GLchar *file_path,
                                        GLenum shader_type);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_shaders_load_and_compile_shaders(void *shader_storage,
                                         int size_of_shader_storage,
                                         const char **shader_paths,
                                         int size_of_shader_paths,
                                         const char *struct_type_name,
                                         GLenum shader_type);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_shaders_unload_and_delete_shaders(void *shaders_storage);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_shaders_create_and_load_program(GLuint *program_id,
                                        GLuint num_of_shaders,
                                        GLuint shaders[]);
/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
void
pycasso_shaders_unload_and_delete_program(pycasso_ShaderProgram *program);

#endif
