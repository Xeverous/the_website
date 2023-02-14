<!--
.. title: C++ FAQ
.. slug: cpp_faq
.. description: a list of common questions regarding C++
.. author: Xeverous
-->

## language

### What is *modern* C++?

It's the refreshed version of the language, the 2011 and later updates. C++11 brought many changes and new features but most importantly - new idioms. Although the language has become more complicated (due to keeping backwards compatibility), the code is now simpler as a lot of new features are better alternatives to previous ones.

Modern C++ is about:

- embracing core C++ idioms such as RAII - compile time resource safety
- encapsulating error-prone low-level code invariants in high-level statically checked interfaces (especially smart pointers, containers and iterators)
- writing type-safe, resource-safe and exception-safe code
- avoiding unportable vendor-specific extensions
- using the standard library, not reinventing the wheel
- ability to program in various styles, not just object-oriented
- ability to use generic programming and metaprogramming
- ability to write simple code thanks to encapsulation in powerful libraries

Aims of modern C++:

- no leaks
- no memory corruption
- no garbage collection
- no limitations of expressibility
- no performance degradation (zero-overhead abstractions)
- ISO-standarized code (guaranteed portability)
- tool enforced correctness

<!-- Source: 44:30 and 1:04:55 "Bjarne Stroustrup: learning and teaching modern C++". -->

### What is C++0x?

The old term for C++11. It was initially planned to arrive before 2010.

Similarly, for later standards:

- C++1y is C++14
- C++1z is C++17
- C++2a is C++20

### `this` is never null. Why is it a pointer, not a reference?

Because `this` was introduced before references have been added to the language. If references came earlier, `this` would be a reference. [SO question about this being a reference](https://stackoverflow.com/questions/645994/why-this-is-a-pointer-and-not-a-reference).

### Why `constexpr` is not applied automatically anywhere possible?

`constexpr` is applied automatically to aggregate type constructors. Besides this, it would be risky to do so. `constexpr` is a form of explicit promise: the code can be invoked at compile time. If it was applied automatically it would be very easy to introduce breaking changes: someone might rely on a particular library version being compile time compliant but future version could break it while the library author never meant it to be used this way. By having to specify compile time compliance explictly, code author can clearly express that code can be safely used in compile time contexts.

Exactly the same principles applies to `noexcept`. This is an explicit promise that the code in the current (and any future) version will not throw exceptions. No keyword means you should not assume such guarantee.

Note that in the case of code that is not formally `constexpr` or `noexcept` compilers may still optimize it as if it was, it just does not happen at the language level.

### Is there a way to terminate the program instantly outside the main function?

Yes. [There are functions which kill the program in various ways](https://en.cppreference.com/w/cpp/utility/program).

### Is C faster than C++?

TODO this question should end being a seprate article. There is a lot to write about.

No. Correctly written code should be fast in both languages. It's just that misused C usually ends in crashes but misused C++ usually ends in lower performance or complex build errors.

There are few things in C that are slower than their relatives in C++. This applies specifically to C standard library which does not have efficient generic abstractions besides macros - for example C functions taking function pointers are far worse optimized than C++ templates.

Even when developing high-performance programs, performance is not needed strictly everywhere. Where possible, convenience features can be used over performance features. It doesn't matter if text entered by the user is processed 10% slower (e.g. because you used a lot of very-safe-and-convenient-but-somewhat-slower things) but it matters if the full product can be delivered several times faster (because you avoid manually rewriting input processing in C) with the same core performance (where C and C++ code uses very similar or even the same mechanisms).

From Bjarne Stroustrup FAQ:

> If nothing else, you can write the program in C style benefiting from C++'s stronger type checking and better notational support, but most programs can benefit from C++'s support for generic and object-oriented programming without compromising size or performance. Sticking to the C-like subset of C++ is most often counter-productive.

> Writing Java-style code in C++ can be as frustrating and sub-optimal as writing C-style code in C++.

> I never saw a project for which C was better than C++ for any reason but the lack of a good C++ compiler.

### Is C++ a legacy language? It is old design?

From Bjarne Stroustrup FAQ:

> Naturally, calling C++ a legacy language shows a bias \[...\]. That aside, people are usually thinking of Java or C# when they ask such a question. I will not compare C++ to those languages, but I can point out that "modern" doesn't necessarily mean "better", and that both Java and C# are rooted in 1980s style OOP to an even greater extent than early C++ is.

> Since 1987 or so, the focus of development the C++ language and its associated programming styles have been the use of templates, static polymorphism, generic programming, and multiparadigm programming. This is way beyond the scope of the much-hyped proprietary languages. Another key difference is that C++ supports user-defined types to the same extent as built-in types. This - especially in combination with the use of templates, constructors, and destructors - enables the C++ programmer to use programming and design techniques that (IMO) are more advanced than what is supported in the languages with which C++ is most often compared

### Is C++ an OOP language?

It belongs to the family of OO languages, but more accurately, C++ is a multi-paradigm language. It means if offers various styles of programming that can be mixed together.

C is mostly about imperative, structural programming. This style is still practiced (not only in C++) but almost always is augmented by other, unique features of the given language and mixed with different paradigms.

C++ puts a great effort to support many paradigms, including object-oriented, functional, generic and metaprogramming. The whole STL is designed around generic programming - instead of implementing interfaces you specialize and instantiate templates.

See also cat-dog program written in various styles. TOWRITE.

### What is STL?

Standard template library. Specifically, containers (data structures), iterators and algorithms. By far templates are the biggest part of C++ standard library (more than 90%). It's quite an effort to find a thing that is not a template.

Now STL is a so fundamental part of the C++ standard library that it's hard to imagine C++ without it. In fact, in many contexts people use the term STL but they actually mean the C++ standard library.

### Is STL for C++ the same thing as LINQ for C#? What are the differences?

Somewhat yes, somewhat no. Both languages use their tools to work with data and apply algorithms but both of these tools have some differences.

- LINQ is a built-in feature in the C# language that utilizes what is offered by .NET. It has its own keywords. STL is a part of the C++ standard library - it can be reimplemented from scratch - it is just a bunch of code.
- LINQ primarily relies on runtime information, STL primarily relies on compile time information.
- LINQ is designed to provide a uniform interface of working with various sources of data (databases, collections, documents, configuration files) and to allow various .NET components to implement a common interface. STL is designed on a lower level - it is made to provide a uniform way of working with containers and iterators. It is designed to write generic code that works and is compiled to as optimal machine code as possible for any data structure, regardless of its memory layout.

## Templates

### What are the differences between C++ templates and Java/C# generics?

Read this [SO question](https://stackoverflow.com/questions/31693/what-are-the-differences-between-generics-in-c-sharp-and-java-and-templates-i).

### What's the difference between `template <typename T>` and `template <class T>`?

There is no difference except 1 corner case which was addressed in C++17. Prior to this, `typename` and `class` keywords could be used interchargebly, with the exception of *template template parameters* in which `class` had to be used (small "typo" in the standard). Since C++17 both are officially valid everywhere, but major compilers accepted it much earlier.

Historically, the keyword `class` was used first in templates to indicate aliased type. It's a common practice in C and C++ to reuse existing keywords for new contexts to avoid creating new ones that could invalidate existing code. Eventually new keyword was created for templates - `typename` (resembling existing `typedef`) to avoid confusion about `class` (template types do not have to be classes, they can also be trivial built-in types). Funny is that `typename` keyword has been overloaded later anyway, so now both keywords are multi-purpose and have different meanings depending on the context.

Some may use a convention that `typename` aliases any type (for example an array holding objects of any type) and `class` is supposed to be instantiated only on types that match specific criteria (e.g. concept of an iterator). Some will write `class` because it's shorter. Some will choose the convention to choose one keyword and stick to it for consistency.

There is also a very rare case when unit testing of protected/private inherited classes uses the hack `#define class struct`, `#define protected public`, `#define private public` - it explodes on `template <class>`. You should not be using such hacks anyway, or resort to more non-intrusive ways such as `-fno-access-control`.

I use the designated keyword `typename` everywhere for consistency and to avoid any confusion. Some C++ beginners (usually after learning other language) incorrectly think that C++ templates work only with classes.

### Why `T` in templates?

I don't know the exact reason, but I predict it started either from the word "type" or "template". This is one of the very few places where C++ uses PascalCase. In generic contexts where more aliases are needed next alphabet letters are used.

In case of more adanced templates and concepts, longer and more descriptive names are used sush as `RandomAccessIterator` and `TriviallyConstructible`.

## making C++

### In Python community it is often said that something is or is not "pythonic". Does C++ have any philosophy or a manifesto of its own?

Most of the C++ philosophy is under the "modern C++" label, but few core members of the committee issued a paper which outlines general plan for the language (including decades-long long-term goals): [The direction for ISO C++](wg21.link/P0939).

### Who actually makes C++? How is it made?

The ISO WG21 committee. Members include Bjarne Stroustrup (language creator) and programming experts from Google, Microsoft, Intel, IBM, Qualcomm, Qt, nVidia and other companies. Committee is open-ended and always says they would take more people - so far it's lacking game dev representatives.

The committee is divided into groups:

- Library Working Group
- Library Evolution Working Group
- Core Working Group
- Evolution Working Group
- Study Groups (more than 15, various topics: e.g. concurrency, low-latency, database, networking)

[Committee schema + images](https://isocpp.org/std/the-committee)

[Infographic of ongoing work on features](https://isocpp.org/std/status)

Committee organizes official meetings every few months and every 3 years issues new international standard.

### Can I submit my own idea for C++?

Yes, check [how to submit a proposal](https://isocpp.org/std/submit-a-proposal). Also, see the [list of ongoing proposals](https://github.com/cplusplus/papers/issues)

Note that many proposals have been rejected and the committee knows that the last thing C++ needs is more complex, unintuitive and hard to learn features. Someone said that while the majority of proposals make sense, if all have been accepted C++ would stop being usable at all.

If you don't have large experience in any industry field, chances are your propositions will be quickly dismissed. Committee wants solutions to problems, backed with implementation experience. I would first post on [/r/cpp](reddit.com/r/cpp) to discuss any changes - many things are being proposed over and over, while not sticking to the language spirit.
