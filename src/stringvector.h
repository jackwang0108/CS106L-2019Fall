#ifndef __STRINGVECTOR_H
#define __STRINGVECTOR_H

#include <string>
#include <vector>
#include <algorithm>

using size_type = std::size_t;

const int kInitialSize = 10;

class StringVector
{
private:
    size_type logicalSize;
    size_type allocatedSize;
    std::string *elems;

public:
    size_type size() const { return logicalSize; }

    bool empty() const { return size() == 0; }

    StringVector();
    // Copy constructor
    StringVector(const StringVector &other) noexcept;
    StringVector(size_type n, const std::string &val);
    StringVector(StringVector &&other) noexcept;
    ~StringVector();

    using iterator = std::string *;
    using const_iterator = const iterator;
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    void grow();
    iterator insert(iterator pos, const std::string &elem);
    void push_back(const std::string &elem);

    StringVector &operator+=(const std::string &element);
    StringVector &operator+=(const StringVector &other);
    StringVector operator+(const StringVector &other) const;
    StringVector &operator=(const StringVector &other);
    StringVector &operator=(StringVector &&rhs) noexcept;

    // prohibit other operator
    StringVector &operator-=(const StringVector &other) = delete;
};

StringVector::StringVector()
    : logicalSize(0), allocatedSize(kInitialSize)
{
    elems = new std::string[allocatedSize];
}

// * Below is initialization list
// * The usage of initialization list is that assigning value as creating the object
// * i.e. creating the object and assigning value are simultaneously
// * When entering the constructor, the compiler actually has created the object
// * and until running the codes inside the constrctor, the values are set into the members
// * So if we are like, const StringValue v1(2, "Hello").
// * We cannot change num because is ths const
StringVector::StringVector(size_type n, const std::string &val)
    : logicalSize(n), allocatedSize(2 * n)
{
    elems = new std::string[allocatedSize];
    std::fill(begin(), end(), val);
}

StringVector::~StringVector()
{
    delete[] elems;
}

StringVector::iterator StringVector::begin()
{
    return elems;
}

const StringVector::iterator StringVector::begin() const
{
    return elems;
}

StringVector::iterator StringVector::end()
{
    return begin() + size();
}

const StringVector::iterator StringVector::end() const
{
    return begin() + size();
}

void StringVector::grow()
{
    iterator new_elems = new std::string[2 * allocatedSize];
    std::copy(begin(), end(), new_elems);
    delete[] elems;
    allocatedSize = 2;
    elems = new_elems;
}

StringVector::iterator StringVector::insert(iterator pos, const std::string &elem)
{
    size_type indx = static_cast<size_type>(pos - begin());
    if (size() == allocatedSize)
    {
        grow();
    }

    pos = begin() + indx;
    std::copy_backward(pos, end(), end() + 1);
    *pos = elem;
    this->logicalSize += 1;
    return pos;
}

void StringVector::push_back(const std::string &elem)
{
    insert(end(), elem);
}

// * add operator+=

// = if we don't return a reference, the code below
// StrinVector c;
// (c += "Test") += "Try";
// will copy StrigVector two times
StringVector &StringVector::operator+=(const std::string &element)
{
    push_back(element);
    return *this;
}

StringVector &StringVector::operator+=(const StringVector &other)
{
    for (auto s : other)
        push_back(s);
    return *this;
}

// * add operator +
StringVector StringVector::operator+(const StringVector &other) const
{
    // = this code actually doesn't work.
    // = because of the = operator is not defined
    StringVector result = *this;
    for (const std::string &s : other)
        result.push_back(s);
    return result;
}

// = but it is actually better to declare it as a non-member function
// * This one is better
StringVector operator+(const StringVector &first, const StringVector &second)
{
    StringVector result = first;
    for (const std::string &s : second)
        result.push_back(s);
    return result;
}

// = The tricky thing about the copy assignment is that is only copies the member
// = So, if we have a pointer as member
// = the memory that the pointer points actually didn't change

// now let us finish the copy constructor
StringVector::StringVector(const StringVector &other) noexcept
    : logicalSize(other.logicalSize), allocatedSize(other.allocatedSize)
{
    elems = new std::string[allocatedSize];
    std::copy(other.begin(), other.end(), begin());
}

// * add copy assignment
StringVector &StringVector::operator=(const StringVector &other)
{
    // check if use v1 = v1
    if (this == &other)
        return *this;
    // This is not construcotr, so we cannot use initialization list
    logicalSize = other.logicalSize;
    allocatedSize = other.allocatedSize;
    // free the old one
    delete[] elems;
    elems = new std::string[allocatedSize];
    std::copy(other.begin(), other.end(), begin());
    return *this;
}

// You don't need to wirte Copy constructors and Copy assign operator for every class
// By default, the compiler will create one for you which copies all members
// * Only write them when the default one cannot satisfy your need
// * the most common reason to rewrite the default special member function is
// * about the ownership
// * pointers, mutex, filestreams, etc.

// Another rule is that, if you define or delete any of the copy constructor, copy assign, destructor
// you should define ALL three

// By default, we don't have to create the destructor by ouerself,
// we just need to create different types of constructor
// if and only if we have something special (ownership problem), we need to create a destructor

// Move constructor
// * the key concept of move semantics is use rvalue reference as parameter
// * and steal the member from rvalue reference
StringVector::StringVector(StringVector &&other) noexcept
    : elems(std::move(other.elems)),
      logicalSize(std::move(other.logicalSize)),
      allocatedSize(std::move(other.allocatedSize))
{
    other.elems = nullptr;
}

// move assign operator
StringVector &StringVector::operator=(StringVector &&rhs) noexcept
{
    if (this != &rhs)
    {
        // delete this before
        delete[] elems;
        logicalSize = std::move(rhs.logicalSize);
        allocatedSize = std::move(rhs.allocatedSize);
        elems = rhs.elems;
        rhs.elems = nullptr;
    }
    return *this;
}

#endif