run: main.o
	g++ main.o -o run
main.o : main.cpp edge_detect.h
	g++ -c -DDEBUG main.cpp -o main.o
