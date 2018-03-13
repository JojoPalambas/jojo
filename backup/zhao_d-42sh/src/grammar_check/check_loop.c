#include <stdio.h>
#include <string.h>

#include "grammar_check.h"


int parse_rulefor(char ***tab)
{
  if (strcmp(**tab, "for"))
    return WRONGEXPR;
  ++*tab;
  if (!**tab)
    return TOKENMISS;
  if (!isVariable(**tab))
    return wrong_ret(**tab);
  ++*tab;
  if (!**tab)
    return TOKENMISS;
  if (***tab == ';')
    ++*tab;
  else
  {
    while(***tab == '\n')
      ++*tab;
    if (!strcmp(**tab, "in"))
    {
      ++*tab;
      while (**tab && (***tab != ';' && ***tab != '\n' ))
        ++*tab;
      if (**tab && (***tab == ';' || ***tab == '\n'))
        ++*tab;
      else
        return TOKENMISS;
    }
  }
  while(**tab && ***tab == '\n')
    ++*tab;
  return parse_dogroup(tab);
}

int parse_rulewhile(char ***tab)
{
  if (strcmp(**tab, "while"))
    return WRONGEXPR;
  ++*tab;
  int ret = parse_compoundlist(tab);
  if (ret == VALIDEXPR)
    return parse_dogroup(tab);
  return ret;
}

int parse_ruleuntil(char ***tab)
{
  if (strcmp(**tab, "until"))
    return WRONGEXPR;
  ++*tab;
  int ret = parse_compoundlist(tab);
  if (ret == VALIDEXPR)
    return parse_dogroup(tab);
  return ret;

}
