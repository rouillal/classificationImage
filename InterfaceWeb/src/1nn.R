#!/usr/bin/R

# ${1} feature vectors file on which the centroids are computed (ideally subset of ${5})
# ${2} codebook size
# ${3} directoy where we want to save the results
# ${4} number max of iteration for clustering
# ${5} feature vectors file of the whole corpus on which the mapping is applied

# R --slave --no-save --no-restore --no-environ --args '/home/data/collection/clef/2010/PhotoAnnotation/GENERATED/CODEBOOKS/random_RGSIFT_Vectors.txt' 4000 '/home/data/collection/clef/2010/PhotoAnnotation/GENERATED/CODEBOOKS/RGSIFT4000CB/' 50 < clustering_script.R


cmd_args=commandArgs();
centers=read.table(cmd_args[7]);
# k=kmeans(tmptable,as.integer(cmd_args[8]),as.integer(cmd_args[10]));

library(class)

corpustable=read.table(cmd_args[9], sep=" ", colClasses="numeric", comment.char="");
knnres=knn1(centers, corpustable,factor(c(1:as.integer(cmd_args[8]))))
write.table(knnres,paste(as.name(cmd_args[10]), sep=""),row.names = FALSE, col.names=FALSE, quote=FALSE);



