#!/bin/bash

ls | while read LINE
do
echo $LINE
R --slave --no-save --no-restore --no-environ --args ../centers256.txt 256 $LINE ../1nn/${LINE%%.*}.txt < ../../src/1nn.R
done
