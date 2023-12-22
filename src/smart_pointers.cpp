#include <string>
#include <vector>
#include <memory>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Last lecture we talked about RAII. We first introduced memory leak by new and delete
// and more general, the problem is about resources acquisition and releasing
// To deal with that, we can use a object to warpper the acquisition in initializing
// and releasing in destructor

// then, we said that we should avoid using pointer explicitly in modern C++
// because the pointer may hold the resources and not releasing if exception went

// But what if we warp the pointer in a class?
// Then the shortcoming of pointer is fixed.
// * That's the idea of smart pointer

// * Smart pointers are RAII compliant pointers
// * STL provide us 3 smart pointer, while in other library
// * like boost, also have other type of smart pointer
// std::unique_ptr;
// std::shared_ptr;
// std::weak_ptr;
// boost:scoped_ptr;
// boost::intrusive_ptr;

struct Node
{
    int x;
    int y;
};

std::ostream &operator<<(std::ostream &os, const Node &n)
{
    os << "Node (x=" << n.x << ", y=" << n.y << ")" << endl;
    return os;
}

// unique_ptr uniquely owns its resource and deletes it when the object is destroyed.
// and cannot be copied (but can be moved, if non-const)!
// if unique_ptr allows copy, the the memory will be free twice!
void useUniquePtr()
{
    std::unique_ptr<Node> n(new Node);
    n->x = 1;
    n->y = 2;
    cout << *n;
}

// What if we want to have multiple pointers to the same object
// There is shared_ptr, shared_ptr has a counter inside
// every time the shared_ptr is copied, the counter plus one
// and when destructor is called, the counter minus one
// So, only the counter equals zero, which means after all pointers
// pointing to the object is destructed the memory is freed
void useSharedPtr()
{
    std::shared_ptr<Node> n1(new Node);
    n1->x = 1;
    n1->y = 2;
    cout << *n1;
    // in a new scope
    if (true)
    {
        std::shared_ptr<Node> n2 = n1;
        cout << *n2;
    }
}

// Similar to shared_ptr, but weak_ptr doesn’t contribute to the reference count.
// weak_ptr is used to deal with smart pointer recurrent problem
// for example. if we have class A, with a member shared_ptr points to B
// and in class B, a member shared_ptr points to A
// and the code below
// int main() {
//     {
//         std::shared_ptr<A> a = std::make_shared<A>();
//         std::shared_ptr<B> b = std::make_shared<B>();
//         a->b_ptr = b;
//         b->a_ptr = a;
//     }  // a and b will not be deleted since there is something else still
//           referencing the object
// }
// to deal with that, we use weak_ptr

class B; // 前向声明

class A
{
public:
    std::shared_ptr<B> b_ptr;
    ~A() { std::cout << "A deleted\n"; }
};

class B
{
public:
    // std::shared_ptr<A> a_ptr;
    std::weak_ptr<A> a_ptr; // weak_ptr!
    ~B() { std::cout << "B deleted\n"; }
};

void useWeakPtr()
{
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    a->b_ptr = b;
    b->a_ptr = a;
}

int main(int argc, char *argv[])
{
    // useUniquePtr();
    // useSharedPtr();
    useWeakPtr();
    return 0;
}