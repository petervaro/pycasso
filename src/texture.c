// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                            File: src/texture.c                             //
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

// Include stadard headers
#include <stdio.h>    // printf()
#include <stdbool.h>  // bool
#include <FreeImage.h>

// Include pycasso headers
#include "../include/allheaders.h"

/*----------------------------------------------------------------------------
void
pycasso_texture_(GLuint *texture_id,
                 const char *file_path,
                 bool repeat_image,
                 bool soft_zoom)
{
    FIBITMAP *bitmap = NULL;
    FREE_IMAGE_FORMAT format = 0;

    // Try to get image format
    format = FreeImage_GetFileType(file_path, 0);
    if (!format)
    {
        format = FreeImage_GetFIFFromFilename(file_path);
        if (!format) goto Error_Detect_Image_Format;
    }

    // Check if format is supported
    if (!FreeImage_FIFSupportsReading(format)) goto Error_Unsupported_Format;

    // Try to load image
    FIBITMAP *bitmap = FreeImage_Load(format, file_path, 0);
    if (!bitmap) goto Error_Load_Image;

    switch (FreeImage_GetBPP(bitmap))
    {
        case 32: x = GL_BGRA; break;
        case 24: x = GL_BGR;  break;
        case  8: x = GL_LUMINANCE; break;

    }

    // Try to convert image
    BYTE *rawbits = FreeImage_GetBits(FreeImage_ConvertToRawBits(bitmap));
    if (!converted_bitmap) goto Error_Convert_Image;

    // Create and bind image as OpenGL texture
    glGenTextures(1, texture_id);
    glBindTexture(GL_TEXTURE_2D, *texture_id);

    // Set what to do when it is magnified and minified
    GLuint zoom = soft_zoom ? GL_LINEAR : GL_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, zoom);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, zoom);

    // Set image to repeat or not
    GLuint repeat = repeat_image ? GL_REPEAT : GL_CLAMP_TO_EDGE;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA8,
                 FreeImage_GetWidth(bitmap),
                 FreeImage_GetHeight(bitmap);
                 0,
                 GL_BGRA,
                 GL_UNSIGNED_BYTE,
                 (void *)FreeImage_ConvertToRawBits(bitmap));
    // Clean up and return
    glBindTexture(GL_TEXTURE_2D, 0);
    FreeImage_Unload(bitmap);
    return;

    // Except errors
    Error_Unsupported_Format:;
    Error_Convert_Image:;
    Error_Load_Image:
        printf("Unable to load image '%s'\n", filepath);
        FreeImage_Unload(bitmap);
    Error_Detect_Image_Format:
        printf("Unable to identify format of image file '%s'\n", file_path);
        *texture_id = 0;
}*/

/*----------------------------------------------------------------------------*/
void
pycasso_texture_load_image_to_texture(GLuint *texture_id,
                                      const char *file_path,
                                      bool repeat_image,
                                      bool soft_zoom)
{
    // Create image ID and bind it
    ILuint image = ilGenImage();
    ilBindImage(image);
    // Load image and check if succeded
    ILboolean load_state = ilLoadImage(file_path);
    if (!load_state)
    {
        printf("Failed to load image '%s'\n", file_path);
        ilBindImage(0);
        ilDeleteImage(image);
        *texture_id = 0;
        return;
    }
    // Convert image and check if succeded
    ILboolean convert_state = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    if (!convert_state)
    {
        printf("Failed to convert image '%s'\n", file_path);
        ilBindImage(0);
        ilDeleteImage(image);
        *texture_id = 0;
        return;
    }
    // Create and bind image as OpenGL texture
    glGenTextures(1, texture_id);
    glBindTexture(GL_TEXTURE_2D, *texture_id);

    // Set what to do when it is magnified and minified
    GLuint zoom = soft_zoom ? GL_LINEAR : GL_NEAREST;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, zoom);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, zoom);

    // Set image to repeat or not
    GLuint repeat = repeat_image ? GL_REPEAT : GL_CLAMP_TO_EDGE;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeat);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeat);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 ilGetInteger(IL_IMAGE_FORMAT),
                 ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT),
                 0,
                 ilGetInteger(IL_IMAGE_FORMAT),
                 ilGetInteger(IL_IMAGE_TYPE),
                 ilGetData());
    // Clean up
    glBindTexture(GL_TEXTURE_2D, 0);
    ilBindImage(0);
    ilDeleteImage(image);
}
