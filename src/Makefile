objects=seperator.o ullman_init.o ullman_utils.o main.o ullman_query.o\
	   	ullman_build.o graph.o\

all : ullman

CXXFLAGS= -g -O2

ullman : $(objects)
	g++ -o ullman -g $(objects) -O2

seperator.o : seperator.h
graph.o : graph.h
ullman_build.o : ullman.h
ullman_utils.o : ullman_utils.h
ullman_init.o : ullman.h
ullman_query.o : ullman.h
main.o : common.h ullman.h ullman_utils.h

.PHONY : clean all

clean :
	rm -rf $(objects) ullman
