/**
** \file executer.c
** \brief C file containing the main functions for executing a shell command
          that has already been subdivided by the lexer and put in an AST by the
          parser
** \author depott_g
*/

#include "parser.h"

static int my_execvp(char *cmd, char **args)
{
    int pid = fork();
    int result = 1;
    if (pid == -1)
        err(-1, "Cannot fork");
    if (pid)
    {
        int ans = wait(&result);
        if (ans == -1)
            err(-1, "Cannot wait for process to terminate");
        result = WEXITSTATUS(result);
    }
    else
    {
        int (*func)(char **) = builtin_find(cmd);
        if (!func)
        {
            result = execvp(cmd, args);
            if (result == 127 || result == -1)
                fprintf(stderr, "%s: command not found\n", cmd);
            exit(result);
        }
        exit(func(args));
    }
    return result;
}

static int subexec_expression(struct AST *A)
{
    // It should not be possible to get a NULL content here
    if (!A->content || !*A->content || !A->content_words)
        errx(-1, "Cannot execute a simple expression");

    char **args = calloc(A->content_words + 1, sizeof (char *));
    if (!args)
        err(-1, "Cannot allocate memory");
    for (size_t i = 0; i < A->content_words; i++)
        args[i] = A->content[i];
    args[A->content_words] = NULL;
    int ans = my_execvp(args[0], args);
    free(args);

    if (A->children[NEXT])
        execute(A->children[NEXT]);
    return ans;
}

static int subexec_not(struct AST *A)
{
    return !execute(A->children[RIGHT]);
}

static int subexec_if(struct AST *A)
{
    if (!A->children[CONDITION])
        errx(-1, "Error with IF statement: No condition found");
    int cond = execute(A->children[CONDITION]);
    int ans = 0;
    if (!cond)
    {
        if (!A->children[LEFT])
            errx(-1, "Error with IF statement: No THEN statement found");
        ans = execute(A->children[LEFT]);
    }
    else
    {
        if (A->children[RIGHT])
            ans = execute(A->children[RIGHT]);
    }
    if (A->children[NEXT])
        return execute(A->children[NEXT]);
    return ans;
}

static int subexec_while(struct AST *A)
{
    if (!A->children[CONDITION])
        errx(-1, "Error with WHILE statement: No condition found");
    if (!A->children[RIGHT])
        errx(-1, "Error with WHILE statement: No content found");
    int ans = 0;
    int cond = execute(A->children[CONDITION]);
    while(!cond)
    {
        ans = execute(A->children[RIGHT]);
        cond = execute(A->children[CONDITION]);
    }
    if (A->children[NEXT])
        return execute(A->children[NEXT]);
    return ans;
}

static int subexec_for(struct AST *A)
{
    if (!A->children[CONDITION])
        errx(-1, "Error with WHILE statement: No condition found");
    if (!A->children[RIGHT])
        errx(-1, "Error with WHILE statement: No content found");
    int ans = 0;
    execute(A->children[CONDITION]);
    for (unsigned i = 0; i < A->children[CONDITION]->content_words; i++)
    {
        var_set(A->content[0], A->children[CONDITION]->content[i]);
        ans = execute(A->children[RIGHT]);
    }
    if (A->children[NEXT])
        return execute(A->children[NEXT]);
    return ans;
}

int execute(struct AST *A)
{
    // It should not be possible to get a NULL pointer here
    if (!A)
        errx(-1, "Execution sequence error");
    // If node is SENTINEL, does nothing but a recursive call on next
    if (A->type == SENTINEL)
    {
        if (A->children[NEXT])
            return execute(A->children[NEXT]);
        return 0;
    }
    // If node is EXPRESSION, uses execvp
    if (A->type == EXPRESSION)
    {
        return subexec_expression(A);
    }
    if (A->type == NOT)
    {
        return subexec_not(A);
    }
    if (A->type == IF)
    {
        return subexec_if(A);
    }
    if (A->type == WHILE)
    {
        return subexec_while(A);
    }
    if (A->type == FOR)
    {
        return subexec_for(A);
    }
    if (A->type == STRING)
    {
        return 0;
    }
    errx(-1, "Use of command managed by the parser but not by the executer");
    return -1;
}
