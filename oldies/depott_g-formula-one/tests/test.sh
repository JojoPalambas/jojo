#!/bin/bash

path=$PWD
echo "$path"

cd `mktemp -d`
cmake $path
make check;

echo "lvl0_grass:"
./check $path/tests/maps/lvl0_grass.frc
echo "\nlvl0_road:"
./check $path/tests/maps/lvl0_road.frc
echo "\nlvl1_round:"
./check $path/tests/maps/lvl1_round.frc
echo "\nlvl2_around_wall:"
./check $path/tests/maps/lvl2_around_wall.frc
echo "\nlvl2_round_block:"
./check $path/tests/maps/lvl2_round_block.frc
echo "\nlvl2_zigzag:"
./check $path/tests/maps/lvl2_zigzag.frc
echo "\nlvl3_complex_zigzags:"
./check $path/tests/maps/lvl3_complex_zigzags.frc
