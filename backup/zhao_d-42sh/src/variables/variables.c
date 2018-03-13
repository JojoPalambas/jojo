/**
** \file variables.c
** \brief C file containing the all the functions needed to store variables and
         the array containing all the variables
** \author depott_g
*/

#include "variables.h"

static struct variable_manager *vm = NULL;

void var_init()
{
    if (!vm)
        vm = calloc(1, sizeof (struct variable_manager));
    if (!vm)
        err(-1, "Cannot allocate memory to store variable manager");
    var_set("PS1", "42sh$ ");
    var_set("PS2", "> ");
}

void var_set(char *name, char *value)
{
    for (unsigned i = 0; i < vm->nb_variables; i++)
    {
        if (!strcmp(vm->variables[i]->name, name))
        {
            free(vm->variables[i]->value);
            int len = strlen(value);
            vm->variables[i]->value = calloc(1, len + 1);
            if (!vm->variables[i]->value)
                err(-1, "Cannot allocate memory to store a variable");
            strcpy(vm->variables[i]->value, value);
            return;
        }
    }
    int namelen = strlen(name);
    int vallen = strlen(value);
    // Changes the number of stored variables
    vm->variables = realloc(vm->variables,
                            sizeof (struct variable) * (vm->nb_variables + 1));
    vm->nb_variables++;

    // Sets the new variable
    vm->variables[vm->nb_variables - 1] =
                                    calloc(1, sizeof (struct variable) + 1);
    vm->variables[vm->nb_variables - 1]->name = calloc(1, namelen + 1);
    if (!vm->variables[vm->nb_variables - 1]->name)
        err(-1, "Cannot allocate memory to store a variable");
    strcpy(vm->variables[vm->nb_variables - 1]->name, name);
    vm->variables[vm->nb_variables - 1]->value = calloc(1, vallen + 1);
    if (!vm->variables[vm->nb_variables - 1]->value)
        err(-1, "Cannot allocate memory to store a variable");
    strcpy(vm->variables[vm->nb_variables - 1]->value, value);
}

char *var_get(char *name)
{
    for (unsigned i = 0; i < vm->nb_variables; i++)
    {
        if (!strcmp(vm->variables[i]->name, name))
        {
            return vm->variables[i]->value;
        }
    }
    return NULL;
}

void var_destroy(void)
{
    for (unsigned i = 0; i < vm->nb_variables; i++)
    {
        free(vm->variables[i]->name);
        free(vm->variables[i]-> value);
        free(vm->variables[i]);
    }
    free(vm->variables);
    free(vm);
    vm = NULL;
}

void var_print(void)
{
    if (!vm)
    {
        printf("NULL\n");
        return;
    }
    for (unsigned i = 0; i < vm->nb_variables; i++)
    {
        printf("%s = %s\n", vm->variables[i]->name, vm->variables[i]->value);
    }
}
