.. title: 09 - std::cin
.. slug: index
.. description: introduction to standard input
.. author: Xeverous

:cch:`std::cin` is an input stream (a globally accessible object of type :cch:`std::istream`). It can be used to extract data from operating system's character input stream (called *stdin*). For most systems, this simply means that if you run the executable in a terminal shell it will accept input from the keyboard.

Unlike :cch:`std::cout`, :cch:`std::cin` uses ``>>`` (it reads to variables, ``<<`` is used for output). Similarly to output, it supports many data types.

Example:

.. cch::
    :code_path: example.cpp
    :color_path: example.color

You can chain reads too. Just like with ``<<``, operands are processed from left to right.

.. cch::
    :code_path: chained_read.cpp
    :color_path: chained_read.color

Input operations may fail. Reasons may vary:

- strictly technical such as failure to allocate memory (generally absent)
- invalid data (e.g. letters when digits for numeric input are expected)
- too long data (e.g. too many digits for given numeric type - value not representable within supported range)

Upon erroneous operation, C++ streams go into failure state, ignoring any further input unless the state is explicitly reset (all input operations will finish immediately). Because error handling requires more knowledge, for now programs will assume that the input is always valid.

For each input request, :cch:`std::cin` will first discard any whitespace characters (space, tab, line break, etc.) and then consume as much valid characters as possible. For an input like space-123-enter-456-enter (technically :cch:` 123\n456\n$$$str`), it will:

- first input:

  - read and ignore the space character
  - read all digits
  - stop on line break (the character will not be consumed)

- second input:

  - read and ignore line break
  - read all digits
  - stop on line break

Note that what is seen on the terminal may not be exactly the same thing that the program is receiving (though in most cases it is). In addition, various command-line terminals may offer specific behavior under specific key combinations (e.g. tab for autocompletion) - such key strokes are not sent to the executed program but intercepted by the terminal program. I can't really list any recommendation here - different terminals differ significantly, the only convention widely agreed upon is tab for autocompletion and enter for any confirmation.

Stream redirection
##################

Input/output (I/O for short) streams are features of the operating system. Shells in such systems offer to manipulate these streams. For example, the program's output may be redirected to a file: ``./hello_world > output.txt``. In such case, the program's output will not be visible in the terminal but a file containing the output will be created instead. Programs are generally unaware of these mechanics unless they explicitly interact with the operating system to check for it (C++ standard library streams don't).

You can also do the same thing with input, within most shells it will be ``./program < input.txt``. This allows you to automate :cch:`std::cin` - this is very useful for repetitive testing of implementations of exercises.

That's enough you should know about streams for now. More will be explained in a dedicated chapter.

FAQ
###

    Can I ask for input and output on the same code line?

No. You will need 2 different statements. Technically it is possible, but most standard streams are separated into input and output streams (most streams perform operations in one direction).
