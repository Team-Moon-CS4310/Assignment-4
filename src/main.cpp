#include <iostream>
#include <string>
#include <thread>
#include <regex>

using namespace std;

std::string *separate(const std::string &input)
{
    int index = 0;
    std::string *t = new std::string[3];
    std::regex reg("(\\S+)");

    // Thankyou https://www.regular-expressions.info/stdregex.html
    std::sregex_iterator next(input.begin(), input.end(), reg);
    std::sregex_iterator end;

    for (smatch mat = *next; next != end; mat = *next)
    {
        t[index] = mat.str();
        index++;
        next++;
    }

    return t;
}

void getInput();

int main(int argc, char const *argv[])
{
    //TODO what to do when input is very long or too many args?
    thread test(getInput);

    test.join();

    return 0;
}

void getInput()
{
    while (true)
    {
        string input;
        getline(cin, input, '\n');

        string *args = separate(input);

        if (args[0] == "cd")
        {
            cout << "cdtest";
        }
        else if (args[0] == "pwd")
        {
        }
        else if (args[0] == "exit")
        {
            cout << "Goodbye!";
            return;
        }

        //this_thread::yield();
    }
}
