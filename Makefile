# Usage:
# $ make			# compile all binary
# $ make clean		# remove all binaries and objects

# -I include path
# -L library path
# -l link with library
# -o name of the output file
# -c output a .o file (when compiling sources)

CXX = g++			# C++ compiler
CC = gcc			# C compiler
CFLAGS = -g -Wall

RM = rm -rf

#LIBDIR = 
LIBS = 

INCDIR =

SRCDIR = ./
OBJDIR = ./
EXEDIR = ./

SRCS = $(wildcard $(SRCDIR)*.c)
OBJS = $(subst .c,.o, $(subst $(SRCDIR),$(OBJDIR), $(SRCS)))
EXEC = $(EXEDIR)main.exe

.DELETE_ON_ERROR:
all: compile launch
.PHONY: all clean

compile: $(EXEC)
	
$(EXEC): $(OBJS)
ifeq ($(LIBS),)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)
else
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LIBDIR) $(LIBS)
endif

$(OBJDIR)%.o: $(SRCDIR)%.cpp
ifeq ($(INCDIR),)
	$(CC) $(CFLAGS) -c -o $@ $<
else
	$(CC) $(CFLAGS) -c -o $@ $< $(INCDIR)
endif

launch:
	$(EXEC)

clean:
	$(RM) $(OBJS) $(EXEC)

describe:
	@echo $(SRCS)
	@echo $(OBJS)
