#############################################################################
# Makefile for building: enumerate_example
#############################################################################

MAKEFILE      = Makefile

####### Compiler, tools and options

CXX           = clang++
DEFINES       =
CXXFLAGS      = -g -std=c++1z -Wall -W -fPIC $(DEFINES)
INCPATH       = -I.
DEL_FILE      = rm -f
LINK          = clang++
LFLAGS        = 

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = enumerate_example.cpp
OBJECTS       = enumerate_example.o
DIST          = ../include/enumerate.h $(SOURCES)
DESTDIR       = 
TARGET        = enumerate_example


####### Build rules
first: all

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS)

all: $(TARGET)

clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core

####### Compile

enumerate_example.o: ../example/enumerate_example.cpp ../include/enumerate.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o enumerate_example.o ../example/enumerate_example.cpp
