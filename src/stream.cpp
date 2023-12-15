#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

void streamBasics();
int stringToInteger(const string &s);
int stringToIntegerTest();
void cinBad();
void cinGood();
int getInteger(const string &prompt, const string &reprompt);
void printStateBits(const istringstream &iss);
void bufferExperiment(ostream &oss);
void mindlessWork();
int endlEachTime();
int endlAtEnd();
void manipulatorsExample();

int main(int argc, char *argv[])
{
    // streamBasics();

    // cinBad();
    cinGood();

    // stringToIntegerTest();

    // = cout has buffer, which prints when meeting endl
    // bufferExperiment(cout);
    // = cerr has no buffer, which prints when something dumped into it
    // bufferExperiment(cerr);

    // = flush the buffer is expensive, when triggers when using endl
    // int a = endlEachTime();
    // int b = endlAtEnd();
    // cout << "endl each time: " << a << endl;
    // cout << "endl at end: " << b << endl;

    // use stream manipulators
    // manipulatorsExample();
    return 0;
}

void streamBasics()
{
    // output stringstream
    ostringstream oss("Ito-En Green Tea ");
    // print on cout, must use str so the cout prints string instead of ostringstream
    cout << oss.str() << endl;
    // output to ostringstream
    oss << 16.9 << " Ounces ";
    cout << oss.str() << endl; // = ostrigstream pointer always points to the start, so it will overwrite

    // = unless we set ate (at the end) flag
    ostringstream oss_ate("Ito-En Green Tea ", stringstream::ate);
    oss_ate << 16.9 << " Ounces ";
    cout << oss_ate.str() << endl;

    oss_ate << "(Pack of " << 12 << ")";
    cout << oss_ate.str() << endl;

    // input stringstream
    istringstream iss("16.9 Ounces");
    double amount;
    string unit;
    iss >> amount;
    iss >> unit;
    cout << amount / 2 << ' ' << unit << endl;
}

int stringToInteger(const string &s)
{
    istringstream iss(s);
    // printStateBits(iss);
    // int result;
    // iss >> result;
    // printStateBits(iss);

    // Safer one, for it will check the status
    // make sure it read a integer
    // int result;
    // char ch;
    // if (iss.fail()) throw std::domain_error("No value int at the beginning");
    // char ch;
    // iss >> ch;
    // if (!iss.fail()) throw std::domain_error("More than a single value");
    // same as !fail
    // if (iss.eof()) throw std::domain_error("More than a single value");

    // result of iss >> result will turn to boolean, so we can use code as
    // int result;
    // char remain;
    // if (!(iss >> result))
    //     throw std::domain_error("No value int at the beginning");
    // if (iss >> remain)
    //     throw std::domain_error("More than a single value");

    // A fancier way
    int result;
    char remain;
    if (!(iss >> result) || iss >> remain)
        throw std::domain_error("Get a int failed!");
    return result;
}

int stringToIntegerTest()
{
    while (true)
    {
        cout << "Type an integer: ";
        string s;
        if (!getline(cin, s))
            throw std::domain_error("getline failed!");
        cout << "You typed in: " << s << endl;
        int result = stringToInteger(s);
        cout << "As an integer, this is: " << result << endl;
        cout << "Half of that is: " << result / 2 << endl;
    }
}

void cinBad()
{
    cout << "What's your name? ";
    string name;
    cin >> name;
    cout << (cin.good() ? 'G' : '-')
         << (cin.fail() ? 'F' : '-')
         << (cin.eof() ? 'E' : '-')
         << (cin.bad() ? 'B' : '-')
         << endl;

    cout << "What's your age? ";
    int age;
    cin >> age;
    cout << (cin.good() ? 'G' : '-')
         << (cin.fail() ? 'F' : '-')
         << (cin.eof() ? 'E' : '-')
         << (cin.bad() ? 'B' : '-')
         << endl;

    cout << "What're you from? ";
    string home;
    cin >> home;
    cout << (cin.good() ? 'G' : '-')
         << (cin.fail() ? 'F' : '-')
         << (cin.eof() ? 'E' : '-')
         << (cin.bad() ? 'B' : '-')
         << endl;

    cout << "Hello " << name << "(age " << age << " from " << home << ")" << endl;
}

void cinGood()
{
    cout << "What's your name? ";
    string name;
    getline(cin, name, '\n');
    // cin.get();

    // cout << "What's your age? ";
    // int age;
    // cin >> age;
    int age = getInteger("What's your age? "s, "Wrong, try again"s);

    cout << "What're you from? ";
    string home;
    // cin >> home;
    // cin >> will leave the '\n', so just ignore the next \n
    cin.ignore();
    getline(cin, home);

    cout << "Hello " << name << "(age " << age << " from " << home << ")" << endl;
}

int getInteger(const string &prompt, const string &reprompt)
{
    while (true)
    {
        cout << prompt;
        string line;
        if (!getline(cin, line))
            throw std::domain_error("...");
        int val;
        char remain;
        istringstream iss(line);
        if (iss >> val && !(iss >> remain))
            return val;
        cout << reprompt << endl;
    }
}

void printStateBits(const istringstream &iss)
{
    cout << (iss.good() ? "G" : "-");
    cout << (iss.fail() ? "F" : "-");
    cout << (iss.eof() ? "E" : "-");
    cout << (iss.bad() ? "B" : "-");
    cout << endl;
}

void bufferExperiment(ostream &oss)
{
    oss << "CS";
    mindlessWork();

    oss << "106";
    mindlessWork();

    oss << "L";
    mindlessWork();

    oss << endl;
    mindlessWork();
}

void mindlessWork() {}

int endlEachTime()
{
    auto startMove = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
        cout << i << endl;
    auto stopMove = std::chrono::high_resolution_clock::now();
    auto moveDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopMove - startMove);
    return moveDuration.count();
}

int endlAtEnd()
{
    auto startMove = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; i++)
        cout << i << '\n';
    cout << flush;
    auto stopMove = std::chrono::high_resolution_clock::now();
    auto moveDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopMove - startMove);
    return moveDuration.count();
}

void manipulatorsExample()
{
    cout << "[" << setw(10) << "Ito"
         << "]" << endl;
    cout << "[" << left << setw(10) << "Ito"
         << "]" << endl;
    cout << "[" << left << setfill('-') << setw(10) << "Ito"
         << "]" << endl;
}