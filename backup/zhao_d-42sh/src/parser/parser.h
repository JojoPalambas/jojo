/**
** \file parser.h
** \brief Header file for all the parser functions
** \author depott_g
*/

#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../variables/variables.h"
#include "builtin.h"

/**
** \enum node_type
** \brief Contained in every AST node, corresponding to its type
*/
enum node_type
{
    SENTINEL = 0,
    EXPRESSION = 1,
    IF = 2,
    WHILE = 3,
    FOR = 4,
    PIPE = 5,
    DECLARATION = 6,
    NOT = 7,
    STRING = 8,
    REDIRECTION = 9,
    PARENTHESIS = 10,
    AND = 11,
    OR = 12
};

/**
** \enum child
** \brief Describes one of the four children of an AST node
*/
enum child
{
    CONDITION = 0,
    LEFT = 1,
    RIGHT = 2,
    NEXT = 3
};

/**
** \struct AST
** \brief Represents an AST node, linked to its children (max 4)
*/
struct AST
{
    // Type of the node
    enum node_type type;
    // Optionnal value of the node
    char **content;
    // Number of words in the content
    size_t content_words;

    // CHildren of the AST
    struct AST *children[4];
};

/*============================================================================*/
/* Functions from parser.c */

/**
** \fn struct AST *parse(char **cmd, size_t size)
** \brief Parses the array of words from the command line to build an executable
          AST.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \return 1 on success, else 0
*/
struct AST *parse(char **cmd, size_t size);

/**
** \fn struct AST *parse_rec(char **cmd, size_t size,
                             struct AST *previous, enum child direction)
** \brief Recursive parsing function that treats the current word and redirects
          to the matching subparsing function.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int parse_rec(char **cmd, size_t size,
                      struct AST *previous, enum child direction);

/**
** \fn struct AST *ast_create(enum node_type type, char **content,
                              size_t content_words)
** \brief Creates a new AST node.
** \param type The type of node to create
** \param content The words to put in the new node
** \param content_words The number of words to put in the node
** \return The newly created node
*/
struct AST *ast_create(enum node_type type, char **content,
                       size_t content_words);

/**
** \fn void ast_init(struct AST *A, enum node_type type,
                     char **content, size_t content_words)
** \brief Initializes an AST node.
** \param A The node to initialize
** \param type The type to give to the node
** \param content The words to put in the node
** \param content_words The number of words to put in the node
*/
void ast_init(struct AST *A, enum node_type type,
                     char **content, size_t content_words);

/**
** \fn void ast_print(struct AST *A, const char *path)
** \brief Creates a dot file with the AST described inside.
** \param A the AST to put in the dot file
** \param path The path of the file to create
*/
void ast_print(struct AST *A, const char *path);

/**
** \fn void ast_destroy(struct AST *A)
** \brief Frees the whole AST.
** \param A The AST to free
*/
void ast_destroy(struct AST *A);

/*============================================================================*/
/* Functions from subparser_expression.c */

/**
** \fn struct AST *subparse_expression(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing simple command expressions.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_expression(char **cmd, size_t size,
                                struct AST *previous, enum child direction);

/**
** \fn int is_expr_separator(char *s)
** \brief Checks whether the given word is an expression separator (\n, ;, &)
** \param s Word to check
** \return 1 if the word is a separator, else 0
*/
int is_expr_separator(char *s);

/*============================================================================*/
/* Functions from subparser_declaration.c*/

/**
** \fn struct AST *subparse_declaration(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing declaration expressions.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_declaration(char **cmd, size_t size,
                                 struct AST *previous, enum child direction);

/*============================================================================*/
/* Functions from subparser_not.c*/

/**
** \fn struct AST *subparse_not(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing expressions preceeded by '!'.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_not(char **cmd, size_t size,
                         struct AST *previous, enum child direction);

/**
** \fn size_t exclamation_scope(char **cmd)
** \brief Finds the size of the scope of the current exclamation mark, i.e. the
          size of the expression negated by the current exclamation mark.
** \param cmd A pointer to the array of words to parse
** \return The scope of the exclamation mark
*/
size_t exclamation_scope(char **cmd);

/*============================================================================*/
/* Functions from subparser_pipe.c*/

/**
** \fn struct AST *subparse_pipe(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing piped expressions.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_pipe(char **cmd, size_t size,
                          struct AST *previous, enum child direction);

/*============================================================================*/
/* Functions from subparser_redirection.c*/

/**
** \fn struct AST *subparse_redirection(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing redirection expressions.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_redirection(char **cmd, size_t size,
                                 struct AST *previous, enum child direction);

/*============================================================================*/
/* Functions from subparser_if.c*/

/**
** \fn struct AST *subparse_if(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing IF expressions.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_if(char **cmd, size_t size,
                        struct AST *previous, enum child direction, int depth);

/**
** \fn int find_in(const char *s, const char **list)
** \brief Finds a word in an array of words.
** \param s The word to find
** \param list The array of words to search in
** \return 1 if the word is found, else 0
*/
int find_in(const char *s, const char **list);

/**
** \fn int find_target(char **cmd, const char **targets,
                const char **adders, const char **substracters, int then_type)
** \brief Finds one of the targets in an array of words, only if it is on level
          0. The program starts at level 0, and every time an adder is
          encountered, the level increases, and every time a substracter is
          encountered, the level decreases. If the level goes under 0, the
          program stops.
** \param cmd The array of words in which the targets are searched
** \param targets An array of targets
** \param adders An array of adders
** \param substracters An array of substracters
** \param for_do 1 if the target has to be right after the first ';' or '\n'
          encountered, else 0
** \return The distance in words from the current word to the target if found,
           else 0
*/
int find_target(char **cmd, const char **targets,
                const char **adders, const char **substracters, int for_do);

/*============================================================================*/
/* Functions from subparser_while.c*/

/**
** \fn struct AST *subparse_while(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing WHILE expressions.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_while(char **cmd, size_t size,
                           struct AST *previous, enum child direction);

/*============================================================================*/
/* Functions from subparser_until.c*/

/**
** \fn struct AST *subparse_until(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing UNTIL expressions.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_until(char **cmd, size_t size,
                           struct AST *previous, enum child direction);

/*============================================================================*/
/* Functions from subparser_for.c*/

/**
** \fn struct AST *subparse_for(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing FOR expressions.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_for(char **cmd, size_t size,
                         struct AST *previous, enum child direction);

/*============================================================================*/
/* Functions from subparser_string.c*/

/**
** \fn struct AST *subparse_string(char **cmd, size_t size,
                                     struct AST *previous, enum child direction)
** \brief Function parsing strings that don't need to be executed.
** \param cmd A pointer to the array of words to parse
** \param size The number of words to consider when parsing the array
** \param previous A pointer to the parent of the node to create
** \param direction An indication describing how to link the current node to
          the parent
** \return 1 on success, else 0
*/
int subparse_string(char **cmd, size_t size,
                            struct AST *previous, enum child direction);

/*============================================================================*/
/* Functions from executer.c */

/**
** \fn int execute(struct AST *ast)
** \brief Executes the given AST.
** \param ast The AST to execute
** \return The return value of the expression contained in the AST
*/
int execute(struct AST *ast);

#endif
