#!/bin/bash

#Conversion de l'image en histogramme de sift
echo "[INFO]Conversion de l'image en histogramme de sift"
./colorDescriptor --descriptor sift $1 --output ../test/image.sift
sed -n '4,$p' ../test/image.sift | tr -d ";" | sed 's/<CIRCLE [1-9].*> //' > ../test/imageSift.sift

R --slave --no-save --no-restore --no-environ --args ../train/centers256.txt 256 ../test/imageSift.sift ../test/res1nn.txt < 1nn.R
./toSvmSift

rm ../test/*.sift
rm ../test/res1nn.txt

#Conversion de l'image en histogramme de couleurs
echo "[INFO]Conversion de l'image en histogramme de couleurs"
./toSvmColor $1

#Prédiction des scores de classification par concept
echo "[INFO]Prédiction des scores de classification par concept"
concepts=("aeroplane" "bicycle" "bird" "boat" "bottle" "bus" "car" "cat" "chair" "cow" "diningtable" "dog" "horse" "motorbike" "person" "pottedplant" "sheep" "sofa" "train" "tvmonitor")
for element in ${concepts[@]}
	do
        ./svm-predict -b 1 ../test/histoSift.svm ../train/classificationSift/model/color_$element.model ../test/sift_$element.out
#Création fichier résultat des scores de classification par concept et par l'histogramme de sift
	./probasConceptsColor ../test/sift_$element.out $element ../test/res1.txt

        ./svm-predict -b 1 ../test/histoColor.svm ../train/model/color_$element.model ../test/color_$element.out
#Création fichier résultat des scores de classification par concept et par l'histogramme de couleurs
	./probasConceptsColor ../test/color_$element.out $element ../test/res2.txt
	done

rm ../test/*.out
rm ../test/*.svm

#Fusion des scores de classification obtenus par les histos de couleurs et de sift (proportion respective 0,4-0,6)
echo "[INFO]Fusion des scores de classification obtenus par les histos de couleurs et de sift (proportion respective 0,4-0,6)"
./fusionScores

#Tri des scores de classification par concept du plus probable au moins probable
echo "[INFO]Tri des scores de classification par concept du plus probable au moins probable"
echo | sort -r -nk1,1 ../test/resFinal.txt

rm ../test/res1.txt
rm ../test/res2.txt
rm ../test/resFinal.txt



