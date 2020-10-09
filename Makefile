run: build
	./OurTerminal.exe

OurTerminal.exe: 
	build

build: src/main.cpp
	g++ -std=c++17 src/main.cpp -pthread -o OurTerminal.exe

clean:
	rm OurTerminal.exe

debug: build
	gdb OurTerminal.exe