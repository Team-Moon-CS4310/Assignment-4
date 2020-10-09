#include "commands.hpp"

std::string *separate(const std::string &input);

int main(int argc, char const *argv[]) {
	directory = std::filesystem::current_path();

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
			cout << "Goodbye!\n";
			return;
		} else {
			cout << args[0] << ": command not foud\n";
		}

		cout << directory << ">";  // Print the current path. Similar to windows cmd.

		// this_thread::yield();
	}
}

std::string *separate(const std::string &input) {
	int index = 0;
	std::string *t = new std::string[3];
	std::regex reg("(\\S+)");

	// Thankyou https://www.regular-expressions.info/stdregex.html
	std::sregex_iterator next(input.begin(), input.end(), reg);
	std::sregex_iterator end;

	for (smatch mat = *next; next != end; mat = *next) {
		t[index] = mat.str();
		index++;
		next++;
	}

	return t;
}
