#include <sys/wait.h>
#include <unistd.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <thread>
using namespace std;

void getInput();
void cd(string destination);
void pwd();
void mkdir(string newDir);
void rmdir(string dir);
void ls();
void cp(string first, string second);
void execute(string file);
bool checkFile(string file);

string *separate(const string &input);

int main(int argc, char const *argv[]) {
	getInput();
	return 0;
}

void getInput() {
	cout << "\033[34m" << filesystem::current_path().c_str() << "\033[0m>";	 // Print the current path. Similar to windows cmd.
	while (true) {
		string input;
		// TODO what to do when input is very long or too many args?
		getline(cin, input, '\n');

		string *args = separate(input);

		// TODO implement
		if (args[0] == "cd") {
			cd(args[1]);
		} else if (args[0] == "pwd") {
			pwd();
		} else if (args[0] == "ls") {
			ls();
		} else if (args[0] == "exit") {
			cout << "Arrivederci!\n";
			return;
		} else if (args[0] == "mkdir") {
			mkdir(args[1]);
		} else if (args[0] == "rmdir") {
			rmdir(args[1]);
		} else if (args[0] == "cp") {
			cp(args[1], args[2]);
		} else if (checkFile(args[0])) {
			if (filesystem::is_regular_file(args[0]) && filesystem::exists(args[0])) {
				execute(args[0]);
			} else {
				cout << "File: \'" << args[0].substr(2, args[0].length()) << "\' does not exist.\n";
			}
		} else if (args->empty()) {
		} else {
			cout << args[0] << ": command not found\n";
		}
		cout << "\033[34m" << filesystem::current_path().c_str() << "\033[0m>";	 // Print the current path. Similar to windows cmd.
	}
}

string *separate(const string &input) {
	int index = 0;
	string *t = new string[3];
	regex reg("(\\S+)");

	sregex_iterator next(input.begin(), input.end(), reg);
	sregex_iterator end;

	for (smatch mat = *next; next != end; mat = *next) {
		t[index] = mat.str();
		index++;
		next++;
	}

	return t;
}

void cd(string newDestination) {
	if (newDestination == "") {
		filesystem::current_path(filesystem::current_path().root_path());
	} else {
		if (filesystem::is_directory(newDestination)) {
			filesystem::current_path(newDestination);
		} else {
			cout << "cd: " << newDestination << ": No such file or directory\n";
		}
	}
}

void pwd() {
	cout << filesystem::current_path() << "\n";
}

void ls() {
	int col = 0;
	for (filesystem::directory_entry p : filesystem::directory_iterator(filesystem::current_path())) {
		// column size of 5.
		if (col == 5) {
			cout << "\n";
			col = 0;
		}
		if (filesystem::is_directory(p.path())) {
			cout << "\033[44;1;30m" << p.path().filename().generic_string() << "\033[0m ";
		} else {
			cout << p.path().filename().generic_string() << " ";
		}
		col++;
	}
	cout << "\n";
}

void mkdir(string newDir) {
	// Check if directory / file with name "newDir" exists
	// If exists, error
	// If does not exist, create directory

	bool directoryExists = false;

	for (filesystem::directory_entry p : filesystem::directory_iterator(filesystem::current_path())) {
		if (p.path().filename() == newDir) {
			directoryExists = true;
		}
	}

	if (directoryExists) {
		cout << "mkdir: cannot create directory \'" << newDir << "\': File exists\n";
	} else if (!directoryExists) {
		filesystem::path directory(newDir);
		filesystem::path newDirectoryPath = filesystem::current_path() / directory;
		filesystem::create_directory(newDirectoryPath);
	}
}

void rmdir(string dir) {
	// Check if directory with name "dir" exists
	// If exists, remove
	// If does not exist, error

	bool directoryExists = false;

	for (filesystem::directory_entry p : filesystem::directory_iterator(filesystem::current_path())) {
		if (filesystem::is_directory(p.path()) && p.path().filename() == dir) {
			directoryExists = true;
		}
	}

	if (directoryExists) {
		filesystem::path directory(dir);
		filesystem::path directoryPathToBeRemoved = filesystem::current_path() / directory;
		filesystem::remove(directoryPathToBeRemoved);
	} else if (!directoryExists) {
		cout << "rmdir: cannot remove \'" << dir << "\': No such directory\n";
	}
}

void cp(string first, string second) {
	bool doesExist = false;

	for (filesystem::directory_entry p : filesystem::directory_iterator(filesystem::current_path())) {
		if (filesystem::exists(first)) {
			doesExist = true;
		}
	}

	if (doesExist) {
		const auto options = filesystem::copy_options::overwrite_existing;
		filesystem::copy(first, second);
	} else {
		cout << "cp: cannot copy \'" << first << "\': Given file or directory not found\n";
	}
}

void execute(string file) {
	pid_t p;
	p = fork();
	wait(NULL);

	if (p == -1) {
		cout << "Error calling fork()\n";
	}

	if (p == 0) {
		const char *args[] = {NULL};
		execv(file.c_str(), (char *const *)args);
	}
}

bool checkFile(string file) {
	if (file[0] == '.' && file[1] == '/') {
		return true;
	}
	return false;
}