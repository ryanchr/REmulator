TARGET_ARCH = linux
CC     = g++
OPT    = #-O2 # -O3
DEBUG  = -g
OTHER  = -w # -Wall -Wno-deprecated
CFLAGS = $(OPT) $(OTHER)
SYSTEMC = /usr/local/systemc-2.2
INCDIR = -I$(SYSTEMC)/include\
		 		 -I./config\
		 		 -include/usr/include/errno.h
LIBDIR = -L$(SYSTEMC)/lib-$(TARGET_ARCH)
LIBS = -lsystemc

YACC    = bison
LEX     = flex
LIBLEX	= -lfl 

LDFLAGS = $(LIBLEX)

OBJDIR = $(shell pwd)/obj

APP=remulator

SRCS=./config/config.tab.c\
	./config/config.lex.c\
	./config/initializer.cpp\
	 alu.cpp\
	 config_rcore.cpp\
	 rca.cpp\
	 rcore.cpp\
	 topsystem.cpp\
	 tools.cpp\
	 jumpmodule.cpp\
	 main.cpp

OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all:$(OBJS)
	$(CC) -o $(APP) $(OBJS) $(LIBDIR) $(INCDIR) $(DEBUG) $(LIBS) $(CFLAGS) $(LDFLAGS) 
	
./config/config.lex.c: ./config/config.lex
	$(LEX) -o$@ $<

./config/config.tab.c: ./config/config.y
	$(YACC) -o$@ -d $<
	
%.o: %.cpp
	$(CC) -c $< $(INCDIR) $(CFLAGS) -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(APP)
	rm -rf $(OBJS)
	rm -f ./config/config.lex.c ./config/config.lex.h
	rm -f ./config/config.tab.c ./config/config.tab.h

