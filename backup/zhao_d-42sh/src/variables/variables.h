/**
** \file variables.h
** \brief Header file for all the variable managing functions
** \author depott_g
*/

#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
** \struct variable_manager
** \brief Structure storing the variable dictionary array and the number of
          elements of the dictionary (i.e. the number of variables)
*/
struct variable_manager
{
    unsigned nb_variables;
    struct variable **variables;
};

/**
** \struct variable
** \brief Structure containing the name of a variable and its value
*/
struct variable
{
    char *name;
    char *value;
};

/*============================================================================*/
/* Functions from variables.c */
/**
** \fn void var_init(void)
** \brief If the variable manager has not been initialized, initializes the
          variable manager. Then, in all cases, sets all the environment
          variables to their default value.
*/
void var_init(void);

/**
** \fn var_set
** \brief Creates a variable with the given name and value, or if a variable
          already has this name, sets its value to the given value. The name and
          value are copied in new strings before being given to the variable.
** \param name Name of the variable to create or update
** \param value Value to give to the set variable
*/
void var_set(char *name, char *value);

/**
** \fn char *var_get(char *name)
** \brief Gets the value of a variable.
** \param name Name of the variable to get the value of
** \return Pointer to the value of the variable if it exists, else NULL
*/
char *var_get(char *name);

/**
** \fn void var_destroy(void)
** \brief Frees the variable manager and everything it contains
*/
void var_destroy(void);

#endif
