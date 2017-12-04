/**
 * \file include.h
 * \brief All the exported functions and structures needed for the project.
 * \author depott_g
*/

#ifndef INCLUDE_H
# define INCLUDE_H

#define _DEFAULT_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <dirent.h>
#include <stdio.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <fnmatch.h>
#include <pwd.h>
#include <grp.h>

/*
 * \enum e_type
 * \brief Describes the type of an expression.
*/
enum e_type
{
    E_SENT = 0, /*! Sentinel */
    E_FILE, /*! File name */
    E_D, /*! -d */
    E_NAME, /*! -name */
    E_TYPE, /*! -type */
    E_OR, /*! -o */
    E_AND /*! -o */
};

/*
 * \struct expr
 * \brief AST structure used to store an expression.
*/
struct expr
{
    enum e_type type; /*! Type of the current node */
    char *name; /*! Name of the current node */
    struct expr *left_op; /*! Left child */
    struct expr *right_op; /*! Right child */

    struct expr *next_op; /*! Next child */
};

/*
 * \enum option
 * \brief Describes the type of an option.
*/
enum option
{
    H = 0, /*! -H */
    L, /*! -L */
    P /*! -P */
};

/*
 * \struct command
 * \brief Gives all the needed informations about the command line.
*/
struct command
{
    int argc; /*! Number of arguments */
    char **argv; /*! Array containing all the arguments */
    int pos; /*! Current parsing position in the command line */

    enum option opt; /*! Current activated option */

    size_t files_start; /*! Index of the beginning of the file names */
    size_t files_end; /*! Index of the end of the file names */

    struct expr *expr; /*! Expressions given in the command line */

    int reverse; /*! Integer describing if -d is activated */
};

/*
 * \enum direction
 * \brief Describes a direction to take while creating the tree.
*/
enum direction
{
    next = 0, /*! To the next child */
    right, /*! To the right child */
    left /*! To the left child */
};

/* Function used to use the expr structure */
struct expr *expr_init(char *arg);
void parse_expr(struct command *cmd, enum direction direc,
                 struct expr *grandfather, struct expr *father);
void expr_free(struct expr *expr);

/* Functions used to parse the command line */
struct command *parse(int argc, char **argv);
void command_free(struct command *cmd);

/*
 * \struct accumulator
 * \brief Represents a path in a way that makes concatenating faster.
*/
struct accumulator
{
    char path[4096]; /*! Path represented by the accumulator */
    size_t pos; /*! Size of the path */
};

/* Basic functions for the accumulator structure, in accu.c */
struct accumulator *accu_init(const char *path);
void accu_concat(struct accumulator *accu, const char *path);
void accu_print(struct accumulator *accu);
void accu_print_concat(struct accumulator *accu, const char *path);
struct accumulator *accu_cpy(struct accumulator *accu);

/* My functions to manipulate strings */
int my_strcmp(const char *s1, const char *s2);

/* Functions used for Threshold 0, in threshold0.c */
void findall(struct accumulator *path, struct command *cmd);
void findall_rec(struct accumulator *path, struct command *cmd);
void process_file(struct dirent *cur_dirent,
                  struct accumulator *accu, struct command *cmd);

/* Functions corresponding to expressions in the command line */
int func_d(struct command *cmd);
int func_name(struct expr *expr, struct accumulator *accu);
int func_type(struct expr *expr, struct accumulator *accu);

#endif
