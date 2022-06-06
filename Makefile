all:
	make clean
	make run

run:
	make build && ./main

clean:
	rm -rf main

build:
	g++ c++fire.cpp auth.cpp handler.cpp networking.cpp -ljsoncpp -o main

gdb:
	g++ c++fire.cpp auth.cpp handler.cpp networking.cpp -ljsoncpp -g -o main
