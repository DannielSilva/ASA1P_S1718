all: comp run

comp: main.cpp
	g++ -std=c++11 -o proj main.cpp

run: proj
	./proj

clean:
	rm proj

test1: comp input1.txt
	./proj < input1.txt

test2: comp input2.txt
	./proj < input2.txt

test3: comp input3.txt
	./proj < input3.txt
