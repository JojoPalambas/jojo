
[[ $- != *i* ]] && return

export LANG=en_US.utf8
export NNTPSERVER="news.epita.fr"



alias ilbullblood='i3lock -c 730800'
alias il='i3lock -i ~/afs/images/GF3.PNG'
alias slrn='slrn -f /home/depott_g/.jnewsrc --create'
alias mygz='tar -zcvf'
alias myungz='tar xf'
alias myuntar='tar -xvf'
alias sou='source ~/.bashrc'
alias mygcc='gcc -Wextra -Wall -Werror -std=c99 -pedantic'
alias gccdb='~/afs/.confs/gccdb.sh'
alias mywc='~/afs/.confs/mywc.sh'

alias ski='~/afs/.confs/ski'
alias ghost='echo Nice pun!'
alias quiche='echo; echo; echo ODILE_G !!!; echo; echo'
alias 3615='firefox'
alias sl2='while [ 1 ]; do sl -al; done'
alias lsd='sl'

alias mkaut='~/afs/.confs/mkaut.sh'
alias mktest='~/afs/.confs/mktest.sh'
alias mkfile='~/afs/.confs/mkfile.sh'
alias vimc='~/afs/.confs/vimc.sh'

alias conftp='cd ~/afs/.confs'

alias corbtp='cd ~/afs/corb'
alias corb='~/afs/.confs/corb.sh'

export EDITOR=vim

alias ls='ls --color=auto'
alias emacs='emacs -nw'

PS1="\e[4;33m[\A @ \W]\e[0;33m >\e[0;37m "
#PS1='[\u@\h \W]\$ '

LS_COLORS=$LS_COLORS:'di=36:'
export LS_COLORS
