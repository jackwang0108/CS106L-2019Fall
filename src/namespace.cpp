#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace Lecture
{
    template <typename T>
    size_t count(const vector<T> &vec, T val)
    {
        size_t num = 0;
        for (auto i : vec)
            if (i == val)
                num++;
        return num;
    }
}

void useLecture()
{
    vector<int> v{3, 1, 4, 1, 5, 9};
    cout << "Lecture count: " << Lecture::count(v, 1) << endl;
}

int main(int argc, char *argv[])
{
    useLecture();
    return 0;
}