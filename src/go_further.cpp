#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

using std::cout;
using std::endl;
using std::pair;
using std::string;
using std::vector;

int main(int argc, char *argv[])
{
    cout << "Where to go?" << endl;
    cout << "Use C++! " << endl;
    cout << "Talk to / encourage each other!" << endl;
    cout << "Let us know what kind of awesome projects you make in the future!" << endl;
    cout << "Further C++ reading:" << endl;

    vector<pair<string, string>> readings{
        {"Accelerated C++", "Andrew Koenig"},
        {"Effective C++", "Scott Meyers"},
        {"Effective Modern C++", "Scott Meyers"},
        {"Exceptinal C++", "Hurb Shutter"},
        {"Modern C++ Design", "Andrei Alexandrescu"},
    };

    for (pair<string, string> &p : readings)
        cout << std::setw(30) << std::right << p.first << "   " << p.second << endl;

    return 0;
}