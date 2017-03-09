#!/bin/bash

concepts=("aeroplane" "bicycle" "bird" "boat" "bottle" "bus" "car" "cat" "chair" "cow" "diningtable" "dog" "horse" "motorbike" "person" "pottedplant" "sheep" "sofa" "train" "tvmonitor")
for element in ${concepts[@]}
	do
		./libsvm-3.22/svm-train -b 1 -g 1 -w+1 19 ../train/classificationSift/svm/color_$element.svm ../train/classificationSift/model/color_$element.model
        ./libsvm-3.22/svm-predict -b 1 ../val/classificationSift/histo.svm ../train/classificationSift/model/color_$element.model ../val/classificationSift/out/color_$element.out
	done
