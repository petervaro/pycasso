/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                             File: src/window.c                             **
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

/* Include standard headers */
#include <string.h>   /* strlen() */
#include <stdio.h>    /* snprintf() */
#include <stddef.h>   /* size_t */
#include <stdlib.h>   /* malloc(), free() */
#include <stdbool.h>  /* bool, true, false */

/* Include GLEW headers (needs to be included before any GL related header) */
#include <GL/glew.h>

/* Include GLFW headers */
#include <GLFW/glfw3.h>

/* Include cutils headers */
#include <cutils/call.h>


/*----------------------------------------------------------------------------*/
/* Base type */
typedef struct pycasso_window_window
{
    GLFWwindow *window;
    size_t width;
    size_t height;
    char *title;
} pycasso_window_Window;



/*----------------------------------------------------------------------------*/
static void
__window_on_error(int error_code,
                  const char *error_note)
{
    #undef  ERROR_FMT
    #define ERROR_FMT "GLFW Error #%d: %s"

    /* Create a storage for message */
    size_t msg_len = snprintf(NULL, 0, ERROR_FMT, error_code, error_note);
    char exc_msg[msg_len];

    /* Format proper exception message */
    snprintf(exc_msg, msg_len, ERROR_FMT, error_code, error_note);
    /* Pass the error message to the exception handler */
    raise(exc_msg, msg_len);
}



/*----------------------------------------------------------------------------*/
static void
__window_on_frame_buffer_resize(GLFWwindow *window,
                                int width,
                                int height)
{
    glViewport(0, 0, width, height);
}



/*----------------------------------------------------------------------------*/
bool
pycasso_window_Window_new(pycasso_window_Window **window,
                          size_t width,
                          size_t height,
                          const char *title)
{
    /* Exception raiser flags */
    bool exception_from_glew = false,
         exception_from_glfw_init = false,
         exception_from_glfw_window = false;

    /* Create a window object */
    pycasso_window_Window *_window = malloc(sizeof(pycasso_window_Window));
    if (!_window) goto Exception_From_Pycasso_Window;

    /* Set error callback and initialise GLFW window */
    glfwSetErrorCallback(__window_on_error);
    if (!glfwInit()) goto Exception_From_Glfw_Init;

    /* Set up generic window hints */
    glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);

    /* Set up OpenGL context samples and version */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    GLFWwindow *glfw_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!glfw_window) goto Exception_From_Glfw_Window;

    /* Make the context of this window current on the calling thread */
    glfwMakeContextCurrent(glfw_window);

    // Initialise GLEW
    glewExperimental = GL_TRUE;
    GLenum glew_status = glewInit();
    /* Calling glewInit will create a GL_INVALID_ENUM error,
       but that doesn't matter according to:
       http://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
       so */ glGetError(); /* has to be called to get rid of
       the error and move on with GL_NO_ERROR */
    if (glew_status != GLEW_OK) goto Exception_From_Glew_Init;

    /* Call frame-buffer-resize initially and set it as a callback */
    __window_on_frame_buffer_resize(glfw_window, width, height);
    glfwSetFramebufferSizeCallback(glfw_window, __window_on_frame_buffer_resize);

    /* Set refresh rate */
// #define MEASURING_FPS
#ifdef MEASURING_FPS
    glfwSwapInterval(0);
#else
    glfwWindowHint(GLFW_REFRESH_RATE, 60);
#endif

    /* Set window and return if there were no exceptions */
    _window->window = glfw_window;
    *window = _window;
    return true;

    /* */
    Exception_From_Glew_Init:
        #undef  EXCEPTION_MESSAGE
        #define EXCEPTION_MESSAGE "Initialisation of extension wrangler failed"
        raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);
        const char *glew_error = (const char *)glewGetErrorString(glew_status);
        raise(glew_error, strlen(glew_error));
        glfwDestroyWindow(glfw_window);
        exception_from_glew = true;

    /* If creation of GLFW window failed */
    Exception_From_Glfw_Window:
        if (!exception_from_glew)
            #undef  EXCEPTION_MESSAGE
            #define EXCEPTION_MESSAGE "Creation of window failed"
            raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);
        glfwTerminate();
        exception_from_glfw_window = true;

    /* If initialisation of GLFW failed */
    Exception_From_Glfw_Init:
        if (!exception_from_glfw_window)
            #undef  EXCEPTION_MESSAGE
            #define EXCEPTION_MESSAGE "Initialisation of window failed"
            raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);
        free(_window);
        exception_from_glfw_init = true;

    /* If allocation of pycasso window object failed */
    Exception_From_Pycasso_Window:
        if (!exception_from_glfw_init)
            #undef  EXCEPTION_MESSAGE
            #define EXCEPTION_MESSAGE "Allocation of window failed"
            raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);
        *window = (pycasso_window_Window *)NULL;
        return false;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_window_Window_del(pycasso_window_Window *window)
{
    /* If previous initialisation of window object failed */
    if (!window)
        return false;

    /* Destroy GLFW window */
    glfwDestroyWindow(window->window);
    glfwTerminate();

    /* Destroy window */
    free(window);
    return true;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_window_Window_closed(pycasso_window_Window *window)
{
    /* TODO: this is very expensive -> check if window was
             created successfully, and in this function only
             ask the GLFWwindow if it needs to be closed or not */
    if (!window)
        return true;
    return (bool)glfwWindowShouldClose(window->window);
}



/*----------------------------------------------------------------------------*/
void
pycasso_window_Window_on_end_loop(pycasso_window_Window *window)
{
    glfwSwapBuffers(window->window);
    glfwPollEvents();
}
