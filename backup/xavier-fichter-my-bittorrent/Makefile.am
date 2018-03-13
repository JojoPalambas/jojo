# Author: xavier.fichter

srcdir= .

UFILES= aclocal.m4  autom4te.cache  config.h config.status  depcomp ar-lib \
config.h.in configure install-sh Makefile.in compile config.log missing \
stamp-h1 .deps src/.deps src/.dirstamp tmp

bin_PROGRAMS = my_bittorrent
AM_LDFLAGS = -lcurl -lcrypto
my_bittorrent_SOURCES = src/bittorrent.c \
                        src/cmd_line_parsing.c \
                        src/dictionnary.c \
                        src/list.c \
                        src/mystr.c \
                        src/torrent_parsing.c
my_bittorrent_CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99

EXTRA_DIST = $(srcdir)/tests/test.sh

check-local:
	$(srcdir)/tests/test.sh

RM= rm -rf

clean-local:
	$(RM) $(UFILES)
