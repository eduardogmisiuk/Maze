EXEC=build/main
SRC=src/*.cc
INC=-I./header
EXECARG=
CPPFLAGS=-Wall -std=c++11 -g

all: compile

nocolors: CPPFLAGS += -DNO_COLORS
nocolors: all

clean:
		find -name "*~" -exec rm -rf {} \;
		rm -rf $(EXEC)

compile:
		g++ -o $(EXEC) $(SRC) $(INC) $(CPPFLAGS)

run:
		./$(EXEC) $(EXECARG)

.PHONY: all clean compile run
