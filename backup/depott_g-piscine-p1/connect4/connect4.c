#include <stdio.h>

int check_line(char* game[], size_t columns, size_t lines, int n)
{
  int win = 0;
  char cur = '-';
  char nb = 0;
  for (unsigned i = 0; i < columns && nb < 4; i++)
  {
    if (game[n * columns + i] == cur)
      nb += 1;
    else
    {
      cur = game[n * columns + i];
      nb = 1;
    }
    if (nb >= 4)
    {
      switch(cur)
      case 'X':
        win = 1;
        break;
      case 'O':
        win = 2;;
        break;
      default:
        win = 0;;
    }
  }
  return win;
}

int check_column(char* game[], size_t columns, size_t lines, int n)
{
  int win = 0;
  char cur = '-';
  char nb = 0;
  for (unsigned i = 0; i < lines && nb < 4; i++)
  {
    if (game[lines * i + n] == cur)
      nb += 1;
    else
    {
      cur = game[lines * i + n];
      nb = 1;
    }
    if (nb >= 4)
    {
      switch(cur)
      case 'X':
        win = 1;
        break;
      case 'O':
        win = 2;;
        break;
      default:
        win = 0;;
    }
  }
  return win;
}

int connect4(char* game[], size_t columns, size_t lines)
{
  int win = 0;
  unsigned i = 0;
  while (i < lines && win == 0)
  {
    win = check_line(game, columns, lines, i);
    i++;
  }
  while (i < columns && win == 0)
  {
    win = check_column(game, columns, lines, i);
    i++;
  }

  return win;
}}
