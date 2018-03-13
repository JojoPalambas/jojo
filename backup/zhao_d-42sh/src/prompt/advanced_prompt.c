#include <stdio.h>
#include "advanced_prompt.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
   char *substitute_prompt(char *s)
   {






   }
   */
char *prompt_substitution(char *s)
{
  size_t len = strlen(s);
  size_t size = len;
  size_t i = 0;
  size_t j = 0;
  char *prompt = malloc(len * 6);
  char *tmp = NULL;
  while (i < len)
  {

    if (!strcmp(s + i,"\\a"))
    {
      memcpy(prompt + j, "\\a", 2);
      i += 2;
      continue;
    }
    if (!strcmp(s + i,"\\d"))
    {
      time_t t = time(NULL);
      struct tm *tm = localtime(&t);
      char date[20] = {0};
      size_t date_len = strftime(date, sizeof(date), "%a %b %d", tm);
      memcpy(prompt + j, date, date_len);
      j += date_len;
      i += 2;
      // free tm ?
      continue;
    }
    if (!strcmp(s + i,"\\D{"))
    {
      char format[512] = {0};
      char date[4096] = {0};
      size_t i2 = i;
      i += 3;
      while (i < len && s[i] != '}')
        format[i - i2] = s[i];
      time_t t = time(NULL);
      struct tm *tm = localtime(&t);
      size_t date_len = strftime(date, 4096, format, tm);
      if (i + date_len > size)
        tmp = realloc(prompt, size + date_len + 1);
      if (tmp)
        prompt = tmp;
      memcpy(prompt + j, date, date_len);
      j += i - i2;
      continue;
    }
    if (!strcmp(s + i,"\\e"))
    {
      memcpy(prompt + j, "\\e", 2);
      i += 2;
      continue;
    }
    if (!strcmp(s + i,"\\h"))
    {

      continue;
    }
    if (!strcmp(s + i,"\\H"))
    {

      continue;
    }
    if (!strcmp(s + i,"\\n"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\r"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\s"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\u"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\w"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\W"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\$"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\nnn"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\\\"))
    {
      continue;
    }
    if (!strcmp(s + i,"\\["))
    {
      continue;
    }
    if (!strcmp(s + i,"\\]y"))
    {
      continue;
    }


  }

  return prompt;
}

/*

int main(void)
{


//  char *s = prompt_substitution();








      return 0;
}
*/
