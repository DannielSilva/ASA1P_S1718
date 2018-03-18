testpath=./Testes
all: comp run

comp: main.cpp
	g++ -std=c++11 -O3 -Wall -o proj main.cpp -lm

run: proj
	./proj

clean:
	rm proj

test1: comp
	./proj < ${testpath}/input1.txt

test2: comp
	./proj < ${testpath}/input2.txt

test3: comp
	./proj < ${testpath}/input3.txt
