.. title: xx - command line arguments
.. slug: index
.. description: parsing command line arguments
.. author: Xeverous

You might have already seen a somewhat different main function:

.. cch::
    :code_path: main_with_args.cpp
    :color_path: main_with_args.color

This is the way you can define a main function to accept a variable number of null-terminated C-strings, typically called "program's command line arguments".

Command line arguments are one of primary ways to provide input data to the program - you have already seen it with many shell built-in programs (e.g. ``cd``), OS-provided programs (e.g. ``echo``, ``grep``) and others (e.g. compiler, linker).

Details
#######

- :cch:`argc` is **arg**\ ument **c**\ ount
- :cch:`argv` is **arg**\ ument **v**\ ector: an array of C-strings (C-strings are :cch:`char*` so an array of them is :cch:`char**` or :cch:`char*[]`)
- :cch:`argv[argc]$$$param[param]` (which normally would be undefined behavior) points to an empty C-string, though I don't see practical value in it (it's the same bad convention as with null-terminated strings, now just for an array)
- :cch:`argc >= 0$$$param >= num`

How exactly the textual arguments are passed to the program is system and implementation dependent (typically spaces separate arguments and quotes must be used to contain them). By the nature of the :cch:`char` type, it's most suitable for ASCII or Unicode UTF-8 and is such in most configurations.

Example
#######

.. cch::
    :code_path: example.cpp
    :color_path: example.color

.. code::

    $ ./program --arg1 --arg2 "a r g 3" -x 10 -y=20
    argument count: 5
    argument values:
    0: ./program
    1: --arg1
    2: --arg2
    3: a r g 3
    4: -x
    5: 10
    6: -y=20

The value behind :cch:`argv[0]$$$param[num]` depends on the system. In a typical implementation it will be the same string that has been used to call the program.

Parsing arguments
#################

C++ standard library does not cover argument parsing. I suggest to use any external library instead - many have an API that is easy to understand and allow automatic generation of ``--help`` and other commands. `Boost has one too <http://boost.org/libs/program_options>`_ but it requires building so unless you already use boost I suggest to find a header-only library (it will be much easier to set up).

In many C projects you may find `getopt <https://en.wikipedia.org/wiki/Getopt>`_ being used. From C++ point of view its interface is very C-ish but nonetheless it's quite popular in projects for Unix systems.

.. admonition:: note
    :class: note

    :cch:`getopt` and its GNU extension (:cch:`getopt_long`) are provided as an addition to the C standard library on Unix systems. The first one is a part of `POSIX <https://en.wikipedia.org/wiki/POSIX>`_ but none are a part of C or C++ standard library. Thus, their availability is tied to the system and the compiler, not language standard. Thus you will find them `documented with the system such as Linux <https://linux.die.net/man/3/getopt>`_ (GNU/Linux distributions are mostly POSIX-compliant) instead of on cppreference.
