/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                        File: src/shader/resources.c                        **
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
#include <stddef.h>   /* size_t */
#include <stdbool.h>  /* bool, true, false */

/* Include OpenGL/GLEW headers */
#include <GL/glew.h>

/* Include cutils headers */
#include <cutils/call.h>

/* Include internal pycasso headers */
#include "include/shader/helper.h"
#include "include/shader/program.h"
#include "include/globalconst.h"

/* Include external resources */
#include "resources/shaders.h"   /* SHADER_SOURCES */

/* Constant, based on the external resource */
#define SHADER_COUNT (sizeof SHADER_SOURCES / sizeof(char*))

/*----------------------------------------------------------------------------*/
enum
{
    vertex_coordinates, /* This has to be the first item */
    texture_coordinates,
    projection_mat,
    view_mat,
    model_mat,
    dimensions,
    radiuses,
    texture,
    texture_sampler,
    color_base,
    color_stop,
    color_base_position,
    color_stop_position,
    color_base_location,
    color_stop_location,
    color_rotation,
    color_position,
};


/*----------------------------------------------------------------------------*/
/* Object to store an input name and
   the preferred layout position index and
   the number of the components the input takes */
typedef struct
{
    size_t pos;        /* Layout position */
    size_t comp;       /* Component count of the input */
    const char *name;  /* Input name */
} ShaderInput;



/*----------------------------------------------------------------------------*/
#define INPUT_NAME(input, count) {.name=#input, .comp=count, .pos=input}
static const ShaderInput SHADER_INPUT_NAMES[] =
{
    [vertex_coordinates] = INPUT_NAME(vertex_coordinates, 2),
    [texture_coordinates] = INPUT_NAME(texture_coordinates, 2),
    [projection_mat] = INPUT_NAME(projection_mat, 16),
    [view_mat] = INPUT_NAME(view_mat, 16),
    [model_mat] = INPUT_NAME(model_mat, 16),
    [dimensions] = INPUT_NAME(dimensions, 2),
    [radiuses] = INPUT_NAME(radiuses, 4),
    [texture] = INPUT_NAME(texture, 2),
    [texture_sampler] = INPUT_NAME(texture_sampler, 3),
    [color_base] = INPUT_NAME(color_base_position, 4),
    [color_stop] = INPUT_NAME(color_base_position, 4),
    [color_base_position] = INPUT_NAME(color_base_position, 1),
    [color_stop_position] = INPUT_NAME(color_stop_position, 1),
    [color_base_location] = INPUT_NAME(color_base_location, 1),
    [color_stop_location] = INPUT_NAME(color_stop_location, 1),
    [color_rotation] = INPUT_NAME(color_rotation, 8),
    [color_position] = INPUT_NAME(color_position, 2),
};
#undef INPUT_NAME
#define MAX_SHADER_INPUT_NAMES \
    (sizeof SHADER_INPUT_NAMES / sizeof(ShaderInput))



/*----------------------------------------------------------------------------*/
/* Object to store input names and the number of names */
typedef struct
{
    size_t bit;                                /* Bit ID of shader */
    size_t len;                                /* Number of inputs */
    const ShaderInput *ins[MAX_SHADER_INPUT_NAMES];  /* Input names */
} ShaderPrefs;



/*----------------------------------------------------------------------------*/
#define INPUT(index) SHADER_INPUT_NAMES + index
/* Constant array to store the number of inputs of a shader,
   the name of the input and length of the name of the input */
static const ShaderPrefs SHADER_PREFS[] =
{
    [MAIN_VS] = {.bit=NO_BIT_ID,
                 .len=1,
                 .ins={INPUT(vertex_coordinates)}},

    [QUAD_COLOR_VS] = {.bit=QUAD_COLOR,
                       .len=0},
                       // .ins={INPUT(projection_mat),
                       //       INPUT(view_mat),
                       //       INPUT(model_mat)}},

    [QUAD_TEXTURE_VS] = {.bit=QUAD_TEXTURE,
                         .len=3,
                         .ins={INPUT(projection_mat),
                               INPUT(view_mat),
                               INPUT(model_mat)}},

    [SYS_GRID_VS] = {.bit=SYS_GRID,
                     .len=2,
                     .ins={INPUT(projection_mat),
                           INPUT(view_mat)}},

    [MAIN_FS] = {.bit=NO_BIT_ID, .len=0},

    [SHAPE_CIRCLE_FS] = {.bit=CIRCLE, .len=0},

    [SHAPE_RECTANGLE_FS] = {.bit=RECTANGLE, .len=0},

    [SHAPE_ROUNDED_RECTANGLE_FS] = {.bit=ROUNDED_RECTANGLE,
                                    .len=2,
                                    .ins={INPUT(dimensions),
                                          INPUT(radiuses)}},

    [FILL_SOLID_COLOR_FS] = {.bit=SOLID_COLOR,
                             .len=1,
                             .ins={INPUT(color_base)}},

    [FILL_TEXTURE_FS] = {.bit=TEXTURE,
                         .len=2,
                         .ins={INPUT(texture),
                               INPUT(texture_sampler)}},

    [FILL_LINEAR_GRADIENT_FS] = {.bit=LINEAR_GRADIENT,
                                 .len=5,
                                 .ins={INPUT(color_rotation),
                                       INPUT(color_base),
                                       INPUT(color_stop),
                                       INPUT(color_base_location),
                                       INPUT(color_stop_location)}},

    [FILL_RADIAL_GRADIENT_FS] = {.bit=RADIAL_GRADIENT,
                                 .len=5,
                                 .ins={INPUT(color_position),
                                       INPUT(color_base),
                                       INPUT(color_stop),
                                       INPUT(color_base_location),
                                       INPUT(color_stop_location)}},

    [FILL_CONICAL_GRADIENT_FS] = {.bit=CONICAL_GRADIENT, .len=0},
};
#undef INPUT



/*----------------------------------------------------------------------------*/
/* The Primitive-resources object stores all the ShaderProgram
   objects and all the available compiled shader IDs */
typedef struct pycasso_shader_resources_primitives
{
    DynamicArray_void_ptr *programs;  /* array of ShaderPrograms */
    GLuint shaders[SHADER_COUNT];     /* array of shader IDs */
} pycasso_shader_resources_Primitives;



/*----------------------------------------------------------------------------*/
/* The ShaderProgram object stores the ID of a successfully
   compiled and linked shader-program, and all the IDs of
   the compiled shaders the shader program is using */
typedef struct shader_program
{
    GLuint id;                       /* shader-program ID */
    DynamicArray_void_ptr *shaders;  /* array of shader IDs (GLuints) */
} ShaderProgram;



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_resources_Primitives_new(pycasso_shader_resources_Primitives **resources)
{
    /* Exception raiser flags */
    bool exception_from_shader_creation = false;

    /* Create primitive resources */
    pycasso_shader_resources_Primitives *_resources =
        malloc(sizeof(pycasso_shader_resources_Primitives));
    if (!_resources) goto Exception_From_Allocation;

    /* Local reference */
    GLuint *shaders = _resources->shaders;

    /* Create and compile all shaders */
    size_t compiled_shader_count;
    for (size_t i=0; i<SHADER_COUNT; compiled_shader_count=i++)
        if (!pycasso_shader_helper_create_and_compile_shader(shaders + i,
                                                             SHADER_SOURCES[i],
                                                             i<MAIN_FS ? GL_VERTEX_SHADER
                                                                       : GL_FRAGMENT_SHADER))
            goto Exception_From_Shader_Creation;

    /* Create a DynamicArray to store ShaderProgram objects */
    if (!new(&_resources->programs, sizeof(ShaderProgram), 64, NULL))
        goto Exception_From_DynamicArray_Allocation;

    /* Store primitive-resources object */
    *resources = _resources;
    return true;

    /* If allocation of dynamic array failed */
    Exception_From_DynamicArray_Allocation:;

    /* If something went wrong during the creation
       and compilation of one of the shaders */
    Exception_From_Shader_Creation:
        pycasso_shader_helper_delete_shaders(compiled_shader_count, shaders);
        free(_resources);
        exception_from_shader_creation = true;

    /* If allocation of primitive-resources object failed */
    Exception_From_Allocation:
        if (!exception_from_shader_creation)
            #undef  EXCEPTION_MESSAGE
            #define EXCEPTION_MESSAGE "Primitives Resources: allocation failed"
            raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);

        *resources = NULL;
        return false;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_resources_Primitives_del(pycasso_shader_resources_Primitives *resources)
{
    if (!resources)
        return false;

    /* Local reference */
    DynamicArray_void_ptr *programs = resources->programs;
    /* Delete all shader programs */
    ShaderProgram *program;
    for (size_t i=0; i<len(programs); i++)
    {
        program = *(ShaderProgram **)get(programs, i);
        pycasso_shader_helper_unload_and_delete_program(program->id,
                                                        len(program->shaders),
                                                        raw(program->shaders));
    }

    /* Delete shader programs array */
    del(programs);
    /* Delete all shaders */
    pycasso_shader_helper_delete_shaders(SHADER_COUNT, resources->shaders);

    /* Destroy resources and return indicating success */
    free(resources);
    return true;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_resources_Primitives_add(pycasso_shader_resources_Primitives *resources,
                                        unsigned int bit_id,
                                        const size_t arche_vertices_count,
                                        const GLfloat *arche_vertices,
                                        const size_t instance_count,
                                        const size_t property_count,
                                        const size_t *property_components_count,
                                        const GLfloat **properties,
                                        size_t *index)
{
    /* The program which will draw the primitive */
    pycasso_shader_program_Program *program;

    /* If program already exists */
    size_t program_index;
    if (find(resources->programs,
             pycasso_shader_program_Program_compare,
             &bit_id,
             &program_index))
    {
        program = (pycasso_shader_program_Program *)get(resources->programs,
                                                        program_index);
    }
    /* If create a new program object */
    else
    {
        /* Counters */
        size_t i, j,
               shader_count       = 0,
               layout_input_count = 0;

        /* Temporary storages */
        GLuint shader_ids[SHADER_COUNT],
               layout_input_positions[MAX_SHADER_INPUT_NAMES * SHADER_COUNT],
               layout_input_component_count[MAX_SHADER_INPUT_NAMES * SHADER_COUNT];
        const GLchar *layout_input_names[MAX_SHADER_INPUT_NAMES * SHADER_COUNT];

        /* Temporary pointers */
        const ShaderInput *input;
        const ShaderPrefs *prefs;

        /* Store shader and properties according to the bit-mask */
        for (i=1; i<SHADER_COUNT; i++)
        {
            prefs = SHADER_PREFS + i;
            /* If shader bit-ID is in bit-mask */
            if (bit_id & prefs->bit)
            {
                /* Store shader ID */
                shader_ids[shader_count] = resources->shaders[i];
                /* Get shader input properties and store them */
                for (j=0; j<prefs->len; j++)
                {
                    input = prefs->ins[j];
                    layout_input_names[layout_input_count] = input->name;
                    layout_input_positions[layout_input_count] = input->pos;
                    layout_input_component_count[layout_input_count] = input->comp;
                    layout_input_count++;
                }
                shader_count++;
            }
        }
        /* Add main vertex and fragment shaders */
        shader_ids[shader_count++] = resources->shaders[MAIN_FS];

        /* Get main vertex shader's input and increase counter */
        input = (SHADER_PREFS + MAIN_VS)->ins[0];
        layout_input_count++;

        /* Create a new shader program */
        pycasso_shader_program_Program_new(&program,
                /*program type bit-mask */ bit_id,
                  /* layout output name */ "fragment",
                  /* layout input count */ layout_input_count,
                  /* layout input names */ layout_input_names,
              /* layout input positions */ layout_input_positions,
        /* layout input component count */ layout_input_component_count,
                        /* shader count */ shader_count,
                          /* shader ids */ shader_ids,
                  /* main vertex shader */ resources->shaders[MAIN_VS],
                          /* main input */ input->name,
                       /* main position */ input->pos,
                /* main component count */ input->comp,
                /* arche vertices count */ arche_vertices_count,
                      /* arche vertices */ arche_vertices);

        /* Store shader program */
        append(resources->programs, program);
    }
    /* Append a new instance to the shader program */
    pycasso_shader_program_Program_append(program,
                     /* instance count */ instance_count,
                   /* properties count */ property_count,
          /* property components count */ property_components_count,
                            /* offsets */ properties,
           /* start index of instances */ index);

    return true;
}



/*----------------------------------------------------------------------------*/
void
pycasso_shader_resources_Primitives_draw_all(pycasso_shader_resources_Primitives *primitives)
{
    DynamicArray_void_ptr *programs = primitives->programs;
    map(programs, len(programs), pycasso_shader_program_Program_draw);
}
