.. title: naming
.. slug: naming
.. description: how to name stuff in C++ code
.. author: Xeverous

C++ has a lot of naming conventions, partially inherited from C. This page aims to list them all to help beginners and people coming from other languages better name stuff in C++ code.

Some of these names are used pretty much always, some only when then there is no better alternative.

main function
#############

- ``argc`` - argument count variable name
- ``argv`` - argument values variable name

Examples:

- :cch:`int main(int argc, char** argv)`
- :cch:`int main(int argc, char* argv[])`

variable names
##############

When we want to concisely express variable purpose.

- ``str`` - string
- ``sv`` - string view
- ``ptr``, ``p`` - pointer
- ``n``, ``len``, ``sz`` - length/size (usually some integer type)
- ``bufsz`` - size of a buffer
- ``i``, ``j``, ``k``, ... - loop control variables - probably originated from ``i`` as a shortcut for *iteration* - this convention applies to many programming languages
- ``x``, ``y``, ``z``, ``w``, ``u``, ``v`` - anything related to position, sometimes also loop counters
- ``first``, ``last``, ``it`` - counters in iterator-based loops, variables/parameters in algorithms
- ``lhs``, ``rhs`` (left/right hand side) - used for operator overloading and comparisons - use these if you have no better names to represent 2 different objects of the same type
- ``scoped_`` - RAII wrappers around specific tasks (e.g. :cch:`std::scoped_lock`, :cch:`std::scoped_allocator_adaptor`)

type names
##########

- ``basic_*`` - for any class template that is expected to be instantiated with different template parameters, e.g. :cch:`std::string` is an alias for :cch:`std::basic_string<char>`, :cch:`std::string_view` is an alias for :cch:`std::basic_string_view<char>`
- ``*_type`` - member type aliases, e.g. if you have a class that holds some objects in a very specific container (which may have very long name) you should define a member type alias (inside the class) named ``container_type``
- there is no pattern for exception class names like ``E*`` or ``*Exception`` in other languages
- there is no pattern for interface class names like ``I*`` or ``*Interface`` in other languages

functions
#########

- (very strong) ``to_*`` - common name for functions which transform a single object to a different type, e.g. :cch:`std::to_string`, :cch:`std::to_chars`, :cch:`std::to_address`
- (very strong) ``make_*`` - common name for factory functions which create an object of specific type (often from multiple arguments) (often multiple overloads), e.g. :cch:`std::make_unique`, :cch:`std::make_shared`, :cch:`std::make_pair`, :cch:`std::make_tuple`, :cch:`std::make_optional`, :cch:`std::make_error_code`
- (strong) ``*_impl`` - common where a function (or class) implementation needs to be split, the implementation code has the same name with ``_impl`` appended (or ``do_`` prepended); very common in boost libraries

templates
#########

- (very strong) ``T``, ``U``, ``V``, ... - similarly to loops, likely originated from ``T`` as a shortcut for *type* or *template*, used as template type parameter names
- (very strong) ``ForwardIterator``, ``UnaryPredicate``, ``TriviallyCopyable``, etc - concept names for types that are expected to satisfy certain requirements (since C++20 actual language feature, no longer a convention)
- (very strong) ``Ts``, ``Args``, any noun in plural form - to name parameter pack in variadic templates
- ``*_t`` - type aliases found inside type traits
- ``*_v`` - values found inside type traits

other
#####

- ``impl``, ``detail`` - common names for namespaces that indicate implementation details (code inside is not a part of public API and has no documentation)
