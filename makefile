a.out: main.o word.o integer.o
	g++ main.o word.o integer.o -o a.out

main.o: main.cpp
	g++ -c main.cpp

word.o: src/word.cpp
	g++ -c src/word.cpp

integer.o: src/integer.cpp
	g++ -c src/integer.cpp

clean:
	rm *.o a.out