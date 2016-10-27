TARGET_ARCH = linux
CC     = g++
OPT    = #-O2 # -O3
DEBUG  = -g
OTHER  = -w # -Wall -Wno-deprecated
CFLAGS = $(OPT) $(OTHER)
SYSTEMC = /usr/local/systemc-2.2
INCDIR = -I$(SYSTEMC)/include\
				-include/usr/include/errno.h
LIBDIR = -L$(SYSTEMC)/lib-$(TARGET_ARCH)
LIBS = -lsystemc

YACC    = bison
LEX     = flex
LIBLEX	= -lfl 

LDFLAGS= $(LIBLEX)

OBJDIR = $(shell pwd)/obj

APP=./test

SRCS=main.cpp\
	./config.tab.c\
	./config.lex.c\
	./initializer.cpp\
	./config_rcore.cpp

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all:$(OBJS)
	$(CC) -o $(APP) $(OBJS) $(LIBDIR) $(INCDIR) $(LIBS) $(CFLAGS) $(LDFLAGS)
	
./config.lex.c: ./config.lex
	$(LEX) -o$@ $<

./config.tab.c: ./config.y
	$(YACC) -o$@ -d $<
	
%.o: %.cpp
	$(CC) -c $< $(INCDIR) $(CFLAGS) -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJS)
	rm -f ./config.lex.c ./config.lex.h
	rm -f ./config.tab.c ./config.tab.h
