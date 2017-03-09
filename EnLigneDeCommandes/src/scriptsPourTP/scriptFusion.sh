#!/bin/bash

scale=2
concepts=("all" "aeroplane" "bicycle" "bird" "boat" "bottle" "bus" "car" "cat" "chair" "cow" "diningtable" "dog" "horse" "motorbike" "person" "pottedplant" "sheep" "sofa" "train" "tvmonitor")
for element in ${concepts[@]}
do
i=1
for LINE in ../val/fusion/top/*.top
do
var=$(./trec_eval.9.0/trec_eval -q ../val/classificationSift/all.rel $LINE | grep map |cut -d ' ' -f 20| cut -d$'\t' -f 2-4 |grep $element | cut -d$'\t' -f 2 )
cpt=$(echo "$i/10"|bc -l | sed 's/^\./0./;s/0*$//')
echo $cpt" "$var >>../val/fusion/csv/$element.csv
let i="$i+1"
done

echo "set terminal png size 800,600" > gnuplot_script
echo "set output '../val/fusion/png/$element.png'" >> gnuplot_script
echo "set title 'MAP en fonction des scores de classification par histos de sifts et couleurs pour $element'" >> gnuplot_script
echo "set ylabel 'Score MAP'" >> gnuplot_script
echo "set xlabel 'Proportion score de classification par histos de couleurs'" >> gnuplot_script
echo "plot '../val/fusion/csv/$element.csv' with linespoints ls 1" >> gnuplot_script

gnuplot gnuplot_script
rm gnuplot_script

done
