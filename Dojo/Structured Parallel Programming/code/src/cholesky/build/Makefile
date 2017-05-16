TARGET = test_cholesky$(EXE)
SRC =  ../common/test_cholesky.cpp

include ../../../config/rules.inc
LIBS += -lmkl_intel_lp64 -lmkl_sequential -lmkl_core -lpthread -lm
$(TARGET): Makefile ../common/test_cholesky.cpp ../cilkplus/*.h 
