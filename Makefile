all: comp run

comp: main.cpp
	g++ -o proj main.cpp

run: proj
	./proj

clean:
	rm proj
