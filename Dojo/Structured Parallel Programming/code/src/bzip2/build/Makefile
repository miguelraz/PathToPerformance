# Set MODEL to tbb or cilkplus.  The value deterimines which version of bzip2 to build.
MODEL = tbb
#MODEL = cilkplus

TARGET = bzip2-$(MODEL)$(EXE)
SRC = ../bzip2-src/bzlib.cpp ../bzip2-src/blocksort.c ../bzip2-src/crctable.c ../bzip2-src/decompress.c ../bzip2-src/huffman.c ../bzip2-src/randtable.c ../bzip2-src/compress_$(MODEL).cpp ../bzip2-src/bzip2.cpp
RUN_ARGS = -9 <foo.txt >foo.bz2
OTHER_CLEAN = foo.txt foo.bz2 ngram$(EXE)

include ../../../config/rules.inc

ifeq ($(MODEL),tbb)
    CPLUS_FLAGS += -DBZLIB_TBB
    OTHER_CLEAN += bzip2-cilkplus$(EXE)
else
    ifeq ($(MODEL),cilkplus)
        CPLUS_FLAGS += -DBZLIB_CILKPLUS
        OTHER_CLEAN += bzip2-tbb$(EXE)
    else
        $(error Makefile must set MODEL to tbb of cilkplus)
    endif
endif

$(TARGET): Makefile $(SRC)

# Before running, be sure that sample input file is available.
run: foo.txt

# Rule for creating sample input file with the text generator.
foo.txt: ngram$(EXE) ../ngram/alice.html
	ngram$(EXE) 250000000 ../ngram/alice.html foo.txt

# Rule for building text generator.
ngram$(EXE): ../ngram/ngram.cpp
	$(CPLUS) $(CPLUS_FLAGS) ../ngram/ngram.cpp $(EXE_KEY)$@

	
