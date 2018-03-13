#include <stdio.h>
#include <string.h>

#include "grammar_check.h"

int parse_dogroup(char ***tab)
{
  if (!**tab)
    return TOKENMISS;
  if (!strcmp(**tab, "do"))
  {
    ++(*tab);
    int res = parse_compoundlist(tab);
    if (res != WRONGEXPR)
    {
      if (res == TOKENMISS)
        return TOKENMISS;
      if (!**tab)
        return TOKENMISS;
      if (!strcmp(**tab, "done"))
      {
        ++(*tab);
        return VALIDEXPR;
      }
    }
  }
  return wrong_ret(**tab);
}
