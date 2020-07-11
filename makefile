build:
	g++ src/main.cpp -std=c++11 -o executable

dev:
	g++ src/dev.cpp -std=c++11 -o dev.out && ./dev.out
