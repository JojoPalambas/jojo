#include <stdio.h>
#include <string.h>
#include <err.h>
#include "grammar_check.h"

int isRedirection(char *str)
{
  for (int i = 0; str[i]; ++i)
  {
    if (str[i] == '<' || str[i] == '>')
      return 1;
  }
  return 0;
}

int isin(char *val, const char **list)
{
  if (!list || !*list)
    return -1;
  for (int i = 0; list[i]; ++i)
  {
    if (!strcmp(val, list[i]))
      return 1;
  }
  return 0;
}

int isWord(char *s)
{
  const char *tokens[35] = {"!","{","(","for","while","until","case","if",
    "function",")","}","&&","||", "esac","done","fi","do",
    "else","elif", ";;","&","|","then","<",">","<<",">>","<<-",
    ">&","<&",">|","<>", ";", "\n"};
  return !isin(s, tokens);
}

int isVariable(char *s)
{
  const char *tokens[] = {
    "!","@","#","$","%","^","&","*","(",")","+","{","}","[","]","\'","\"","-","*","/",",",".",
    "<",">","\\","|","~","`"
  };
  if ((*s <= 'z' && *s >= 'a') || (*s <= 'Z' && *s >= 'A'))
  {
    ++s;
    while (*s &&((*s <= 'z' && *s >= 'a')
          || (*s <= 'Z' && *s >= 'A')
          || (*s >= '0' && *s <= '9')
          || !isin(s, tokens)))
      ++s;
  }
  else
    return 0;
  return !*s;
}

int wrong_ret(char *s)
{
  warnx("syntax error near unexpected token `%s'", s);
  return WRONGEXPR;
}
