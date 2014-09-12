/* HEADER */
// Include stadard headers
#include <stdlib.h>

// Include pycasso headers
#include "../include/allheaders.h"


/*----------------------------------------------------------------------------*/
pycasso_GeometryInstance *
pycasso_admin_init_instance(pycasso_StaticResources *resources)
{
    // Create instance
    pycasso_GeometryInstance *instance = malloc(sizeof(pycasso_GeometryInstance));
    if (!instance)
    {
        printf("Couldn't allocated memory for new instance\n");
        exit(EXIT_FAILURE);
    }

    // Set pointers of instance struct
    instance->prev_instance = resources->last_instance;
    instance->next_instance = (void *)NULL;

    // Update resources pointers
    resources->last_instance->next_instance = instance;
    resources->last_instance = instance;

    return instance;
}

/*----------------------------------------------------------------------------*/
void
pycasso_admin_delete_instance(pycasso_GeometryInstance *instance,
                              pycasso_StaticResources *resources)
{
    // Point from instance's prev_instance instance to
    // instance's next_instance instance (remove instance from chain)
    instance->prev_instance->next_instance = instance->next_instance;

    // Update resources' last_instance to point
    // at the really last instance in list
    if (instance->next_instance == (void *)NULL)
        resources->last_instance = instance->prev_instance;
    else
        resources->last_instance = instance->next_instance;

    // Clean up
    free(instance);
}
