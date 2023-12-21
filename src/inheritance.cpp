#include <vector>
#include <string>
#include <iostream>

// In java, there's something called interface.
// interface defines what a class need to provide
//
// interface Drink {
//     public void make();
// }
//
// class Tea implements Drink {
//     public void make(){
//          implementation
//     }
// }

// C++ has the similary thing, call pure virtual function and inheritence
class Drink1
{
public:
    // we declare make as a pure-virtual function,
    // means this function will be overload by other classes which inherits Drink
    // by equals to zero, it means any class inherited Drink must implement them
    // or the compiler will throw an error
    virtual void make() = 0;

    // test here is a virtual function
    virtual void test() {}
};

// In C++, if a function has a least one pure virtual function
// then it is called abstract class
// abstract class cannot be instantiated

// * Here public means how to inherit Drink. There are public, protected, private
// * public means, public in Drink is still public in Tea, private in Drink is still private in Tea, protected in Drink is still protected in Tead
// * private and protected means convert all things in Drink into private or protected
class Tea1 : public Drink1
{
public:
    void make()
    {
        // implementation
        std::cout << "Making a cup of tea..." << std::endl;
    }
};

class Drink
{
private:
    std::string _flavor;

public:
    Drink() = default;
    Drink(std::string flavor) : _flavor(flavor) {}

    virtual void make() = 0;
    virtual ~Drink() = default;
};

class Tea : public Drink
{
public:
    Tea() = default;
    Tea(std::string flavor) : Drink(flavor) {}
    virtual ~Tea(){};

    void make()
    {
        std::cout << "Made tea from the Tea class!" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    Tea t("red");
    t.make();
    return 0;
}