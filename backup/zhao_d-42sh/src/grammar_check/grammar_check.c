#include <stdio.h>
#include <string.h>

#include "grammar_check.h"


int parse_input(char **tab)
{
  if (!strcmp(*tab, "\n") || **tab == EOF)
    return VALIDEXPR;
  int ret = parse_list(&tab);
  if (ret == TOKENMISS)
    return TOKENMISS;
  return ret == VALIDEXPR ? VALIDEXPR : WRONGEXPR;
}

int parse_andor(char ***tab)
{
  int i = parse_pipeline(tab);
  if (i == WRONGEXPR)
    return WRONGEXPR;
  if (i == TOKENMISS)
  {
    if (!**tab || !***tab)
      return TOKENMISS;
    else
      return WRONGEXPR;
  }
  else
  {
    while (**tab && (!strcmp(**tab, "&&") || !strcmp(**tab, "||")))
    {
      ++(*tab);
      while (***tab == '\n')
        ++(*tab);
      i =  parse_pipeline(tab);
      if (i != VALIDEXPR)
        return WRONGEXPR;
    }
    return i;
  }
}

int parse_pipeline(char ***tab)
{
  if (***tab == '!')
    ++*tab;
  int ret = parse_command(tab);
  if (ret == VALIDEXPR && **tab)
  {
    while (***tab == '|')
    {
      while (***tab == '\n')
        ++*tab;
      if (parse_command(tab) != VALIDEXPR)
        return WRONGEXPR;
    }
    return VALIDEXPR;
  }
  else
    return ret;
}

int parse_funcdec(char ***tab)
{
  if (!strcmp(**tab, "function"))
    ++*tab;
  if (isWord(**tab))
    ++*tab;
  else
    return wrong_ret(**tab);
  if (***tab == '(')
    ++*tab;
  else
    return wrong_ret(**tab);
  if(**(*tab+1) == ')')
    ++*tab;
  else
    return wrong_ret(**tab);
  while (***tab == '\n')
    ++tab;
  return parse_shellcommand(tab);
}

int parse_compoundlist(char ***tab)
{
  const char *first_andor[13] =
  {
    "!", "0", "1", "2", "{", "(", "for", "while", "until", "case", "if",
    "function"
  }; // and assignmentword, word
  const char *next[4] =
  {
    ";", "&", "\n"
  };
  while(**tab && ***tab == '\n')
    ++*tab;
  if (!**tab)
    return TOKENMISS;
  int ret = parse_andor(tab);
  if (ret != VALIDEXPR)
    return ret;
  if (**tab && ***tab)
  {
    do {
      if (isin(**tab, next))
        ++*tab;
      while(**tab && ***tab == '\n')
        ++*tab;
      if (**tab && ***tab && (isWord(**tab) || (*(*tab+1) != NULL
              && **(*tab+1) == '=') || isin(**tab, first_andor)))
        ret = parse_andor(tab);
      else
        break;
      if (ret != VALIDEXPR)
        return ret;
    }while(1);
    if (**tab && isin(**tab, next))
      ++*tab;
  }
  return ret;
}


#if DEBUG_UNIT

#include <assert.h>

int main(void)
{
  char *test1[] = {"for", "i", "in", "toto", ";", "do", "echo", "banane", ";",
    "done" , "\n", "\0"};
  char *test2[] = {"for", "i", "in", "toto", ";", "do", "echo", "banane", ";",
    "\n", "\0" };
  char *test3[] = {"for", "in", "toto", ";", "do", "echo", "banane", ";" , "\n",
    "\0"};
  char *test4[] = {"for", "i", "in", "toto", "tata", ";", "do", "echo",
    "banane", ";", "done" , "\n", "\0"};
  char *test5[] = {"while", "true", ";", "do", "echo", "banane", ";", "done",
    "\n", "\0"};
  char *test6[] = {"while", "true", "true", ";", "do", "echo", "banane", ";",
    "done", "\n", "\0"};
  char *test7[] = {"while", "true", "true", ";", "do", "echo", "banane", ";",
    "\n", "\0"};
  char *test8[] = {"case", "banane", "in", "start", ")", "start", ";;", "stop",
    ")", "stop",";;","esac", "\n", "\0"};
  printf("Test1\n");
  assert(parse_input(test1) == VALIDEXPR);
  printf("Test2\n");
  assert(parse_input(test2) == TOKENMISS);
  printf("test3\n");
  assert(parse_input(test3) == WRONGEXPR);
  printf("test4\n");
  assert(parse_input(test4) == VALIDEXPR);
  printf("test5\n");
  assert(parse_input(test5) == VALIDEXPR);
  printf("test6\n");
  assert(parse_input(test6) == VALIDEXPR);
  printf("test7\n");
  assert(parse_input(test7) == TOKENMISS);
  printf("test8\n");
  assert(parse_input(test8) == VALIDEXPR);
  return 0;
}

#endif
