/**
** \file grammar_check.h
** \brief Header file for the grammar checking
** \author Vincent TRINH
** \version 0.9
** \date 2017-12-14
**
** \return Every functions in this header return an integer represented by a
** macro that can be TOKENMISS VALIDEXPR or WRONGEXPR
*/

#ifndef GRAMMAR_CHECK_H
# define GRAMMAR_CHECK_H

# define TOKENMISS 2 /**< \brief Returned if a token is missing */
# define VALIDEXPR 1 /**< \brief Returned if it is a valid expression */
# define WRONGEXPR 0 /**< \brief Returned if the expression is totally wrong */

/**
** \brief Checks if it is a correct input. This is the essential function that
** is called to check if an input is right or not
** \param tab List of tokens given by the lexer
*/
int parse_input(char **tab);
/**
** \brief Checks if it is an asignment word
*/
int parse_assignment_word(char ***tab);
/**
** \brief Checks if it is a command list
*/
int parse_list(char ***tab);
/**
** \brief Checks the 'andor' rule
*/
int parse_andor(char ***tab);
/**
** \brief Checks the 'pipeline' rule
*/
int parse_pipeline(char ***tab);
/**
** \brief Checks the 'command' rule
*/
int parse_command(char ***tab);
/**
** \brief Checks the 'simple_command' rule
*/
int parse_simplecommand(char ***tab);
/**
** \brief Checks the 'shell_command' rule
*/
int parse_shellcommand(char ***tab);
/**
** \brief Checks the 'funcdec' rule
*/
int parse_funcdec(char ***tab);
/**
** \brief Checks the 'redirection' rule
*/
int parse_redirection(char ***tab);
/**
** \brief Checks the 'prefix' rule
*/
int parse_prefix(char ***tab);
/**
** \brief Checks the 'element' rule
*/
int parse_element(char ***tab);
/**
** \brief Checks the 'compoundlist' rule
*/
int parse_compoundlist(char ***tab);
/**
** \brief Checks the 'rule_for' rule
*/
int parse_rulefor(char ***tab);
/**
** \brief Checks the 'rule_while' rule
*/
int parse_rulewhile(char ***tab);
/**
** \brief Checks the 'rule_until' rule
*/
int parse_ruleuntil(char ***tab);
/**
** \brief Checks the 'case' rule
*/
int parse_case(char ***tab);
/**
** \brief Checks the 'if' rule
*/
int parse_if(char ***tab);
/**
** \brief Checks the 'else_clause' rule
*/
int parse_elseclause(char ***tab);
/**
** \brief Checks the 'do_group' rule
*/
int parse_dogroup(char ***tab);
/**
** \brief Checks the 'else_clause' rule
*/
int parse_caseclause(char ***tab);
/**
** \brief Checks the 'case_item' rule
*/
int parse_caseitem(char ***tab);
/**
** \brief checks if the given string is a redirection
*/
int isRedirection(char *str);
/**
** \brief Checks if a given string is in a list of strings
*/
int isin(char *val, const char **list);
/**
** \brief Checks if a string given is a word
*/
int isWord(char *s);
/**
** \brief Checks if a given string is a valid variable name
*/
int isVariable(char *s);
/**
** \brief Checks if the following expression is an assignment word
*/
int parse_assignmentword(char ***tab);
/**
** Returns WRONGEXPR and displays an error message
*/
int wrong_ret(char *s);

#endif
