#include <map>
#include <string>
#include <vector>
#include <thread>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Employee
{
private:
    int _idNumber;
    string _first;
    string _last;
    string _title;
    double _salary;

public:
    Employee(int idNumber)
        : _idNumber(idNumber) {}
    Employee(int idNumber, string first, string last, string title, double salary)
        : _idNumber(idNumber), _first(first), _last(last), _title(title), _salary(salary){};
    ~Employee() = default;

    string &First() { return _first; }
    string &Last() { return _last; }
    string &Title() { return _title; }
    double Salary() { return _salary; }
};

// This function below, has 23 possible pathes
// if nothing wrong, there are 3 possible pathes
// but if something wrong, there will be a way to exit before return
// * That is exception!
// So, the total pathes are:
//      1: Copy constructor of Employee paramter, may throw
//      2: Constructor of temp string/ints, may throw
//      6: call to Title, Salary, First(2), Last(2), may throw
//      10: Operators may be user-overloaded, may throw
//      1: Copy constructor of string or return value, may throw
string evaluateSalaryAndReturnName(Employee &e)
{
    if (e.Title() == "CEO" || e.Salary() > 100000)
    {
        cout << e.First() << " " << e.Last() << " is overpaid" << endl;
    }

    return e.First() + " " + e.Last();
}

// This code has severe memory leak problem
// Because when using new, we allocate memory in heap
// And after the new, we can use the memory to store our objects
// Until delete, we free the allocated heap memory
// * But, what if the code went to exception before delete?
// when encountered an exception, the funtion exits and go to catch stattment
// so, the pointer pointing to the allocated memory in the function is released
// = The result is, we can never access the allocated heap memeory again
// = neither release the heap memory by delete
string evalueateSalaryAndReturnName(int idNumber)
{
    Employee *e = new Employee(idNumber);
    if (e->Title() == "CEO" || e->Salary() > 100000)
    {
        cout << e->First() << " " << e->Last() << " is overpaied " << endl;
    }
    auto result = e->First() + " " + e->Last();
    delete e;
    return result;
}

// = a more general concern is resources that need to be release
//                      Acquire         Release
// Heap memory          new             delete
// Files                open            close
// Locks                try_lock        unlock
// Sockets              socket          close

// In object-oriented programming, object safty is extremely important in
// Functions can have four levels of exception safety:
// • Nothrow exception guarantee
//      • absolutely does not throw exceptions: destructors, swaps, move constructors, etc.
// • Strong exception guarantee
//      • rolled back to the state before function call
// • Basic exception guarantee
//      • program is in valid state after exception
// • No exception guarantee
//      • resource leaks, memory corruption, bad...
// * We can explicitly declare that a function's is nothrow exception
void testNothrowException() noexcept {}
// * For others, there is no key word, we have to design the code carefully

// = Go back to memory leak, or resource holding
// * To solve this problem, the inventor of C++ come up with RAII
// * Which means, Require Acquisition In Instantiation
// * This is not a good name, the better name of the same concept are:
// *        SBRM: Scope Based Memory Management
// *        CADRE: Constructor Acquires, Destructor Releases

// * The key idea of RAII is when object is created, the constructor is called
// * and when object is deleted, the destructor is called.
// = So, we should always put the resource acquisition code in the constructor
// = and resource releasing code in the destructor
// = because destructor are always called when the scope ends

// * Based on the idea of RAII, this function is not RAII compliant
void printFile()
{
    std::fstream input;
    input.open("hamlet.txt");
    string line;
    while (std::getline(input, line))
    {
        cout << line << endl;
    }
    input.close();
}

// * but this function is RAII compliant
void printFileRAII()
{
    std::fstream input("hamlet.txt");
    string line;
    while (std::getline(input, line))
    {
        cout << line << endl;
    }
}

// * Similarly, for lock, this is not RAII compliant
void cleanDatabase(std::mutex &databaseLock, std::map<int, int> &database)
{
    databaseLock.lock();
    // other code
    // ...
    // ...
    databaseLock.unlock();
}

// * to fix that, we just need to use a object to wrap that up
void cleanDatabaseRAII(std::mutex &databaseLock, std::map<int, int> &database)
{
    std::lock_guard<std::mutex> lock(databaseLock);

    // other codes
    // ...
    // ...
}

// Here is a simplified version (without template) of lock_guard
class lock_guard
{
private:
    std::mutex &acquiredLock;

public:
    // mutex cannot be copied, that's why we have to use initialization list
    // there is a snippet of mutex implementation
    // class mutex
    // {
    // public:
    //     mutex(const mutex &other) = delete;
    //     mutex &operator=(const mutex &rhs) = delete;
    //     mutex(mutex &&other) = delete;
    //     mutex &operator=(mutex &&other) = delete;
    // };
    lock_guard(std::mutex &lock) : acquiredLock(lock)
    {
        acquiredLock.lock();
    }
    ~lock_guard()
    {
        acquiredLock.unlock();
    }
};

// * In modern C++, we should avoid calling new and delete explicity
// * just wrap them in the class

int main(int argc, char *argv[])
{
    return 0;
}