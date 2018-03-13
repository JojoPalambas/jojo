#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "../grammar_check/grammar_check.h"
#include "../lexer/lexer.h"
#include "../parser/parser.h"
#include "prompt.h"

char *find_val(const char *str)
{
  if (!strcmp(str,"PS1"))
    return "42sh$ ";
  return "> ";
}

void char_free(char *s)
{
  if (s)
  {
    free(s);
    s = NULL;
  }
}

/* Signal Handler for SIGINT */
void sigintHandler(int sig_num __attribute__((unused)))
{
  signal(SIGINT, sigintHandler);
  fprintf(stdout, "\n42sh$ ");
  fflush(stdout);
}

/* Signal Handler for SIGTERM */
void sigtermHandler(int sig_num __attribute__((unused)))
{
  signal(SIGTERM, sigtermHandler);
  fprintf(stdout, "exit");
  fflush(stdout);
}
void prompt(void)
{
  rl_outstream = stderr;
  char *buffer = NULL;
  struct token_list *t = NULL;
  struct AST *ast = NULL;
  int res = VALIDEXPR;
  char *ps2 = NULL;
  size_t len = 0;
  signal(SIGINT, sigintHandler);
 // signal(SIGTERM, sigtermHandler);
  while (1)
  {
    if (res != TOKENMISS)
    {
      // fprintf(stderr, "42sh$ ");
      buffer = readline("42sh$ ");
      if (!buffer)
      {
        printf("exit\n");
        return;
      }
      add_history(buffer);
      len = strlen(buffer);
      buffer = realloc(buffer, len + 2);
      buffer[len] = '\n';
      buffer[len + 1] = '\0';

    }
    if (buffer && !strcmp(buffer, ""))
      continue;
    if (buffer && !strcmp(buffer, "exit\n"))
    {
      printf("exit\n");
      char_free(buffer);
      return;
    }
    else
    {
      /* lexer */
      t = lexer(buffer);
      /* Grammar check */
      res = parse_input(t->token);

      if (res == VALIDEXPR && buffer[strlen(buffer) - 1] != '\\')
      {
        ast = parse(t->token, t->size);
        execute(ast);
        if (check_flag(FLAG_AST))
          ast_print(ast, "OUTPUT.dot");
        /* free everything */
        if (t)
          free_token_list(t);
        if (ast)
          ast_destroy(ast);
        char_free(buffer);
        t = NULL;
        ast = NULL;
      }

      else if (res == TOKENMISS || buffer[strlen(buffer) - 1] == '\\')
      {
        printf("buffer -> %s\n", buffer);
        if (buffer[strlen(buffer) - 1] == '\\')
          buffer[strlen(buffer) - 1] = ' ';
        // fprintf(stderr, "> ");
        ps2 = readline("> ");
        add_history(ps2);
        size_t lenb = strlen(buffer);
        size_t lenp = strlen(ps2);
        ps2 = realloc(ps2, lenp + 4);
        ps2[lenp] = '\n';
        ps2[lenp + 1] = '\0';
        lenp += 4;
        buffer = realloc(buffer, lenb + lenp);
        memcpy(buffer + lenb + 1, ps2, lenp - 2);
        buffer[lenb] = ' ';
        free(ps2);
        res = TOKENMISS;
      }
      else if (res == WRONGEXPR)
      {
        // warnx("Syntax error");
        char_free(buffer);
      }
      if (t)
        free_token_list(t);
    }
  }
  char_free(buffer);
  free_token_list(t);
  return;
}
