MAKEFILE      = Makefile

EQ            = =

COREDIR       = ../../../src/core
COREOBJDIR    = $(COREDIR)/obj

####### Compiler, tools and options

CC            = gcc
CXX           = g++
CFLAGS        = -pipe -O2 -Wall -W -Wno-psabi -Wno-unused-parameter -D_REENTRANT -fPIC
CFLAGS        = -pipe -O2 -Wall -W -Wno-psabi -Wno-unused-parameter -D_REENTRANT -fPIC
CXXFLAGS      = -pipe -O2 -Wall -W -Wno-psabi -Wno-unused-parameter -D_REENTRANT -fPIC
CXXFLAGS      = -pipe -O2 -Wall -W -Wno-psabi -Wno-unused-parameter -D_REENTRANT -fPIC
INCPATH       = -I. -I$(COREDIR)
DEL_FILE      = rm -f
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = -lpthread

####### Output directory

OBJECTS_DIR   = obj

####### Files

SOURCES       = positions.cpp \
		$(COREDIR)/action.cpp \
		$(COREDIR)/board.cpp \
		$(COREDIR)/check.cpp \
		$(COREDIR)/eval.cpp \
		$(COREDIR)/hash.cpp \
		$(COREDIR)/init.cpp \
		$(COREDIR)/move.cpp \
		$(COREDIR)/play.cpp \
		$(COREDIR)/search.cpp
OBJECTS       = $(OBJECTS_DIR)/positions.o \
		$(COREOBJDIR)/action.o \
		$(COREOBJDIR)/board.o \
		$(COREOBJDIR)/check.o \
		$(COREOBJDIR)/eval.o \
		$(COREOBJDIR)/hash.o \
		$(COREOBJDIR)/init.o \
		$(COREOBJDIR)/move.o \
		$(COREOBJDIR)/play.o \
		$(COREOBJDIR)/search.o
TARGET        = run_test.out


first: all
####### Build rules

$(TARGET):  $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

all: makedirs $(TARGET)

clean:
	@rm -rf $(OBJECTS_DIR)

makedirs:
	@test -d $(OBJECTS_DIR) || mkdir -p $(OBJECTS_DIR)
	@test -d $(COREOBJDIR) || mkdir -p $(COREOBJDIR)

####### Compile

$(OBJECTS_DIR)/positions.o: positions.cpp positions.h \
		$(COREDIR)/action.h \
		$(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h \
		$(COREDIR)/eval.h \
		$(COREDIR)/hash.h \
		$(COREDIR)/play.h \
		$(COREDIR)/parse.h \
		$(COREDIR)/search.h \
		$(COREDIR)/init.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(OBJECTS_DIR)/positions.o positions.cpp

$(COREOBJDIR)/action.o: $(COREDIR)/action.cpp $(COREDIR)/action.h \
		$(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h \
		$(COREDIR)/eval.h \
		$(COREDIR)/hash.h \
		$(COREDIR)/play.h \
		$(COREDIR)/search.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/action.o $(COREDIR)/action.cpp

$(COREOBJDIR)/board.o: $(COREDIR)/board.cpp $(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/board.o $(COREDIR)/board.cpp

$(COREOBJDIR)/check.o: $(COREDIR)/check.cpp $(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/check.o $(COREDIR)/check.cpp

$(COREOBJDIR)/eval.o: $(COREDIR)/eval.cpp $(COREDIR)/eval.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/twiddle.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/eval.o $(COREDIR)/eval.cpp

$(COREOBJDIR)/hash.o: $(COREDIR)/hash.cpp $(COREDIR)/hash.h \
		$(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/hash.o $(COREDIR)/hash.cpp

$(COREOBJDIR)/init.o: $(COREDIR)/init.cpp $(COREDIR)/init.h \
		$(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h \
		$(COREDIR)/hash.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/init.o $(COREDIR)/init.cpp

$(COREOBJDIR)/move.o: $(COREDIR)/move.cpp $(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h \
		$(COREDIR)/action.h \
		$(COREDIR)/board.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/move.o $(COREDIR)/move.cpp

$(COREOBJDIR)/play.o: $(COREDIR)/play.cpp $(COREDIR)/play.h \
		$(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h \
		$(COREDIR)/search.h \
		$(COREDIR)/action.h \
		$(COREDIR)/init.h \
		$(COREDIR)/parse.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/play.o $(COREDIR)/play.cpp

$(COREOBJDIR)/search.o: $(COREDIR)/search.cpp $(COREDIR)/search.h \
		$(COREDIR)/board.h \
		$(COREDIR)/move.h \
		$(COREDIR)/typedefs.h \
		$(COREDIR)/twiddle.h \
		$(COREDIR)/action.h \
		$(COREDIR)/play.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $(COREOBJDIR)/search.o $(COREDIR)/search.cpp
