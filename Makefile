run: build
	./OurTerminal.exe

buildDebug: src/main.cpp
	g++ -std=c++17 -g src/main.cpp -pthread -o OurTerminal.exe

OurTerminal.exe: 
	build

build: src/main.cpp
	g++ -std=c++17 src/main.cpp -pthread -o OurTerminal.exe

clean: OurTerminal.exe
	rm OurTerminal.exe

debug: buildDebug
	gdb OurTerminal.exe