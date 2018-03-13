/* Author: xavier.fichter */

#ifndef BITTORRENT_H
#define BITTORRENT_H

/*==================================INCLUDES=================================*/

#include <err.h>
#include <curl/curl.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>

/*===================================MACROS==================================*/



/*=================================STRUCTURES================================*/

struct cmdline
{
  char **files;
  unsigned options;
};

enum e_type
{
  INTEGER,
  STRING,
  LIST,
  DICTIONNARY
};

union u_type
{
  int integer;
  char *string;
  struct list *list;
  struct dictionnary *dictionnary;
};

struct b_type
{
  enum e_type type;
  union u_type value;
};

struct list
{
  struct b_type data;
  struct list *next;
};

struct dictionnary
{
  char *key;
  struct b_type value;
  struct dictionnary *next;
};

/*=================================FUNCTIONS=================================*/

/* mystr.c */
size_t mystrlen(char *str);
int mystrcmp(char *a, char *b);
int mystr_in(char **tab, size_t len, char *str);
void mystr_print(char *str);
char *concatx(char *s1, size_t *size1, const char *s2, size_t size2);

/* cmd_line_parsing.c */
struct cmdline *cmd_line_parsing(int argc, char **argv);

/* dictionnary.c */
struct dictionnary *dictionnary_init(char* key, struct b_type value);
void dictionnary_add(struct dictionnary *d, char *key, struct b_type  value);
void dictionnary_print(struct dictionnary *d, unsigned indent);
void dictionnary_free(struct dictionnary *d);

/* list.c */
struct list *list_init(struct b_type data);
void list_add(struct list *l, struct b_type data);
void list_print(struct list *l);
void list_free(struct list *l);

/* torrent_parsing.h */
struct list *list_parsing(FILE *file);
struct dictionnary *dictionnary_parsing(FILE *file);
struct dictionnary *torrent_parsing(char *pathname);
char *get_info_as_str(char *pathname);

/* tracker.c */

#endif
