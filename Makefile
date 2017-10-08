EXEC=build/main
SRC=src/*.cc
INC=-I./header
EXECARG=
CPPFLAGS=-Wall -std=c++11 -g

all: clean compile

clean:
		find -name "*~" -exec rm -rf {} \;

compile:
		g++ -o $(EXEC) $(SRC) $(INC) $(CPPFLAGS)

run:
		./$(EXEC) $(EXECARG)

.PHONY: all clean compile run
