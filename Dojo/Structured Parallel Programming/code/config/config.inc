# Set CPLUS to a supported compiler, i.e. one of: icpc, g++, icl, cl.
#CPLUS = icpc 
#CPLUS = g++
#CPLUS = icl
#CPLUS = cl

#----------------------------------------------------------------------------a
# You should not need to change the lines below.
#----------------------------------------------------------------------------

ifdef CPLUS
CPLUS := $(strip $(CPLUS))
endif

ifeq ($(CPLUS),icpc)
    # Settings for using Intel C++ compiler 12.1 or later on Linux or Mac OS.
    CPLUS_FLAGS = -std=c++0x -openmp -O2 -xHost -ansi-alias -DHAVE_OPENMP=1 -DHAVE_CILKPLUS=1
    LIBS = -ltbb
endif

ifeq ($(CPLUS),g++)
    # Settings for using gcc on Linux or Mac OS
    CPLUS_FLAGS = -std=c++0x -O2 -DHAVE_OPENMP=1 -DHAVE_CILKPLUS=0 
    LIBS = -ltbb -lgomp
endif

ifeq ($(CPLUS),cl)
    # Settings for using Microsoft C++ compiler on Microsoft Windows
    # The OpenMP examples require OpenMP 3.0, but cl supports only OpenMP 2.0, so HAVE_OPENMP is set to 0 here.
    OS = windows
    CPLUS_FLAGS = /O2 /EHsc /openmp /DHAVE_OPENMP=0 /DHAVE_CILKPLUS=0
endif

ifeq ($(CPLUS),icl)
    # Settings for using Intel C++ compiler on Microsoft Windows
    OS = windows
    CPLUS_FLAGS = /O2 /EHsc /QxHost /Qansi-alias /DHAVE_OPENMP=0 /DHAVE_CILKPLUS=0
endif

# Set compiler flags particular to an OS
ifeq ($(OS),windows)
    EXE_KEY = /Fe#
    INCLUDE_KEY = /I
    EXE = .exe
    RM = del 
else
    EXE_KEY = -o #
    INCLUDE_KEY = -I
    EXE = .x
    RM = rm -f 
    ifeq ($(shell uname -s),Linux)
        LIBS += -lrt 
    endif
endif

