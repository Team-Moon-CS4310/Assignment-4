#include "commands.hpp"
using namespace std;

void cd(string newDestination) {
	cout << "cdtest\n";
}

void pwd() {
	cout << directory << "\n";
}

void ls() {
	for (std::filesystem::directory_entry p : std::filesystem::directory_iterator(directory)) {
		cout << p.path().filename().generic_string() << "\n";
	}
}