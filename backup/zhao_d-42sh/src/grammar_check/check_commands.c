#include <stdio.h>
#include <string.h>

#include "grammar_check.h"

int parse_command(char ***tab)
{
  const char *firstshellcmd[8] =
  {
    "(",
    "{",
    "for",
    "while",
    "until",
    "case",
    "if"
  };
  if (!strcmp(**tab, "function") ||(*(*tab+1) && **(*tab+1) == '='))
    return parse_funcdec(tab);
  else if (isin(**tab, firstshellcmd))
    return parse_shellcommand(tab);
  else
    return parse_simplecommand(tab);
}

int parse_simplecommand(char ***tab)
{
  const char *followsimplecommand[11] =
  {
    "|", "||", "&&", "done", "fi", "esac", ";", ";;", "\n"
  };
  int ret = WRONGEXPR;
  while  (*(*tab+1) && ((**(*tab+1) == '=') || isRedirection(**tab))) // prefix
  {
    ret = parse_prefix(tab);
    if (ret != VALIDEXPR)
      return WRONGEXPR;
  }
  if (isWord(**tab) || isRedirection(**tab))
  {
    while (**tab && (isWord(**tab) || !isRedirection(**tab))
        && !isin(**tab, followsimplecommand))  //element
      ++*tab;
    ret = VALIDEXPR;
  }
  else
    if (ret != WRONGEXPR)
      return ret;
  return (!**tab || isin(**tab, followsimplecommand)) ? VALIDEXPR : TOKENMISS;
}

int parse_shellcommand(char ***tab)
{
  int ret = 0;
  if (***tab == '(')
  {
    ++*tab;
    ret = parse_compoundlist(tab);
    if (ret != VALIDEXPR)
      return ret;
    if (**(*tab+1) == ')')
      return VALIDEXPR;
    else return TOKENMISS;
  }
  if (***tab == '{')
  {
    ++*tab;
    ret = parse_compoundlist(tab);
    if (ret != VALIDEXPR)
      return ret;
    if (**(*tab+1) == '}')
      return VALIDEXPR;
    else return TOKENMISS;
  }
  if (!strcmp(**tab,"for"))
    return parse_rulefor(tab);
  if (!strcmp(**tab,"while"))
    return parse_rulewhile(tab);
  if (!strcmp(**tab,"until"))
    return parse_ruleuntil(tab);
  if (!strcmp(**tab,"case"))
    return parse_case(tab);
  if (!strcmp(**tab,"if"))
    return parse_if(tab);
  return wrong_ret(**tab);
}

int parse_list(char ***tab)
{
  int ret = parse_andor(tab);
  if (ret == TOKENMISS)
    return TOKENMISS;
  if (ret == WRONGEXPR)
    return WRONGEXPR;
  if (!**tab || ***tab == '\n' || (((***tab == '&' || ***tab == ';'))
        && !**(*tab+1)))
    return VALIDEXPR;
  else if (((***tab == '&' || ***tab == ';')))
  {
    ++*tab;
    return parse_list(tab);
  }
  return WRONGEXPR;
}
