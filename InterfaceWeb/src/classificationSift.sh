#!/bin/bash

#Conversion de l'image en histogramme de sift
echo "[INFO]Conversion de l'image en histogramme de sift"
./src/colorDescriptor --descriptor sift $1 --output test/image.sift
sed -n '4,$p' test/image.sift | tr -d ";" | sed 's/<CIRCLE [1-9].*> //' > test/imageSift.sift

/usr/local/bin/R --slave --no-save --no-restore --no-environ --args train/centers256.txt 256 test/imageSift.sift test/res1nn.txt < src/1nn.R
./src/toSvmSift

rm test/*.sift
rm test/res1nn.txt

#Prédiction des scores de classification par concept
echo "[INFO]Prédiction des scores de classification par concept"
concepts=("aeroplane" "bicycle" "bird" "boat" "bottle" "bus" "car" "cat" "chair" "cow" "diningtable" "dog" "horse" "motorbike" "person" "pottedplant" "sheep" "sofa" "train" "tvmonitor")
for element in ${concepts[@]}
	do
        ./src/svm-predict -b 1 test/histoSift.svm train/classificationSift/model/color_$element.model test/sift_$element.out
#Création fichier résultat des scores de classification par concept et par l'histogramme de sift
	./src/probasConceptsColor test/sift_$element.out $element test/res.txt
	done

rm test/*.out
rm test/histoSift.svm

#Tri des scores de classification par concept du plus probable au moins probable
echo "[INFO]Tri des scores de classification par concept du plus probable au moins probable"
sort -r -nk1,1 test/res.txt > test/result.txt

rm test/res.txt



