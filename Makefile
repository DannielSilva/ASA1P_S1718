all: comp run

comp: main.cpp
	g++ -std=c++11 -o proj main.cpp

run: proj
	./proj

clean:
	rm proj
