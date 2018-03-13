/**
** \file parser.c
** \brief C file containing the main functions for parsing a shell command that
         has already been subdivided by the lexer
** \author depott_g
*/

#include "parser.h"

void ast_init(struct AST *A, enum node_type type,
              char **content, size_t content_words)
{
    A->type = type;
    if (content_words && content)
    {
        A->content = calloc(content_words + 1, sizeof (char *));
        if (!A->content)
            err(-1, "Cannot allocate memory space to store tree content");
        for (size_t i = 0; i < content_words; i++)
            A->content[i] = content[i];
    }
    else
        A->content = NULL;
    A->content_words = content_words;
    A->children[0] = NULL;
    A->children[1] = NULL;
    A->children[2] = NULL;
    A->children[3] = NULL;
}

struct AST *ast_create(enum node_type type, char **content,
                       size_t content_words)
{
    struct AST *A = malloc(sizeof (struct AST));
    if (!A)
        err(-1, "Cannot allocate memory space to store tree node");
    ast_init(A, type, content, content_words);
    return A;
}

int parse_rec(char **cmd, size_t size,
                      struct AST *previous, enum child direction)
{
    // If the end of the command is reached
    if (!cmd || !*cmd || size <= 0
        || !strcmp(*cmd, ")") || !strcmp(*cmd, "}"))
        return 1;
    // If an extra ';' or '\n' is encountered
    if (!strcmp(*cmd, ";") || !strcmp(*cmd, "\n"))
        return parse_rec(cmd + 1, size - 1, previous, direction);

    // If a reserved word is found
    if (!strcmp(*cmd, "!"))
        return subparse_not(cmd, size, previous, direction);
    if (!strcmp(*cmd, "if"))
        return subparse_if(cmd, size, previous, direction, 0);
    if (!strcmp(*cmd, "while"))
        return subparse_while(cmd, size, previous, direction);
    if (!strcmp(*cmd, "until"))
        return subparse_until(cmd, size, previous, direction);
    if (!strcmp(*cmd, "for"))
        return subparse_for(cmd, size, previous, direction);

    // If *cmd is the last word of the command, considers it as a command
    if (!cmd[1])
        return subparse_expression(cmd, size, previous, direction);

    if (!strcmp(cmd[1], "="))
        return subparse_declaration(cmd, size, previous, direction);

    return subparse_expression(cmd, size, previous, direction);
}

struct AST *parse(char **cmd, size_t size)
{
    struct AST *A = ast_create(SENTINEL, NULL, 0);
    if (!A)
        err(-1, "Cannot allocate memory space for tree node");
    if (!parse_rec(cmd, size, A, NEXT))
    {
        ast_destroy(A);
        return NULL;
    }
    return A;
}

static void indent_print(char c, size_t indent, FILE *f)
{
    for (size_t i = 0; i < indent; i++)
        fprintf(f, "%c", c);
}

static void ast_print_type2(struct AST *A, FILE *f)
{
    if (A->type == STRING)
        fprintf(f, "STRING");
    else if (A->type == REDIRECTION)
        fprintf(f, "REDIRECTION");
    else if (A->type == PARENTHESIS)
        fprintf(f, "PARENTHESIS");
    else if (A->type == AND)
        fprintf(f, "AND");
    else if (A->type == OR)
        fprintf(f, "OR");
    else if (A->type == EXPRESSION)
        fprintf(f, "EXPRESSION");
    else
        fprintf(f, "UNKNOWN");
}

static void ast_print_type(struct AST *A, FILE *f)
{
    if (!A)
        return;
    if (A->type == SENTINEL)
        fprintf(f, "SENTINEL");
    else if (A->type == EXPRESSION)
        fprintf(f, "EXPRESSION");
    else if (A->type == IF)
        fprintf(f, "IF");
    else if (A->type == WHILE)
        fprintf(f, "WHILE");
    else if (A->type == FOR)
        fprintf(f, "FOR");
    else if (A->type == PIPE)
        fprintf(f, "PIPE");
    else if (A->type == DECLARATION)
        fprintf(f, "DECLARATION");
    else if (A->type == NOT)
        fprintf(f, "NOT");
    else
        ast_print_type2(A, f);
}

static void ast_print_node(struct AST *A, FILE *f, int nb)
{
    indent_print(' ', 4, f);
    fprintf(f, "\"%d\\n", nb);
    ast_print_type(A, f);
    fprintf(f, "\\n");
    for (size_t i = 0; i < A->content_words; i++)
    {
        fprintf(f, "%s%s", A->content[i],
                (i == A->content_words - 1 ? "" : " "));
    }
    fprintf(f, "\"");
}

static void ast_print_label(FILE *f, int child)
{
    if (child == 0)
        fprintf(f, "    [ label=\"< Condition\" ];");
    else if (child == 1)
        fprintf(f, "    [ label=\"< Left\" ];");
    else if (child == 2)
        fprintf(f, "    [ label=\"< Right\" ];");
    else
        fprintf(f, "    [ label=\"< Next\" ];");
}

static void ast_print_rec(struct AST *A, FILE *f, int *nb)
{
    if (!A)
        return;
    *nb += 1;
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (!A->children[i])
            continue;
        count++;
        ast_print_node(A, f, *nb);
        fprintf(f, " -> ");
        ast_print_node(A->children[i], f, *nb + count);
        ast_print_label(f, i);
        fprintf(f, "\n");
    }
    for (int i = 0; i < 4; i++)
        ast_print_rec(A->children[i], f, nb);

}

void ast_print(struct AST *A, const char *path)
{
    FILE *f = fopen(path, "w");
    if (!f)
    {
        warnx("Failed to open %s", path);
        return;
    }
    fprintf(f, "digraph AST\n");
    fprintf(f, "{\n");

    int counter = 0;
    ast_print_rec(A, f, &counter);

    fprintf(f, "}");

    fclose(f);
}

void ast_destroy(struct AST *A)
{
    if (!A)
        return;
    free(A->content);
    for (int i = 0; i < 4; i++)
    {
        ast_destroy(A->children[i]);
    }
    free(A);
}
