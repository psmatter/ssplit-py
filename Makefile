#Makefile for ssplit python api.
# 
#
# The directly bound sources
APISRC = src/ssplit_py_api.cpp
APIOBJ = obj/ssplit_py_api.o

# The path to the header file. 
# Include path for Python headers
PYTHON_INCLUDES := $(shell python3-config --includes)
INCLUDE_PATH = $(SRCDIR)/ $(PYTHON_INCLUDES)

# The library sources 
SRC = regex.cpp ssplit.cpp 

SRCDIR = ./src
OBJDIR = ./obj
LIBDIR = ./lib

OBJECTS = $(foreach sf,$(SRC),$(OBJDIR)/$(sf:.cpp=.o))

#local lib
APILIB = $(LIBDIR)/splitter.so

# The C compiler to use.
CC = g++
AR = ar

DBG= nm -gDC
# The C compiler flags to use.
CF = -Wall -std=c++17 
SH = -fpic
LD = -shared 
AR = rvs
EX = -Wl,-rpath,$(LIBDIR)/ -pthread


# The library flags to link against the Splitter library.
LIBS = -lpcre2-8 $(shell python3-config --libs)


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/%.h   
	$(CC) $(CF) $(SH) -I$(INCLUDE_PATH) -c $<  -o $@

$(APILIB): $(APISRC) $(OBJECTS)
	$(CC) $(CF) $(SH) $(LD) $(EX) \
                   -I$(INCLUDE_PATH) -L$(LIBDIR)\
                    $(APISRC) -o $(APILIB)\
                    $(OBJECTS) $(LIBS)


pymodule: $(APILIB)

# The clean target.
.PHONY: clean

clean:
	rm -f $(APILIB)
	rm -f $(OBJDIR)/*


