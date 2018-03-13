/**
** \file lexer.h
** \brief header file for the lexer
** \author Dylan ZHAO
** \version 0.5
** \date 2017-12-19
**
** list of the lexer's function
*/
#ifndef LEXER_H
# define LEXER_H
#include <stdio.h>



/**
**  The token_list structure is used to return a char** containning the
**  tokenization of a string. The size member indicate the size of the
**  token_list.
*/
struct token_list
{
  char **token;
  size_t size;
};


/**
**  The function tab_len() takes a char ** array as parameter and
**  return its length
*/
size_t tab_len(const char **tab);

/**
**  The function free_token_list() takes a token_list as parameter
**  and free all the content of its member 'token' before it free itself.
**  if parameter is NULL, free_token_list() should not do anything.
*/
void free_token_list(struct token_list *t);

/**
**  The function is_comment() takes a char* and an index start as
**  parameters. If there is a comment, the function sould return
**  the position of the end of the comment. Otherwise -1 is returned.
*/
int is_comment(const char *a, size_t start);

/**
**  The function matching_pairs() takes a char* as input, i as start position,
**  and j to return the position of the end of the matching pairs.
**  It uses a helper function as follow :
**  size_t matching_pairs_rec(const char *a, size_t start, char open, char end);
**  it should return 0 and put the end index in j, otherwise -1 is returned.
*/
int matching_pairs(const char *a, size_t i, size_t *j);

/**
**  The function check_delim() takes a char * as input, a char ** containing
**  the list of the delimiters we want to check and len wich represent
**  the number of character compared on a successful return.
**  It return 0 on a successful call, -1 otherwise.
*/
int check_delim(const char *a, const char *list[], int *len);

/**
**  The function split takes a char* as input, and return the tokenized input
**  in a char**.
*/
struct token_list *split(char *input);

/**
**  lexer() is the main function, it calls split().
*/
struct token_list *lexer(char *input);

#endif /* LEXER_H */
