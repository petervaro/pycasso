#include <Python/Python.h>

/*
 *
 *     ... / 2014DESIGN / C / books / Python C API Tutorial.webloc
 *
 */

// Define a new exception object for the Pycasso module
static PyObject *PycassoError;


static PyObject *PycassoWindow(PyObject *self, // module object
                               PyObject *pyarg_title,
                               PyObject *pyarg_width,
                               PyObject *pyarg_height)
{
    const char *title;
    int width, height;

    if (!PyArg_Parse(pyarg_title, "s", &title)) printf("Invalid string 'title'\n");
    if (!PyArg_Parse(pyarg_width, "i", &width)) printf("Invalid int 'width'\n");
    if (!PyArg_Parse(pyarg_height, "i", &height)) printf("Invalid int 'height'\n");

    // Create window
    GLFWwindow *window;
    window_init(&window, width, height, title);
    // Enter event loop
    window_on_run(window);

    // There was an error
    return NULL;
}