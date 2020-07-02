build:
	g++ src/main.cpp -o executable

dev:
	g++ src/dev.cpp -o dev.out && ./dev.out
