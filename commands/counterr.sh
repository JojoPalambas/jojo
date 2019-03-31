#!/bin/bash

touch .out
touch .err

out_bytes=0
out_chars=0
out_words=0
out_lines=0

err_bytes=0
err_chars=0
err_words=0
err_lines=0

echo
echo "- Processing..."

$1 1>.out 2>.err

out_bytes=$(cat .out | wc -c)
out_chars=$(cat .out | wc -m)
out_words=$(cat .out | wc -w)
out_lines=$(cat .out | wc -l)

err_bytes=$(cat .err | wc -c)
err_chars=$(cat .err | wc -m)
err_words=$(cat .err | wc -w)
err_lines=$(cat .err | wc -l)

echo "- Finished!"

echo
echo "========== OUT =========="
echo
echo "Bytes: $out_bytes"
echo "Chars: $out_chars"
echo "Words: $out_words"
echo "Lines: $out_lines"

echo
echo "========== ERR =========="
echo
echo "Bytes: $err_bytes"
echo "Chars: $err_chars"
echo "Words: $err_words"
echo "Lines: $err_lines"

echo

rm .out
rm .err
