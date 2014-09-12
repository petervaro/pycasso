/* INFO ************************************************************************
**                                                                            **
**                                  pycasso                                   **
**                                  =======                                   **
**                                                                            **
**    Cross-platform, hardware accelerated, constraint based GUI framework    **
**                       Version: 0.5.02.035 (20140911)                       **
**                                                                            **
**                         File: src/shader/program.c                         **
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
#include <string.h>   /* memcpy() */
#include <stdlib.h>   /* malloc(), free() */
#include <stdbool.h>  /* bool, true, false */

/* Include OpenGL/GLEW headers */
#include <GL/glew.h>

/* Include cutils headers */
#include <cutils/call.h>

/* Include internal pycasso headers */
#include "include/shader/helper.h"
#include "include/debug.h"


/*----------------------------------------------------------------------------*/
/* This object and all of its methods are calling OpenGL functions directly,
   however, they are up "one-level" in the abstraction layers */
typedef struct pycasso_shader_program_program
{
    /* Bit-mask ID => type of program */
    unsigned int bit_id;

    /* Counters for instanced draw */
    size_t vert_count,
           inst_count,
           shad_count; /* This is needed for deletion */

    GLuint prog_id,         /* Shader-program ID */
           vao_id,          /* Corresponding vertex object */
           jmp_inputs_pos,  /* Jump value (data + inputs_pos) */
           jmp_shader_ids,  /* Jump value (data + inputs_pos + inputs_pos) */
           data[];          /* Data: VBO IDs, input layout positions and
                               vertex and fragment shader IDs */

} pycasso_shader_program_Program;



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_program_Program_compare(const void *bit_id,
                                       const void *program,
                                       size_t size)
{
    debug();
    bool found =
        (unsigned int)bit_id == (**(pycasso_shader_program_Program **)program).bit_id;
    debug();
    return found;
}



/*----------------------------------------------------------------------------*/
#define SETUP_VERTEX_BUFFER_OBJECT(program_id,                                 \
                                   vbo_ids,                                    \
                                   index_of_vbo_id,                            \
                                   input_name,                                 \
                                   input_position,                             \
                                   components_count,                           \
                                   attribute_divisor,                          \
                                   instance_count,                             \
                                   vbo_data)                                   \
    do {                                                                       \
        /* Upload data to VBO */                                               \
        glGenBuffers(1, vbo_ids + index_of_vbo_id);                            \
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[index_of_vbo_id]);               \
        glBufferData(GL_ARRAY_BUFFER,                                          \
  /* size of data */ instance_count * components_count * sizeof(GLfloat),      \
  /* initial data */ vbo_data,                                                 \
    /* usage-mode */ GL_STATIC_DRAW);                                          \
                                                                               \
        /* Setup VBO */                                                        \
        glBindAttribLocation(program_id, input_position, input_name);          \
        glVertexAttribPointer(input_position,                                  \
       /* components count */ components_count,                                \
        /* components type */ GL_FLOAT,                                        \
      /* has to normalize? */ GL_FALSE,                                        \
          /* attrib offset */ 0,                                               \
          /* buffer offset */ (GLvoid *)NULL);                                 \
        glEnableVertexAttribArray(input_position);                             \
        glVertexAttribDivisor(input_position, attribute_divisor);              \
    } while (0)



/*----------------------------------------------------------------------------*/
#define SAME_PER_INSTANCE 0
#define VARY_PER_INSTANCE 1
bool
pycasso_shader_program_Program_new(pycasso_shader_program_Program **program,
                                   const unsigned int program_type_bit_mask,
                                   const GLchar *layout_output_name,
                                   const size_t layout_input_count,
                                   const GLchar **layout_input_names,
                                   const GLuint *layout_input_positions,
                                   const GLuint *layout_input_component_count,
                                   const size_t shader_count,
                                   const GLuint *shader_ids,
                                   const GLuint main_vertex_shader_id,
                                   const GLchar *main_vertex_shader_input_name,
                                   const GLuint main_vertex_shader_input_position,
                                   const GLuint main_vertex_shader_input_component_count,
                                   const size_t arche_vertices_count,
                                   const GLfloat *arche_vertices)
{
    /* Exception raiser flags */
    bool exception_from_shader_program_creation = false;

    /* Create program object */
    pycasso_shader_program_Program *_program =
        /* Object size + ID data */
        malloc(sizeof(pycasso_shader_program_Program) +
               (layout_input_count*2 + shader_count) * sizeof(GLuint));
    if (!_program) goto Exception_From_Allocation;

    /* Set static values */
    _program->bit_id = program_type_bit_mask;
    _program->vert_count = arche_vertices_count;
    _program->inst_count = 0;
    _program->shad_count = shader_count;

    /* Set internal jump value */
    _program->jmp_inputs_pos = layout_input_count;
    /* Store the main vertex shader input layout position */
    memcpy(_program->data + layout_input_count,
           &main_vertex_shader_input_position,
           sizeof(GLuint));
    /* Store input layout positions */
    memcpy(_program->data + layout_input_count + 1,
           layout_input_positions,
           layout_input_count * sizeof(GLuint));

    /* Set internal jump value */
    _program->jmp_shader_ids = layout_input_count*2;
    /* Store main vertex shader IDs */
    memcpy(_program->data + layout_input_count*2,
           &main_vertex_shader_id,
           sizeof(GLuint));
    /* Store shader IDs */
    memcpy(_program->data + layout_input_count*2 + 1,
           shader_ids,
           shader_count * sizeof(GLuint));

    /* Create shader program */
    GLuint program_id;
    if (!pycasso_shader_helper_create_and_link_program(&program_id,
                                                       main_vertex_shader_id,
                                                       shader_count,
                                                       shader_ids))
        goto Exception_From_Shader_Program_Creation;

    /* Create Vertex Array Object and start using it */
    glGenVertexArrays(1, &_program->vao_id);
    glBindVertexArray(_program->vao_id);

    /* Static input (arche vertices) */
    size_t vbo_index = 0;
    SETUP_VERTEX_BUFFER_OBJECT(program_id,
          /* VBO ID pointer */ _program->data,
                   /* index */ vbo_index,
       /* layout input name */ main_vertex_shader_input_name,
   /* layout input position */ main_vertex_shader_input_position,
        /* components count */ main_vertex_shader_input_component_count,
       /* attribute divisor */ SAME_PER_INSTANCE,
              /* data count */ arche_vertices_count,
                    /* data */ arche_vertices);

    /* Initailly allocated space for this many instances */
    #define INIT_INST_COUNT 1024
    /* Dynamic inputs (variable properties) */
    for (size_t i=0; i<(layout_input_count - 1); i++)
    {
        vbo_index++;
        SETUP_VERTEX_BUFFER_OBJECT(program_id,
              /* VBO ID pointer */ _program->data,
                       /* index */ vbo_index,
           /* layout input name */ layout_input_names[i],
       /* layout input position */ layout_input_positions[i],
            /* components count */ layout_input_component_count[i],
           /* attribute divisor */ VARY_PER_INSTANCE,
                  /* data count */ INIT_INST_COUNT,
                        /* data */ NULL);
    }

    /* Set fragment output */
    glBindFragDataLocation(program_id, 0, layout_output_name);

    /* Store program ID */
    _program->prog_id = program_id;
    debug("program-id: %d", program_id);

    /* Store program and return as succeseded */
    *program = _program;
    return true;

    /* If something went wrong during the creation
       and linking of the shader program */
    Exception_From_Shader_Program_Creation:
        free(_program);
        exception_from_shader_program_creation = true;

    /* If allocation of program object failed */
    Exception_From_Allocation:
        if (!exception_from_shader_program_creation)
            #undef  EXCEPTION_MESSAGE
            #define EXCEPTION_MESSAGE "Program: allocation failed"
            raise(EXCEPTION_MESSAGE, sizeof EXCEPTION_MESSAGE);
        /* Set program pointer and return indicating failure */
        *program = NULL;
        return false;
}



/*----------------------------------------------------------------------------*/
bool
pycasso_shader_program_Program_del(pycasso_shader_program_Program *program)
{
    /* If program was not created successfully */
    if (!program) return false; /* Cannot operate on NULL */

    /* Destroy layout inputs */
    for (size_t i=program->jmp_inputs_pos; i<program->jmp_shader_ids; i++)
        glDisableVertexAttribArray(program->data[i]);

    /* Delete Vertex Buffers and Array Objects
       jmp_inputs_pos = input count = VBO count */
    glDeleteBuffers(program->jmp_inputs_pos, program->data);
    glDeleteVertexArrays(1, &program->vao_id);

    /* Delete program */
    GLuint *shader_ids = program->data + program->jmp_shader_ids;
    pycasso_shader_helper_unload_and_delete_program(program->prog_id,
                                                    program->shad_count,
                                                    shader_ids);
    /* Delete shaders */
    pycasso_shader_helper_delete_shaders(program->shad_count, shader_ids);

    /* Delete program and return indicating success */
    free(program);
    return true;
}



/*----------------------------------------------------------------------------*/
void
pycasso_shader_program_Program_append(pycasso_shader_program_Program *program,
                                      const size_t instance_count,
                                      const size_t properties_count,
                                      const size_t *property_components_count,
                                      const GLfloat **properties,
                                      size_t *start_index)
{
    /* If program was not created successfully */
    if (!program) return; /* Cannot operate on NULL */

    /* Mapped pointer */
    void *buffer;

    /* HACK: 0 is for arche vertices */
    size_t vbo_id = 1;

    /* Upload all values of all properties of all instances */
    for (size_t i=0; i<properties_count; i++)
    {
        /* Use VBO (property) and mapp it to pointer */
        glBindBuffer(GL_ARRAY_BUFFER, program->data[vbo_id++]);
        buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        /* Copy properties to VBO */
        memcpy(buffer,
               properties[i],
               instance_count * property_components_count[i] * sizeof(GLfloat));
        glUnmapBuffer(GL_ARRAY_BUFFER);
    }

    /* Set start of indices of instances and update instance counter */
    *start_index = program->inst_count;
    program->inst_count += instance_count;
}



/*----------------------------------------------------------------------------*/
/* TODO: Index is needed because of the caller is a map() function on
         a DynamicArray which stores all the programs => change the order in
         CUTILS, so that it could be used as a _Generic interface (first
         argument based selection) */
void
pycasso_shader_program_Program_draw(size_t index,
                                    pycasso_shader_program_Program *program)
{
    /* If program was not created successfully */
    /* TODO: visual feedback => draw something to indicate the error */
    if (!program) return; /* Cannot operate on NULL */

    debug(opengl_get_error());

    /* Start using program */
    glUseProgram(program->prog_id);

    debug(opengl_get_error());

    glBindVertexArray(program->vao_id);

    debug(opengl_get_error());

    /* Draw all instances */
    glDrawArraysInstanced(GL_TRIANGLE_FAN,
/* First index in buff */ 0,
 /* Number of vertices */ program->vert_count,
/* Number of instances */ program->inst_count);

    debug(opengl_get_error());
}
