debug: OurTerminal.exe
	gdb OurTerminal.exe

OurTerminal.exe: 
	build

run: OurTerminal.exe
	./OurTerminal.exe

build: src/main.cpp
	c++ src/main.cpp -pthread -o OurTerminal.exe

clean: OurTerminal.exe
	rm OurTerminal.exe