#include <thread>
#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::thread;
using std::vector;

void greet(int id)
{
    cout << "Hello there! My name is " << id << endl;
}

void useThread()
{
    cout << "Hello there! My name is " << __func__ << endl;
    std::thread thread1(greet, 1);
    std::thread thread2(greet, 2);
}

void useJoin()
{
    cout << "Hello there! My name is " << __func__ << endl;
    std::thread thread1(greet, 1);
    std::thread thread2(greet, 2);
    thread1.join();
    thread2.join();
}

std::mutex mtx;

void greetMtx(int id)
{
    std::lock_guard<std::mutex> lg(mtx);
    cout << "Hello there! My name is " << id << endl;
}

void useMutex()
{
    cout << "Hello there! My name is " << __func__ << endl;
    vector<thread> threads;
    for (int i = 0; i < 10; i++)
        threads.push_back(std::thread(greetMtx, i));

    for (auto &t : threads)
        t.join();
}

int main(int argc, char *argv[])
{
    // useThread();
    // useJoin();
    useMutex();
    return 0;
}