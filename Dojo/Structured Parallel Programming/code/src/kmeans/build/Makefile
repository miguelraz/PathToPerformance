TARGET = test_kmeans$(EXE)
SRC = ../cilkplus/kmeans_cilk.cpp ../common/repair_empty_clusters.cpp ../common/test_kmeans.cpp ../tbb/kmeans_tbb.cpp

include ../../../config/rules.inc

$(TARGET): Makefile $(SRC) ../cilkplus/*.h ../tbb/*.h 
