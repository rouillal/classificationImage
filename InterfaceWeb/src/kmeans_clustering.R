#!/usr/bin/R

# ${1} feature vectors file
# ${2} codebook size
# ${3} directoy where we want to save the results
# ${4} number max of iteration for clustering

# R --slave --no-save --no-restore --no-environ --args '/tmp/input/features.txt' 2000 '/tmp/output/' 50 < gen_clusters_v2.R


cmd_args=commandArgs();
tmptable=read.table(cmd_args[7], sep=" ", colClasses="numeric", comment.char="");
k=kmeans(tmptable,as.integer(cmd_args[8]),as.integer(cmd_args[10]));

tmpname=as.name(cmd_args[9]);

write.table(k$centers,paste(tmpname, sep=""));

