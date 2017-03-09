#!/bin/bash

find "../val/1nn/" -type f | while read LINE
do
./read_image $LINE
done
