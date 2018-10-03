####################################
###                           ######
###         MAKEFILE          ######
###                           ######
####################################

##include Makefile.common

# directory names
SRC_DIR = $(PWD)/src
INCLUDE_DIR = $(PWD)/include
BIN_DIR = $(PWD)

# source files
SRCFILES = $(wildcard *.cc $(SRC_DIR)/*.cc)
OBJFILES= $(patsubst %.cc, %.o, $(SRCFILES))

## ROOT flags
CPPFLAGS_ROOT=$(shell root-config --cflags)
LDFLAGS_ROOT=$(shell root-config --libs) -lMinuit -lEG

# COAST flags
COAST_INCDIR=$(COAST_DIR)/include
COAST_LIBDIR=$(COAST_DIR)/lib
CPPFLAGS_COAST=-I$(COAST_INCDIR)
LDFLAGS_COAST=-L$(COAST_LIBDIR) -lCorsikaFileIO -lCorsikaIntern -lMachineIndependent -lCorsikaROOTOut -lCorsikaROOT -lCorsikaToROOT

# COMPILER FLAGS
CXXFLAGS += -O2 -std=c++11 -Wall -fPIC -pthread -m64

## INCLUDES
CPPFLAGS+=-I$(INCLUDE_DIR)
CPPFLAGS+=$(CPPFLAGS_ROOT)
CPPFLAGS+=$(CPPFLAGS_COAST)


## LIBRARY FLAGS
LDFLAGS+=$(LDFLAGS_ROOT)
LDFLAGS+=$(LDFLAGS_COAST)

## EXECUTABLE NAME
EXE = CorsikaROOTReader


#####################################################

.PHONY: all depend clean

all: $(EXE)

$(EXE): $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(CPPFLAGS) $(LDFLAGS)


depend: Make-depend

Make-depend: $(SRCFILES)
	$(CPP) $(CXXFLAGS) $(CPPFLAGS) -MM $^ > $@


clean:
	- rm -f $(OBJFILES) $(EXE) *.o *.so *.ps core


