// INFO ////////////////////////////////////////////////////////////////////////
//                                                                            //
//                                  pycasso                                   //
//                                  =======                                   //
//                                                                            //
//    Cross-platform, hardware accelerated, constraint based GUI framework    //
//                       Version: 0.5.02.035 (20140911)                       //
//                                                                            //
//                          File: src/_DEL_window.c                           //
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

// Include standard headers
#include <stdio.h>
#include <stdlib.h>   // srand(), rand()
#include <time.h>     // time()
#include <string.h>
#include <math.h>     // M_PI

// Include pycasso headers
#include "../include/allheaders.h"
#include "../include/debug.h"

/*----------------------------------------------------------------------------*/
void
pycasso_window_generate_title(char *string_buffer)
{
    // Open file
    FILE *version_file = fopen(VERSION_FILE_NAME, "r");

    // Try to load file to buffer
    char version_buff[VERSION_BUFF_SIZE];
    if (version_file == NULL)
    {
        fclose(version_file);
        printf("File cannot be opened: '%s'\n", VERSION_FILE_NAME);
        version_buff[0] = '\0';
    }
    else
    {
        fgets(version_buff, VERSION_BUFF_SIZE, version_file);
        fclose(version_file);
    }

    // Concatenate strings
    strcpy(string_buffer, "Pycasso ");
    strcat(string_buffer, version_buff);
}


/*----------------------------------------------------------------------------*/
void
pycasso_window_on_error(int error, const char* description)
{
    fputs(description, stderr);
}


/*----------------------------------------------------------------------------*/
void
pycasso_window_on_key_pressed(GLFWwindow *window,
                              int key,
                              int scancode,
                              int action,
                              int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

#define RECT_TEST_NUM 32
/*----------------------------------------------------------------------------*/
void
pycasso_window_on_run(pycasso_StaticResources *resources)
{
    // Specify clear color (background)
    // TODO: make background color and blending available for user
    // float clear_color[3];
    // pycasso_color_str_to_rgb("000000", clear_color);
    // glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.f);
    glClearColor(.46f, .71f, .67f, 1.f);

    // Set blending and alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set projection matrix to identity matrices
    mat4x4_identity(resources->projection_matrix); // Camera space -> Screen

    pycasso_Grid *grid = pycasso_geo_grid_init(resources,
                       /* horizontal space */  16.f,
                          /* vertical space */ 16.f,
                           /* color of grid */ (GLfloat[]){0.f, 0.f, 0.f, .25f});

    // Declare variables
    pycasso_RoundedRectangle *rectangles[RECT_TEST_NUM];
    pycasso_RoundedRectangle *rectangle;

    srand(time(NULL));
    int i;
    float x, y, w, h, r, tl, tr, br, bl;
    for (i=0; i<RECT_TEST_NUM; i++)
    {
        x  = (float)(rand() % 486) + 10.f;
        y  = (float)(rand() % 486) - 10.f;
        w  = (float)(rand() % 128) + 32.f;
        h  = (float)(rand() % 128) + 32.f;
        r  = (float)(rand() % 360);
        tl = (float)(rand() % 16);
        tr = (float)(rand() % 16);
        br = (float)(rand() % 16);
        bl = (float)(rand() % 16);
        // Initialise rectangle
        rectangle = pycasso_geo_rectangle_colored_init(resources,
                                              /* x */  x,//(i+x)*32.f,
                                              /* y */  y,//(i+y)*24.f,
                                          /* width */  w,
                                         /* height */  h,
                                    /* color_angle */  r,
                                     /* base color */  (GLfloat[]){.07f, .11f, .1f, 0.f},
                                     /* stop color */  (GLfloat[]){.99f, .37f, .39f, 1.f},
                            /* base color location */  0.f,
                            /* stop color location */  1.f,
             /* top left, righ; bottom right, left */  (GLfloat[]){tl, tr, br, bl});
          // Store rectangle
        rectangles[i] = rectangle;
    }

    // Initialise rectangle
    rectangle = pycasso_geo_rectangle_textured_init(resources,
                                           /* x */  50.f,
                                           /* y */  50.f,
                                       /* width */  412.f,
                                      /* height */  412.f,
                                /* texture file */  "img/test.png",
          /* top left, righ; bottom right, left */  (GLfloat[]){16.f, 32.f, 64.f, 128.f});

    // Initial values
    int viewport_curr_width,
        viewport_curr_height,
        viewport_prev_width  = 0,
        viewport_prev_height = 0;

    // Enter event loop
    while (!glfwWindowShouldClose(resources->window))
    {
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);

        // Get viewport's FB size
        glfwGetFramebufferSize(resources->window,
                               &viewport_curr_width,
                               &viewport_curr_height);
        glViewport(0, 0, viewport_curr_width, viewport_curr_height);

        // Update projection matrix only if viewport size has changed
        if (viewport_curr_width  != viewport_prev_width ||
            viewport_curr_height != viewport_prev_height)
        {
            // Set projection matrix to ortho
            mat4x4_ortho(resources->projection_matrix,
             /* Left */  0.f,
            /* Right */  (float)viewport_curr_width,
           /* Bottom */  (float)viewport_curr_height,
              /* Top */  0.f,
             /* Near */  -10.f,
              /* Far */  +10.f);

            // Set new matrix in shader programs
            for (int i=0; i<RECT_TEST_NUM; i++)
                pycasso_geo_rectangle_projection(rectangles[i], resources->projection_matrix);

            // Set new values
            viewport_prev_width  = viewport_curr_width;
            viewport_prev_height = viewport_curr_height;
        }

        // Draw grid
        pycasso_geo_grid_draw(grid, (float)viewport_curr_width, (float)viewport_curr_height);
        // Draw textured rectangle instance
        // pycasso_geo_rectangle_draw(rectangle);
        // Draw linear gradient rectangle instances
        for (i=0; i<RECT_TEST_NUM; i++) pycasso_geo_rectangle_draw(rectangles[i]);

        // Show what we rendered in the
        // background to the frame buffer
        glfwSwapBuffers(resources->window);
        // Catch close, resize and other stuffs
        // glfwWaitEvents();
        // Print FPS
        glfwPollEvents(); printfps();
    }

    // Set blending back to original
    glBlendFunc(GL_ONE, GL_ZERO);
    glDisable(GL_BLEND);
}
