#!/bin/bash

touch out
touch err

OK="\e[1;32m"
KO="\e[1;31m"
QU="\e[0;33m"
WH="\e[0;37m"

function test
{
    echo

    ./my_bittorrent $1 1> out 2> err
    ans=$?

    err=""
#    if [ $ans = 0 ]; then
#        err="${OK}[OK]${WH}"
#    else
#        err="${KO}[KO]${WH}"
#    fi

    echo -e "Test with ${QU}\"$1\"${WH}"
    echo -e "                               $err"
    echo
    cat out
    echo -e "${KO}"
    cat err
    echo -e "${WH}"
}

echo
echo ----- Beginning of the testsuite
echo

test "tests/torrents/congratulations_basic.torrent"
test "--pretty-print-torrent-file tests/torrents/congratulations_basic.torrent"
test "--verbose tests/torrents/congratulations_basic.torrent"
test "--dump-peers tests/torrents/congratulations_basic.torrent"
test "--verbose --dump-peers tests/torrents/congratulations_basic.torrent"
#test "--verbose --dump-peers tests/torrents/images_basic.torrent"
#test "--verbose --dump-peers tests/torrents/congratulations_rogue.torrent"
#test "--verbose --dump-peers tests/torrents/congratulations_seed.torrent"
test "--verbose --dump-peers tests/torrents/congratulations_slow_disconnect.torrent"
#test "--verbose --dump-peers tests/torrents/congratulations_split.torrent"

echo
echo "----- End of the testsuite"
echo

rm out
rm err
