/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                            File: src/session.c                             **
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
#include <stdio.h>    /* stderr */
#include <stdlib.h>   /* malloc(), free() */
#include <stdbool.h>  /* bool, true, false */

/* Include OpenGL/GLEW headers */
#include <GL/glew.h>

/* Include cutils headers */
#define CEXC_SET
#include <cutils/call.h>

/* Include internal pycasso headers */
#include "include/window.h"
#include "include/shader/resources.h"

/* TODO: Consider, if some sort of encapsulation needed in control.c:
   inside pycasso_session_run() there are GL functions.. is it good or bad?
   Does it make harder to switch between the different windowing libs (eg: GLFW)? */
/* TODO: fix sys_grid.fs + sys_grid.vs deviation on resizing */
/* TODO: move shader lists from init.c -> shader.h */
/* TODO: REFACTOR debug.h */
/* TODO: data types: System  : Window -> Region -> Layout -> Constraint
                     Geometry: Surface, Curve, Text */

/*----------------------------------------------------------------------------*/
/* Base object to store all the informations of a session */
typedef struct pycasso_session_session
{
    pycasso_window_Window *window;
    pycasso_shader_resources_Primitives *primitives;
} pycasso_session_Session;



/*----------------------------------------------------------------------------*/
bool
pycasso_session_Session_new(pycasso_session_Session **session)
{
    /* Start cutils exception handler */
    start_exception_handling(stderr);

    /* Exception raiser flags */
    bool exception_from_window_creation = false;

    /* Create a session object to store all informations about this session */
    pycasso_session_Session *_session =
        malloc(sizeof(pycasso_session_Session));
    if (!_session)
        goto Exception_From_Allocation;

    if (!pycasso_window_Window_new(&_session->window, 512, 512, "title"))
        goto Exception_From_Window_Creation;

    if (!pycasso_shader_resources_Primitives_new(&_session->primitives))
        goto Exception_From_Primitive_Resources_Creation;

    /* TODO: initialise FreeImage here ... */
    /* TODO: initialise FreeType here ... */

    /* Set session and return */
    *session = _session;
    return true;

    /* If something went wrong during the
       creation of the primitives' resources */
    Exception_From_Primitive_Resources_Creation:
        pycasso_window_Window_del(_session->window);

    /* If something went wrong during the
       creation of the window object */
    Exception_From_Window_Creation:
        exception_from_window_creation = true;
        free(_session);

    /* If something went wrong during the
       memory allocation of the session object */
    Exception_From_Allocation:
        if (!exception_from_window_creation)
            #undef  EXCEPTION_MESSAGE
            #define EXCEPTION_MESSAGE "Allocation of session failed"
            raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);
        *session = NULL;
        return false; /* Internal allocation failed */
}



/*----------------------------------------------------------------------------*/
bool
pycasso_session_Session_run(pycasso_session_Session *session,
                            void (*function)(pycasso_session_Session*))
{
    /* Previous initialisation of the session object failed */
    if (!session)
        return false;

    /* TODO: set this background color somewhere...
             if it set => remove GLEW header from this file !!! */
    static const GLfloat clear_color[] = {.46f, .71f, .67f, 1.f};
    static const GLfloat clear_depth = 1.f;

    /* Enable color-blending and depth test */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    pycasso_window_Window *window = session->window;
    while (!pycasso_window_Window_closed(window))
    {
        /* Clear color => create background */
        glClearBufferfv(GL_COLOR, 0, clear_color);
        glClearBufferfv(GL_DEPTH, 0, &clear_depth);

        /* Execute user-function */
        function(session);

        /* Draw all primitives */
        pycasso_shader_resources_Primitives_draw_all(session->primitives);

        /* Notify window, it is the end of the loop */
        pycasso_window_Window_on_end_loop(window);
    }
    /* Reset values */
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_ONE, GL_ZERO);
    glDisable(GL_BLEND);

    /* Bind and use nothing */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);

    /* Return indication everything was successful */
    return true;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_session_Session_del(pycasso_session_Session *session)
{
    if (!session)
        return false;

    pycasso_window_Window_del(session->window);

    /* Destroy the session of the session */
    free(session);

    /* Stop cutils exception handler */
    stop_exception_handling();
    return true;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_session_Session_add_instances(pycasso_session_Session *session,
                                      unsigned int bit_mask,
                                      size_t arche_vertices_count,
                                      const float *arche_vertices,
                                      size_t instances_count,
                                      size_t property_count,
                                      size_t *property_components_count,
                                      const float **properties,
                                      size_t *index)
{
    return pycasso_shader_resources_Primitives_add(session->primitives,
                                                   bit_mask,
                                                   arche_vertices_count,
                                                   arche_vertices,
                                                   instances_count,
                                                   property_count,
                                                   property_components_count,
                                                   properties,
                                                   index);
}
