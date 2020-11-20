
main: main.cpp
	g++ -o main -g3 -Wall -I. main.cpp

run: main
	main

input: main
	main < input

valgrind: main
	valgrind main


gen: gen.cpp
	g++ -o gen -Ofast -Wall -I. gen.cpp





# end
