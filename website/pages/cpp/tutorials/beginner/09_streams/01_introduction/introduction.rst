.. title: 01 - intro
.. slug: index
.. description: introduction to C++ streams
.. author: Xeverous

Theory
######

A stream is an abstraction over I/O (input/output) operations. The core goal is to hide implementation-specific details and offer a common interface for the same operations, regardless what the stream is actually connected to. The stream can represent a file, network traffic, in-memory operations such as compression and more - basically any abstract task that involves reading or writing data. Streams can work with any data (they almost always work on byte level) but in majority of cases it is text.

A good example is Linux kernel interface, where for userspace streams are represented with file descriptors (unique integer numbers). File descriptors do not necessarily represent files on disk (they represent anything that supports I/O operations) - in unix philosophy everything is either a file or a process.

Opening a stream looks differently depending on what it is:

.. cch::
    :code_path: unix_stream_open.cpp
    :color_path: unix_stream_open.color

but subsequent operations use the same interface:

.. cch::
    :code_path: unix_stream_rw.cpp
    :color_path: unix_stream_rw.color

Closing streams is also done through the same function:

.. cch::
    :code_path: unix_stream_close.cpp
    :color_path: unix_stream_close.color

.. details::
    :summary: Linux online manual pages

    - https://man7.org/linux/man-pages/man2/open.2.html
    - https://man7.org/linux/man-pages/man2/socket.2.html
    - https://man7.org/linux/man-pages/man2/read.2.html
    - https://man7.org/linux/man-pages/man2/write.2.html
    - https://man7.org/linux/man-pages/man2/close.2.html

The beauty of this approach is that once a thing has been set up (socket opened, file created, etc.) the same code can be used to operate on it, regardless of what exactly it represents. This is known as *polymorphism* and is one of key aspects of OOP (object-oriented programming, explained in later chapters). The respective OOP terms for opening, using and closing objects are *construction*, *methods* and *destruction*.

Even though majority of Linux kernel code is C (which has no explicit features for object-oriented programming), specific patterns from OOP can be seen in its interfaces. Later in the tutorial you will learn dedicated C++ features for OOP.

Standard library streams
########################

C++ streams are a higher level of abstraction - you don't want to directly call OS-level functions when performing I/O - doing so is bug-prone and limits code portability. On platforms where Linux is the kernel, C++ standard library streams are just wrapper code around it that add buffering, error handling, formatting and other features. On other platforms (e.g. Windows) the logic is more complex as the interface mandated by the C++ standard differs from the interface provided by the OS.

Streams in the standard library form a hierarchy of types:

.. TOCSS fix background (image is transparent)

.. image:: http://upload.cppreference.com/mwiki/images/0/06/std-io-complete-inheritance.svg

They are implemented using *inheritance*. Inheritance is explained in detail in polymorphism chapter, for now you just need to know it's a feature which allows to define types as extensions to other types.

- :cch:`std::ios_base` is the base type for all stream types, it holds core stream state (errors, formatting, locale and other stuff).
- :cch:`std::basic_ios` extends :cch:`std::ios_base` by adding a stream buffer - a handle to an abstract (hypothetical) I/O device. It's a template to support different character types (:cch:`CharT`) and their behavior (:cch:`Traits`).
- :cch:`std::basic_istream` and :cch:`std::basic_ostream` are primary types for input and output operations, respectively. Out of these types string-streams and file-streams are made.

``basic_`` is the name prefix C++ standard library uses when a type is a template for generalized implementation. Concrete types are aliases of the basic type with specific template parameters. Examples:

- :cch:`std::string` is an alias of :cch:`std::basic_string<char>`
- :cch:`std::wstring` is an alias of :cch:`std::basic_string<wchar_t>`
- :cch:`std::ostream` is an alias of :cch:`std::basic_ostream<char>`
- :cch:`std::wostream` is an alias of :cch:`std::basic_ostream<wchar_t>`

You don't need to understand templates for now. I'm mentioning this because cppreference only documents templates from which these types come from. Don't get surprised when searching for *something* you land on *basic_something* with an information what template parameters are - just mentally replace every occurrence of :cch:`CharT` with the type specified in the alias.

Since :cch:`wchar_t` has significant use only with Windows-related APIs, pretty much all code you will write and see will use :cch:`CharT` as :cch:`char`. Unicode, UTF-8 encoding in particular, uses single byte :cch:`char` for storing textual data and is by far the most popular text encoding.

Predefined streams
##################

Unix-like operating systems offer 3 predefined streams for every program:

- *stdin* (standard input)
- *stdout* (standard output)
- *stderr* (standard error)

Each program gets them upon startup. By default, they will be connected to the console terminal in which the program is run. Programs which do not have console opened (they usually either have no human interface or only GUI) still have these streams, the data just can not be observed (but could be if they were launched from a terminal or another program opened them through a *pipe* to collect their output).

C and C++ standard libraries offer global objects which are connected to the operating system's predefined streams:

.. list-table::
    :header-rows: 1

    * - fd
      - stream name
      - direction
      - C stream object
      - C stream type
      - C++ stream object
      - C++ stream type
    * - 0
      - standard input
      - read
      - :cch:`stdin`
      - :cch:`FILE*`
      - :cch:`std::cin`
      - :cch:`std::istream`
    * - 1
      - standard output
      - write
      - :cch:`stdout`
      - :cch:`FILE*`
      - :cch:`std::cout`
      - :cch:`std::ostream`
    * - 2
      - standard error
      - write
      - :cch:`stderr`
      - :cch:`FILE*`
      - :cch:`std::cerr`
      - :cch:`std::ostream`

..

    How relevant is this for Windows?

From C and C++ point of view (as a user of the standard library) there is no difference - they just work. Obviously underlying implementation is different - even file descriptors (called *file handles* on Windows) are designed differently.

Stream redirection
##################

Typical console terminal application combines program's standard output and standard error streams. Still, it doesn't make them the same - their data can be separated using stream redirection.

.. cch::
    :code_path: stream_redirection.cpp
    :color_path: stream_redirection.color

Below examples for the Bash shell, though they are compatible with many other shells too:

.. code::

    # redirect stdout to null device
    $ ./program 1>/dev/null
    error message
    # redirect stderr to null device (will display only output)
    $ ./program 2>/dev/null
    info message
    # redirect stderr to a file (output on screen, errors in file)
    $ ./program 2>errors.txt
    info message
    $ cat errors.txt
    error message
    # redirect stdin to stdout and then both to a file
    $ ./program > file.txt 2>&1
    $ cat file.txt
    info message
    error message

See https://stackoverflow.com/questions/818255/in-the-shell-what-does-21-mean for more examples and explanation.

It's also possible to redirect input:

.. code::

    $ ./program < input.txt

in such case the program will not wait for keyboard input - :cch:`std::cin` will eat data from the file and go into failure state upon reaching end of file. This is very useful for testing programs for school/university assignments as it allows to you fully automate program's input.

Buffering
#########

For performance reasons, streams are buffered. The cost of system calls is high (regardless how much data is transferred to/from the system) so streams accumulate data and flush it (pass it to the system) once the buffer is full or a specific thing happened (e.g. text buffer got a newline character).

:cch:`std::endl` works like :cch:`'\n' << std::flush$$$chr 2oo namespace::func`. In majority of situations the flush is redundant and only degrades performance by forcing unnecessary system calls. C++ standard library has a guuarantee that standard output is flushed before read operations on standard input. This means you can mix :cch:`std::cout` with :cch:`std::cin` without worrying that some data would not be output prior to read operations. For more information, see `CppCon 2017: Dietmar Kühl "The End of std::endl" <https://www.youtube.com/watch?v=6WeEMlmrfOI>`_ (3min).

Standard error stream is not buffered because errors are generally rare so the buffer would rarely be flushed, delaying output of important information. In the worst case a program could place error information in the buffer, then crash and the error would not be output at all. For this reason error streams output data immediately.

:cch:`std::clog` and :cch:`std::wclog` are a buffered standard error stream alternative to :cch:`std::cerr` and :cch:`std::wcerr`. As the names suggest, they are intended for logging, which typically are read some time after program execution, thus the lack of need for immediate output allows buffered implementation for increased performance.

Stream limitations
##################

Because streams provide unified way of performing I/O, many device-specific operations are not supported on the stream level of abstraction.

Supported operations:

- reading
- writing
- querying stream state (checking for errors)

Unsupported operations:

- size information (different meaning for different things: file - file size, network streams - amount of data transferred)
- manipulating device-specific state (e.g. for terminal: moving cursor, clearning output, changing text color, changes in protocol logic for network sockets)

Many C++ beginners ask how to manipulate the terminal (moving cursor, coloring text etc.) but the standard library streams operate on a higher abstraction level and thus do not offer such operations. There are some workarounds (e.g. passing :cch:`'\\r'` to :cch:`std::cout` will move cursor to the beginning of the line in the terminal, overwriting last line) but they rely on implementation-defined behavior and can easily break (e.g. if executable output is redirected to a file it can become corrupted). So if you really want device-specific behavior you need to use device-specific interface - usually a set of specific functions given by the driver or operating system. This is outside the scope of the C++ standard library and this tutorial.
