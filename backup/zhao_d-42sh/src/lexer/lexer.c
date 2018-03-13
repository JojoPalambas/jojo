#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "lexer.h"

static const char *delim[] =
{
  "(", ")", "[", "]", "{", "}", "<<-", "<<", "<&", "<>", ">|", ">>", ">&",
  ">", "<", "\n", "!", "||", "|", "&&", "&", ";;", ";", "=", "\'", "\"", NULL
};


static const char *redirection[] =
{
  "<<-", "<<", "<&", "<>", ">|", ">>", ">&",">", "<", NULL
};


int is_redirection(const char *input, size_t i, size_t *j)
{
  size_t tmp = *j + 1;
  int o = 0;
  while (input[i + tmp] && input[i + tmp] >= '0' && input[i + tmp] <= '9')
  {
    tmp++;
  }
  if (!check_delim(input + i + tmp, redirection, &o))
  {
    *j = tmp + o - 1;
    return 0;
  }
  return -1;
}


size_t tab_len(const char **tab)
{
  size_t len = 0;
  while (tab[len])
    len++;
  return len;
}

void free_token_list(struct token_list *t)
{
  if (t)
  {
    for (size_t i = 0; i < t->size; i++)
      free(t->token[i]);
    free(t->token);
    free(t);
  }
  t = NULL;
}

int is_comment(const char *a, size_t start)
{
  if (a[start] != '#')
    return -1;
  size_t pos = 1;
  while (a[start + pos] != '\n' && a[start + pos] != '\0')
    pos++;
  return pos + 1;
}

size_t matching_pairs_rec(const char *a, size_t start, char open, char end)
{
  size_t counter = 1;
  size_t pos = 0;
  while (counter > 0 && a[start + pos])
  {
    char c = a[start + ++pos];
    if (c == open) {
      counter++;
    }
    else if (c == end) {
      counter--;
    }
  }
  return pos + 1;
}

int matching_pairs(const char *a, size_t i, size_t *j)
{
  if (!a)
    return -1;
  char s = a[i + *j];
  switch (s)
  {
    case '(':
      *j = matching_pairs_rec(a, i, '(', ')');
      break;
    case '{':
      *j = matching_pairs_rec(a, i, '{', '}');
      break;
      //  case '\'':
    case '\"':
      *j = matching_pairs_rec(a, i, s, s);
      break;
    default:
      return -1;
      break;
  }
  return 0;
}


/* len represent the number of character compared on a successful return */
int check_delim(const char *a, const char *list[], int *len)
{
  if (!a)
    return -1;
  int correct = 0;
  size_t l = tab_len(list);
  size_t len_a = strlen(a);
  for (size_t i = 0; i < l; i++)
  {
    correct = 0;
    *len = 0;
    size_t list_len = strlen(list[i]);
    for (size_t j = 0; j < list_len && j < len_a; j++)
    {
      if (/*list[i][j] != '\0' &&*/ *(a + j) != list[i][j])
        correct = -1;
      if (correct == -1)
        continue;
      *len += 1;
    }
    if (correct == 0)
      return 0;
  }
  return -1;
}


struct token_list *split(char *input)
{
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;
  short space = 0;
  int delim_len = 0;
  struct token_list *t = malloc(sizeof(struct token_list));
  t->size = strlen(input);
  t->token = malloc(t->size * sizeof(char *) + 2);
  char **tmp = t->token;
  short alone = 0;
  while (i < t->size)
  {
    j = 0;
    space = 0;
    alone = 0;

    while (input[i + j] && (i + j) < t->size)
    {
      if (j == 0 && input[i] == '$' && matching_pairs(input, i + 1, &j) != -1)
      {
        j++;
        break;
      }
      if (j == 0 && input[i] >= '0' && input[i] <= '9' &&
          !is_redirection(input, i, &j))
      {
        j++;
       // printf("->%c\n", input[i]);
        break;
      }
      if (input[i + j] == ' ')
      {
        space++;
        j++;
        break;
      }
      else if (!check_delim(input + i + j, delim, &delim_len))
      {
        j = (alone == 1)? j: j + delim_len; // j + 1 + delim_len ?
        break;
      }
      else
        alone = 1;
      j++;
    }
    size_t len = j - space;
    if (len > 0)
    {
      tmp[k] = malloc(len + 1);
      for (size_t x = 0; x < len; x++)
        tmp[k][x] = input[i + x];
      tmp[k][len] = '\0';
      k++;
    }
    i += j;
  }
  t->size = k;
  t->token[k] = NULL;
  return t;
}

struct token_list *lexer(char *input)
{
  return split(input);
}


/*
int main(int argc, char *argv[])
{
  char test[] = "if test 1 -eq 2 ;then do ;;;; echo truruijgljg done\n";//    1>file1 3> file2 918747891273>> file3";//"${totor}totor $asb ${qee} <> >> 1234>popo 1>2 1>file 3142>file";
  if (argc == 2)
  {
    printf("input: %s\n", argv[1]);
    struct token_list *t = split(argv[1]);
    size_t i = 0;
    while (i < t->size)
    {
      printf("%s\n", t->token[i]);
      i++;
    }
    free_token_list(t);
  }
  else
  {
    printf("input: %s\n", test);
    struct token_list *t = split(test);
    size_t i = 0;
    while (i < t->size)
    {
      printf(" %s\n", t->token[i]);
      i++;
    }
    free_token_list(t);
  }
  return 0;
}*/
