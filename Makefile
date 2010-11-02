# vim:noet

CC=g++
CFLAGS=-Wall -c
LDFLAGS=-L/usr/lib -lglut -lglui -lGLU -lGL
SOURCEDIR=.
OBJECTDIR=.
SOURCES:=$(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS=$(SOURCES:$(SOURCEDIR)%.cpp=$(OBJECTDIR)%.o)
SHELL = /bin/sh

.DEFAULT_GOAL := P4

P4: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf $(OBJECTS) P4
