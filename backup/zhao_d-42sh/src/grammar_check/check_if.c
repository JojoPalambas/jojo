#include <stdio.h>
#include <string.h>

#include "grammar_check.h"

int parse_if(char ***tab)
{
  if (strcmp(**tab, "if"))
    return wrong_ret(**tab);
  ++*tab;
  int ret = parse_compoundlist(tab);
  if (ret != VALIDEXPR)
    return ret == WRONGEXPR ? wrong_ret(**tab) : ret;
  if (!**tab)
    return TOKENMISS;
  if (strcmp(**tab, "then"))
    return wrong_ret(**tab);
  ++*tab;
  ret = parse_compoundlist(tab);
  if (ret != VALIDEXPR)
    return ret;
  if (!**tab)
    return TOKENMISS;
  if (!strcmp(**tab, "else") || !strcmp(**tab, "elif"))
  {
    ret = parse_elseclause(tab);
    if (ret == VALIDEXPR)
    {
      if (**tab && !strcmp(**tab, "fi"))
      {
        ++*tab;
        return VALIDEXPR;
      }
      return TOKENMISS;
    }
    return ret;
  }
  if (!strcmp(**tab, "fi"))
  {
    ++*tab;
    return VALIDEXPR;
  }
  return TOKENMISS;
}

int parse_elseclause(char ***tab)
{
  if (!strcmp(**tab, "else"))
  {
    ++*tab;
    return parse_compoundlist(tab);
  }
  else if (!strcmp(**tab, "elif"))
  {
    ++(*tab);
    if (parse_compoundlist(tab) == VALIDEXPR)
    {
      if (!**tab)
        return TOKENMISS;
      if (!strcmp(**tab, "then"))
      {
        ++(*tab);
        int ret = parse_compoundlist(tab);
        if (ret == VALIDEXPR)
        {
          if (**tab && (!strcmp(**tab, "else") || !strcmp(**tab, "elif")))
          {
            return parse_elseclause(tab);
          }
          return VALIDEXPR;
        }
        else
          return ret != WRONGEXPR ? TOKENMISS : wrong_ret(**tab);
      }
    }
    else
      return WRONGEXPR;
  }
  return wrong_ret(**tab);
}
