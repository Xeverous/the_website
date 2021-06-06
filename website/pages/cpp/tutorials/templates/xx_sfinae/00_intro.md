<!--
.. title: 00 - intro
.. slug: 00_intro
.. description: introduction to SFINAE
.. author: Xeverous
-->

Suppose you have mixed function overloading with templates. One implementation is a template, one is not.

```c++
#include <iostream>

class animal
{
public:
    virtual ~animal() = default;
    virtual std::string sound() const = 0;
};

class cat : public animal
{
public:
    std::string sound() const override
    {
        return "meow";
    }
};

template <typename T>
void print_info(const T& t)
{
    std::cout << "Object is not an animal and has value " << t << ".\n";
}

void print_info(const animal& a)
{
    std::cout << "Object is an animal and does " << a.sound() << ".\n";
}

int main()
{
    int x = 7;
    cat c;
    print_info(x); // expecting template function with [T = int]
    print_info(c); // expecting non-template function
}
```

It seems reasonable that the expected output would be:

```
Object is not an animal and has value 7.
Object is an animal and does meow.
```

Instead, we get a compiler error spam starting with something like this (everything further down is about all failed attempts to match operators with various stream << overloads):

```c++
main.cpp: In instantiation of 'void print_info(const T&) [with T = cat]':
main.cpp:34:17:   required from here
main.cpp:21:59: error: no match for 'operator<<' (operand types are 'std::basic_ostream<char>' and 'const cat')
     std::cout << "object is not an animal and has value " << t << '\n';
     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~
```

So what has gone wrong? The key is "in instantation of `void print_info(const T&) [with T = cat]`" and the text fragment from function template. **Why template overload was choosen when a cat is an animal?**

The short answer is very simple: **templates do not like convertions**. There were 2 choices:

- use `print_info(const animal&)` - requires to perform implicit upcast
- use `print_info(const T&)` with `T = cat` - a perfect match

The second option was choosen. Why call a function needing implicit convertion when we can use `T = cat` and perfectly match the type? This is "how templates think".

The cause of this problem is the fact that **overload resolution happens after template argument deduction**.

Entire process, done by the compiler:

- The expression `print_info(c)` must be evaluated.
- The name `print_info` is looked up in relevant scopes (I will skip name lookup internals, they don't matter in this case)
- The name is resolved to a function. Begin search of all possible overloads.
- 2 potential matches are found:

```c++
template <typename T>
void print_info(const T&);      // (1)

void print_info(const animal&); // (2)
```

- Template type deduction is performed. For (1), based on provided argument, `T` is deduced to `cat`. All deductions succeed.
- Overload resolution has 2 candidates to consider:

```c++
void print_info(const cat&);    // (1)
void print_info(const animal&); // (2)
```

- (1) is choosen because it's a perfect match. (2) would require implicit convertion.

The fact that the deduction occurs before different overloads are considered has a big consequence. It's an impactful C++ language design decision. If the reverse was true, there would be many problems regarding template specializations and overloads. Instead of good matches with (potentially specialized) templates, various types would pretend very weird convertions to fit into non-template overloads potentially losing data or accuracy while being converted.

However, there is another consequence. **Because deduction occurs first, it has been allowed to fail.** Overloads in which deduction failed are not considered. As long as at least 1 overload matches and has no competing overload with the same overload resolution scoring, function call will succeed. This enables SFINAE (substitution failure is not an error) which is a very powerful feature capable to throw away certain overloads before they can be considered.

SFINAE means that instead of compilation errors, overloads with failed deduction are simply not considered to be available. The error would only arise if all overloads have been discarded (there would not be anything left to choose from). As long as at least 1 candidate is valid, everything is ok, we just ignore these that do not make sense.
