#include <stdio.h>
#include <string.h>

#include "grammar_check.h"


int parse_redirection(char ***tab)
{
  if (isRedirection(**tab))
  {
    ++*tab;
    if (*tab)
      return isWord(**tab) ? VALIDEXPR : wrong_ret(**tab);
  }
  return TOKENMISS;
}

int parse_prefix(char ***tab)
{
  if (isRedirection(**tab))
    return parse_redirection(tab);
  else
    return parse_assignmentword(tab);
}

int parse_element(char ***tab)
{
  if (isWord(**tab) && !(isRedirection(**tab)))
    return VALIDEXPR;
  return parse_redirection(tab);
}

int parse_assignmentword(char ***tab)
{
  if (***tab != '=')
    ++*tab;
  if (***tab == '=')
    ++*tab;
  else
    return wrong_ret(**tab);
  if (***tab)
  {
    ++*tab;
    return VALIDEXPR;
  }
  return TOKENMISS;
}
