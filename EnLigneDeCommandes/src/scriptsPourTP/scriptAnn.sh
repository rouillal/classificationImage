#!/bin/bash

concepts=("aeroplane" "bicycle" "bird" "boat" "bottle" "bus" "car" "cat" "chair" "cow" "diningtable" "dog" "horse" "motorbike" "person" "pottedplant" "sheep" "sofa" "train" "tvmonitor")
for element in ${concepts[@]}
	do
		touch ../train/classificationSift/svm/color_$element.svm
		./read_image ../train/ann/$element.ann.txt ../train/classificationSift/svm/color_$element.svm
	done
