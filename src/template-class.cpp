#include <string>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Template and inheritence are two way to achieve polymorphic
// Template is more about compile time, which mean the compiler generate
// a set of functions
// While inheritence is more about runtime, that the code
// runs a set of function

// What template do is during compilation, the compiler automatically
// generate code for us

// So, except template function which let the compiler generate
// functions, we can also use template class, which let the compiler
// generate class for us during compiling

// in template, class and typename are most the same
// except that we want to declare that we need a self-defined class
// to instantiate the template

// we can also use = to set the default instantiate method

template <class T, class Container = std::vector<T>>
class Priority_Q
{
private:
    size_t _count{0};
    Container _heap;

public:
    Priority_Q() = default;
    ~Priority_Q() = default;

    T top() const
    {
        if (_heap.empty())
            return {};
        return _heap[0];
    }

    T pop()
    {
        if (!_heap.empty())
        {
            std::pop_heap(_heap.begin(), _heap.end());
            _heap.pop_back();
            _count--;
        }
    }

    void push(T val)
    {
        _heap.push_back(val);
        std::push_heap(_heap.begin(), _heap.end());
        _count++;
    }

    friend std::ostream &operator<<(std::ostream &os, const Priority_Q &pq)
    {
        os << "{";
        for (size_t i = 0; i < pq._count; i++)
        {
            if (i > 0)
                os << ", ";
            os << pq._heap[i];
        }
        return os << "}";
    }
};

int main(int argc, char *argv[])
{
    Priority_Q<int> intQueue;
    intQueue.push(5);
    intQueue.push(3);
    intQueue.push(7);

    cout << intQueue << endl;

    Priority_Q<char> charQueue;
    charQueue.push('a');
    charQueue.push('v');
    charQueue.push('l');

    cout << charQueue << endl;
    return 0;
}