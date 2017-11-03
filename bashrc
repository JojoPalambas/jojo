[[ $- != *i* ]] && return

export LANG=en_US.utf8
export NNTPSERVER="news.epita.fr"

# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
case $- in
    *i*) ;;
      *) return;;
esac

# don't put duplicate lines or lines starting with space in the history.
# See bash(1) for more options
HISTCONTROL=ignoreboth

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# If set, the pattern "**" used in a pathname expansion context will
# match all files and zero or more directories and subdirectories.
#shopt -s globstar

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "${debian_chroot:-}" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color|*-256color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48

alias ilbullblood='i3lock -c 730800'
alias il='i3lock -i ~/afs/images/GF3.PNG'
alias slrn='slrn -f /home/depott_g/.jnewsrc --create'
alias mygz='tar -zcvf'
alias myungz='tar xf'
alias myuntar='tar -xvf'
alias sou='source ~/.bashrc'
alias mygcc='gcc -Wextra -Wall -Werror -std=c99 -pedantic'
alias gccdb='~/commands/gccdb.sh'
alias mywc='~/commands/mywc.sh'

alias ski='~/commands/ski'
alias ghost='echo Nice pun!'
alias quiche='echo; echo; echo ODILE_G !!!; echo; echo'
alias 3615='firefox'
alias sl2='while [ 1 ]; do sl -al; done'
alias lsd='sl'
alias lds='sl'

alias mkaut='~/commands/mkaut.sh'
alias mktest='~/commands/mktest.sh'
alias mkfile='~/commands/mkfile.sh'
alias vimc='~/commands/vimc.sh'

alias conftp='cd ~/commands'

alias corbtp='cd ~/corb'
alias corb='~/commands/corb.sh'

export EDITOR=vim

alias ls='ls --color=auto'
alias emacs='emacs -nw'

#PS1="\e[4;33m[\A @ \W]\e[0;33m >\e[0;37m "
#PS1='[\u@\h \W]\$ '

#LS_COLORS=$LS_COLORS:'di=36:'
#export LS_COLORS
