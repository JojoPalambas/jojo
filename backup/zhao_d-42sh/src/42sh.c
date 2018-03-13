# define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "42sh.h"
#include "prompt/prompt.h"
#include "variables/variables.h"


unsigned check_flag(enum flags flags)
{
  return metadata.flags & flags;
}


unsigned set_flag(char **argv)
{
  unsigned flags = 0;
  while (*argv && **argv == '-')
  {
    if (!strcmp(*argv, "-c"))
      flags = flags | FLAG_C;
    else if (!strcmp(*argv, "-O"))
      flags = flags & ~FLAG_O;
    else if (!strcmp(*argv, "+O"))
      flags = flags | FLAG_O;
    else if (!strcmp(*argv, "--norc"))
      flags = flags | FLAG_NORC;
    else if (!strcmp(*argv, "--ast-print"))
      flags = flags | FLAG_AST;
    else if (!strcmp(*argv, "--version"))
      flags = flags | FLAG_VERSION;
    ++argv;
  }
  return flags;
}

int main(int argc, char **argv)
{
  var_init();
  metadata.flags = set_flag(argv+1);
  struct token_list *t = NULL;
  char **tab = NULL;
  struct AST *ast = NULL;
  int res = 0;
  if (check_flag(FLAG_C))
  {
    if (check_flag(FLAG_VERSION))
      printf("Version 1.0\n");
    t = lexer(argv[argc - 1]);
    tab = t->token;
    ast = parse(tab, t->size);
    if (check_flag(FLAG_AST))
      ast_print(ast, "AST.dot");
    res = execute(ast);
    if (t)
      free_token_list(t);
    if (ast)
      ast_destroy(ast);
  }
  else if (!isatty(0))
  {
    char *buffer = NULL;
    size_t tmp = 0;
    if (getline(&buffer, &tmp, stdin) != -1)
    {
      t = lexer(buffer);
      tab = t->token;
      ast = parse(tab, t->size);
      res = execute(ast);
    }
    if (t)
      free_token_list(t);
    if (ast)
      ast_destroy(ast);
    free(buffer);
  }
  else
  {
    if (check_flag(FLAG_VERSION))
      printf("Version 1.0\n");
    else
      prompt();
  }
  var_destroy();
  return res;
}
