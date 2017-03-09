#!/bin/bash

ls | while read LINE
do
./read_image $LINE >../newSift/$LINE
done
