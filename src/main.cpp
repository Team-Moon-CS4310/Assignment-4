#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <thread>
#include <fstream>
using namespace std;

void getInput();
void cd(string destination);
void ls();
void pwd();
void mkdir(string newDir);
void rmdir(string dir);
void cp(string first, string second);
void execute(string file);

string *separate(const string &input);

int main(int argc, char const *argv[]) {
	cout << "\033[34m" << filesystem::current_path() << "\033[0m>";	 // Print the current path. Similar to windows cmd.

	thread test(getInput);

	test.join();
	return 0;
}

void getInput() {
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
		} else if (filesystem::is_regular_file(args[0])) {
			execute(args[1]);
		}

		else {
			cout << args[0] << ": command not found\n";
		}
		cout << "\033[34m" << filesystem::current_path() << "\033[0m>";	 // Print the current path. Similar to windows cmd.
	}
}

string *separate(const string &input) {
	int index = 0;
	string *t = new string[3];
	regex reg("(\\S+)");

	// Thankyou https://www.regular-expressions.info/stdregex.html
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
		}
	}

	//Can set directory properly
	// Relative path = everything after the C:\
  // root path = rootname + rootdirectory, ex: C:\
  // root directory = \
  // root name = C: for example.
	// Stem = file w/o file extension.
	// filename == full filename with extension
	// Parent path = path 1 step above current, up until hit /
	// Extension = file extension only

	/* DEBUG TODO remove
	cout << directory.relative_path() << "\n";
	cout << directory.root_path() << "\n";
	cout << directory.root_directory() << "\n";
	cout << directory.root_name() << "\n";
	cout << directory.stem() << "\n";
	cout << directory.filename() << "\n";
	cout << directory.parent_path() << "\n";
	cout << directory.extension() << "\n";
  */
}

void pwd() {
	cout << filesystem::current_path() << "\n";
}

void ls() {
	int col = 0;
	for (filesystem::directory_entry p : filesystem::directory_iterator(filesystem::current_path())) {
		// colum size of 5.
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
	//filesystem::create_directory("testDir");
	//ofstream("testDir/file.txt").put('a');
	
	const auto options = filesystem::copy_options::overwrite_existing;
	filesystem::copy(first, second, options);
}

void execute(string file){

}