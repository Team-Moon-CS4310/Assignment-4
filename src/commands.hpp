#include <filesystem>
#include <iostream>
#include <regex>
#include <string>
#include <thread>
using namespace std;
static string directory;

void getInput();
void cd(string destination);
void ls();
void pwd();