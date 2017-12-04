/* Author: xavier.fichter */

#include "bittorrent.h"

/* create a new cmdline struct with the array given as argument */

static struct cmdline *cmdline_init(size_t nb_files)
{
  struct cmdline *cmdline = malloc(sizeof(struct cmdline));
  cmdline->files = malloc(nb_files * sizeof(char *));
  cmdline->options = 0;
  return cmdline;
}

/* transform an option in the associated integer */

static unsigned get_opt(char *opt)
{
  switch(opt[2])
  {
    case 'v':
      return 1;
      break;
    case 's':
      return 2;
      break;
    case 'p':
      return 4;
      break;
    case 'd':
      return 8;
      break;
    default:
      return -1;
  }
  return -1;
}

/* init tab[ind] to str */

static void add_files(char **tab, size_t ind, char *str)
{
  tab[ind] = calloc(mystrlen(str) + 1, sizeof(char));
  for(size_t i = 0 ; i < mystrlen(str) ; i++)
    tab[ind][i] = str[i];
}

/* parse the command line and return a cmdline struct containing all
                                                                informations */

struct cmdline *cmd_line_parsing(int argc, char **argv)
{
  size_t nb_files = 0;
  char *opt[4] = {"--seed", "--pretty-print-torrent-file", "--dump-peers",
                                                                  "--verbose"};
  for(int j = 1 ; j < argc ; j++)
  {
    if(!mystr_in(opt, 4, argv[j]))
      nb_files++;
  }

  struct cmdline *cmdline  = cmdline_init(nb_files);
  size_t f_ind = 0;

  for(int i = 1 ; i < argc ; i++)
  {
    if(mystr_in(opt, 4, argv[i]))
      cmdline->options += get_opt(argv[i]);
    else
    {
      add_files(cmdline->files, f_ind, argv[i]);
      f_ind++;
    }
  }
  return cmdline;
}
