#include <stdio.h>
#include <string.h>

#include "grammar_check.h"

int parse_case(char ***tab)
{
  if (strcmp(**tab, "case"))
    return wrong_ret(**tab);
  ++*tab;
  if (!**tab)
    return TOKENMISS;
  if (!isWord(**tab))
    return wrong_ret(**tab);
  ++*tab;
  if (!**tab)
    return TOKENMISS;
  while (**tab && ***tab == '\n')
    ++*tab;
  if (!**tab)
    return TOKENMISS;
  if (strcmp(**tab, "in"))
    return wrong_ret(**tab);
  ++*tab;
  while (**tab && ***tab == '\n')
    ++*tab;
  int ret = parse_caseclause(tab);
  if (ret == VALIDEXPR)
  {
    if (!strcmp(**tab, "esac"))
    {
      ++*tab;
      return VALIDEXPR;
    }
    else
      return TOKENMISS;
  }
  return ret == TOKENMISS ? TOKENMISS : wrong_ret(**tab);
}

int parse_caseclause(char ***tab)
{
  if (!**tab)
    return TOKENMISS;
  if (!strcmp(**tab, "(") || isWord(**tab))
  {
    int ret = parse_caseitem(tab);
    if (ret == VALIDEXPR)
    {
      while (!strcmp(**tab, ";;"))
      {
        ++(*tab);
        while(***tab == '\n')
          ++(*tab);
        if (!strcmp(**tab, "esac"))
          return VALIDEXPR;
        if (!strcmp(**tab, "(") || isWord(**tab))
        {
          ret = parse_caseitem(tab);
          if (ret == VALIDEXPR)
            return VALIDEXPR;
          return ret == TOKENMISS ? TOKENMISS : wrong_ret(**tab);
        }
      }
      while (***tab == '\n')
        ++(*tab);
      if (!strcmp(**tab, "esac"))
      {
        ++*tab;
        return VALIDEXPR;
      }
      else
        return TOKENMISS;
    }
    return ret == TOKENMISS ? TOKENMISS : wrong_ret(**tab);
  }
  return WRONGEXPR;
}

int parse_caseitem(char ***tab)
{
  const char *first_andor[13] =
  {
    "!", "0", "1", "2", "{", "(", "for", "while", "until", "case", "if",
    "function"
  }; // assignmentword, word)
  if (***tab == '(')
    ++*tab;
  if (isWord(**tab))
    ++*tab;
  else
    return wrong_ret(**tab);
  while(***tab == '|')
  {
    if (!isWord(**tab))
      return wrong_ret(**tab);
    else
      ++*tab;
  }
  if (***tab != ')')
    return wrong_ret(**tab);
  ++*tab;
  while (**tab && ***tab == '\n')
    ++*tab;
  if (!**tab)
    return TOKENMISS;
  if (isin(**tab, first_andor) || isWord(**tab))
    return parse_compoundlist(tab);
  return VALIDEXPR;
}
