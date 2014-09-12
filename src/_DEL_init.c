/* HEADER */
// Include stadard headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  // true

// Include pycasso headers
#include "../include/allheaders.h"

/*----------------------------------------------------------------------------*/
void
pycasso_init(pycasso_StaticResources *resources)
{
    // // Initialize DevIL
    // ilInit();

    // // Flip loaded images from thier upside down position
    // ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    // ilEnable(IL_ORIGIN_SET);

    // Set error callback
    glfwSetErrorCallback(pycasso_window_on_error);

    // Initialize GLFW
    if (!glfwInit())
    {
        printf("Failed to initialise GLFW\n");
        goto ERROR_GLFW_INIT;
    }

    // Set up generic window hints
    glfwWindowHint(GLFW_REFRESH_RATE, 60);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);

    // Set up OpenGL context samples and version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    // Set window title
    char window_title[WINDOW_TITLE_SIZE];
    pycasso_window_generate_title(window_title);

    // Create window
    // TODO: make size and title available for user!
    resources->window = glfwCreateWindow(512, 512, window_title, NULL, NULL);
    if (!resources->window)
    {
        printf("Failed to initialize window\n");
        goto ERROR_GLFW_WINDOW;
    }

    // Register event callbacks
    glfwSetKeyCallback(resources->window, pycasso_window_on_key_pressed);

    // Make the context of this window current on the calling thread
    glfwMakeContextCurrent(resources->window);

    // Initialise GLEW
    glewExperimental = true;
    GLenum status = glewInit();
    /*
     * Calling glewInit will create a GL_INVALID_ENUM error,
     * but that doesn't matter according to:
     * http://www.opengl.org/wiki/OpenGL_Loading_Library#GLEW
     * so */ glGetError(); /* has to be called to get rid of
     * the error and move on with GL_NO_ERROR
     */
    if (status != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        goto ERROR_GLEW_INIT;
    }

    // Load and store color fill shader resources
    resources->fs = malloc(sizeof(pycasso_FragShaders));
    const char *fs_type_name = "pycasso_FragShaders";
    if (!resources->fs)
    {
        printf("Couldn't allocated memory for '%s'.\n", fs_type_name);
        goto ERROR_RESOURCES;
    }
    const char* fs_shaders_paths[] = {
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_solid_color.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_linear_gradient.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_radial_gradient.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_conical_gradient.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "fill_texture.fs",

        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "shape_rectangle.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "shape_rounded_rectangle.fs",
        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "shape_circle.fs",

        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "main.fs",

        PYCASSO_SHADER_PATH PYCASSO_FRAGMENT_PATH "sys_grid.fs",
    };
    pycasso_shaders_load_and_compile_shaders(resources->fs,
                                             sizeof(pycasso_FragShaders)/sizeof(GLuint),
                                             fs_shaders_paths,
                                             sizeof(fs_shaders_paths)/sizeof(char*),
                                             fs_type_name,
                                             GL_FRAGMENT_SHADER);

    // Load and store vertex shader resources
    resources->vs = malloc(sizeof(pycasso_VertShaders));
    const char *vs_type_name = "pycasso_VertShaders";
    if (!resources->vs)
    {
        printf("Couldn't allocated memory for '%s'.\n", vs_type_name);
        exit(EXIT_FAILURE);
    }
    const char *vs_shaders_paths[] = {
        PYCASSO_SHADER_PATH PYCASSO_VERTEX_PATH "quad_color.vs",
        PYCASSO_SHADER_PATH PYCASSO_VERTEX_PATH "quad_texture.vs",
        PYCASSO_SHADER_PATH PYCASSO_VERTEX_PATH "sys_grid.vs",
    };
    pycasso_shaders_load_and_compile_shaders(resources->vs,
                                             sizeof(pycasso_VertShaders)/sizeof(GLuint),
                                             vs_shaders_paths,
                                             sizeof(vs_shaders_paths)/sizeof(char*),
                                             vs_type_name,
                                             GL_VERTEX_SHADER);

    // Create an empty instance for the first item
    pycasso_GeometryInstance *empty = malloc(sizeof(pycasso_GeometryInstance));
    empty->type = PYCASSO_GEO_EMPTY;
    empty->prev_instance = (void *)NULL;
    empty->next_instance = (void *)NULL;
    empty->geometry = (void *)NULL;

    // Store this empty item as last instance
    resources->last_instance = empty;

    return;

    // TODO: use label naming conventions here
    ERROR_RESOURCES:
    ERROR_GLEW_INIT:
        printf("%s\n", glewGetErrorString(status));
        glfwDestroyWindow(resources->window);
    ERROR_GLFW_WINDOW:
        glfwTerminate();
    ERROR_GLFW_INIT:
        exit(EXIT_FAILURE);
}


/*----------------------------------------------------------------------------*/
void
pycasso_new(pycasso_StaticResources *resources)
{
    pycasso_window_on_run(resources);
}


/*----------------------------------------------------------------------------*/
void
pycasso_destroy(pycasso_StaticResources *resources)
{
    // Delete shaders
    pycasso_shaders_unload_and_delete_shaders(resources->fs);
    pycasso_shaders_unload_and_delete_shaders(resources->vs);
    // Delete shader storages
    free(resources->fs);
    free(resources->vs);

    // Delete all instances
    pycasso_GeometryInstance *instance = resources->last_instance;
    pycasso_GeometryInstance *temporary;
    while (true)
    {
        if (instance->prev_instance == (void *)NULL) break;
        else
        {
            // Store next step in linked-list
            temporary = instance->prev_instance;
            // Delete
            switch (instance->type)
            {
                case PYCASSO_GEO_EMPTY: break;
                case PYCASSO_GEO_GRID:
                    pycasso_geo_grid_delete((pycasso_Grid *)instance->geometry);
                    break;
                case PYCASSO_GEO_ROUNDED_RECTANGLE:
                    pycasso_geo_rectangle_delete((pycasso_RoundedRectangle *)instance->geometry);
                    break;
                default: break;
            }
            // Step to the next element in the linked-list
            instance = temporary;
        }
    }

    // Delete instances storage
    free(resources->last_instance);

    // Destroy window and terminate all glfw processes
    glfwDestroyWindow(resources->window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
