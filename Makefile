PROJECT = shader 

SHELL = /bin/bash

CC = g++ 

FLAGS = -std=c++11 -Wall 
#-Weffc++ 
CFLAGS = -c
LDFLAGS = $(GL_OPTS) $(SFML_OPTS)

TARGET = $(PROJECT)

SRCDIR = ./
BINDIR = ./

SOURCES = $(shell echo $(SRCDIR)/shader.cpp)
OBJECTS = $(shell echo $(SOURCES) | sed 's/\.cpp/\.o/g')

GL_OPTS = -lGL -lGLU -lGLEW 
SFML_OPTS = -lsfml-window -lsfml-system -lsfml-graphics

all: $(TARGET)
	@echo 'Building $(TARGET)'

$(TARGET): $(OBJECTS)
	$(CC) $(FLAGS) $(LDFLAGS) -o $(BINDIR)/$(TARGET) $(OBJECTS)

$(BINDIR)/shadero: $(SRCDIR)/shader.cpp
	$(CC) $(FLAGS) $(CFLAGS) $(SRCDIR)/shader.cpp -o $(BINDIR)/shader.o

clean: 
	@echo 'Cleaning up...'
	rm $(BINDIR)/shader
	rm $(BINDIR)/*.o
