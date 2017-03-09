#!/bin/bash

#Conversion de l'image en histogramme de couleurs
echo "[INFO]Conversion de l'image en histogramme de couleurs"
./toSvmColor $1

#Prédiction des scores de classification par concept
echo "[INFO]Prédiction des scores de classification par concept"
concepts=("aeroplane" "bicycle" "bird" "boat" "bottle" "bus" "car" "cat" "chair" "cow" "diningtable" "dog" "horse" "motorbike" "person" "pottedplant" "sheep" "sofa" "train" "tvmonitor")
for element in ${concepts[@]}
	do
        ./svm-predict -b 1 ../test/histoColor.svm ../train/model/color_$element.model ../test/color_$element.out
#Création fichier résultat des scores de classification par concept et par l'histogramme de couleurs
	./probasConceptsColor ../test/color_$element.out $element ../test/res.txt
	done

rm ../test/*.out
rm ../test/histoColor.svm

#Tri des scores de classification par concept du plus probable au moins probable
echo "[INFO]Tri des scores de classification par concept du plus probable au moins probable"
echo | sort -r -nk1,1 ../test/res.txt

rm ../test/res.txt



