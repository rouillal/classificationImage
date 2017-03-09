#!/bin/bash

concepts=("aeroplane" "bicycle" "bird" "boat" "bottle" "bus" "car" "cat" "chair" "cow" "diningtable" "dog" "horse" "motorbike" "person" "pottedplant" "sheep" "sofa" "train" "tvmonitor")
for element in ${concepts[@]}
	do
		./read_image ../val/classificationSift/out/color_$element.out $element
#		./trec_eval.9.0/trec_eval ../val/rel/$element.rel  ../val/top/$element.top
	done
