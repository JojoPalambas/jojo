#ifndef _42SH_H
# define _42SH_H

# define VERSION 1.0

/**
** Representing the options given in the commandline
*/
enum flags
{
  FLAG_C=1,
  FLAG_O=2,
  FLAG_NORC=4,
  FLAG_AST=8,
  FLAG_VERSION=16
};

/**
** Global variable that represents the environment
*/
struct metadata
{
  unsigned flags;           /**< Flags given in the commandline */
} metadata;

/**
** \brief Sets the options given in the commandline
** \param argv Options given
** \return an unsigned char representing the flags
*/
unsigned set_flag(char **argv);

/**
** \prief Checks the in the global variable
** \param flags  flag to check
** \return a non null value if the flag is set
*/
unsigned check_flag(enum flags flags);

char *get_val(char *key);

#endif /* !42SH_H */
