.. title: 01 - intro
.. slug: index
.. description: introduction to C++ streams
.. author: Xeverous

Theory
######

A stream is an abstraction over I/O (input/output) operations. The core goal is to hide implementation-specific details and offer a common interface for the same operations, regardless what the stream is actually connected to. The stream can represent a file, network traffic, in-memory operations such as compression and more - basically any abstract task that involves reading or writing data. Streams can work with any data (they almost always work on byte level) but in majority of cases it is text.

A good example is linux kernel interface, where for userspace streams are represented with file descriptors (unique integer numbers). File descriptors do not necessarily represent files on disk (they represent anything that supports I/O operations) - in unix philosophy everything is either a file or a process.

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

Obviously C++ streams are a higher level of abstraction - you don't want to directly call OS-level functions when performing I/O - doing so is bug-prone and limits code portability. On platforms where linux is the kernel, C++ standard library streams are just wrapper code around it that add buffering, error handling, formatting and other features. On other platforms (e.g. Windows) the logic is more complex as the interface mandated by the C++ standard differs from the interface provided by the OS.

Predefined streams
##################

On most OSes, each program automatically gets some streams upon startup. Unix systems example:

.. list-table::
    :header-rows: 1

    * - fd
      - stream name
      - direction
      - C stream object
      - C++ stream object
    * - 0
      - standard input
      - read
      - :cch:`stdin`
      - :cch:`std::cin`
    * - 1
      - standard output
      - write
      - :cch:`stdout`
      - :cch:`std::cout`
    * - 2
      - standard error
      - write
      - :cch:`stderr`
      - :cch:`std::cerr`

On Windows there are predefined streams too but the situation is more complicated.

:cch:`std::clog` is identical to :cch:`std::cerr` except 1 thing: :cch:`std::cerr` is the only unbuffered stream.

What exactly these streams are connected to is very system-specific (in C++ terms: predefined global stream objects are implementation-defined) but for pretty much any system:

- standard input will be connected to the keyboard
- standard output and error will be connected to the console terminal

Programs which do not have console opened (they usually either have no human interface or only GUI) still have these streams, the data just can not be observed (but could be if they were launched from a terminal or another program opened them through a *pipe* to collect their output).

Stream redirection
##################

On all shells that I know, standard output and standard error are combined in terminal output. Still, it doesn't make them the same - their data can be separated using stream redirection.

.. cch::
    :code_path: stream_redirection.cpp
    :color_path: stream_redirection.color

Below examples for Bash (they may be compatible with some other shells too):

.. code::

    # redirect stdout to null device (will display only errors)
    ./program 1>/dev/null
    # redirect stderr to null device (will display only output)
    ./program 2>/dev/null
    # redirect stderr to a file (output on screen, errors in file)
    ./program 2>errors.txt

See https://stackoverflow.com/questions/818255/in-the-shell-what-does-21-mean for more examples and explanation.

It's also possible to redirect input:

.. code::

    ./program < input.txt

in such case the program will not wait for keyboard input - :cch:`std::cin` will eat data from the file and go into failure state upon reaching end of file. This is very useful for testing programs for school/university assignments as it allows to you fully automate program's input.

Buffering
#########

For performance reasons, streams are buffered. The cost of system calls is high (regardless how much data is transferred to/from the system) so streams accumulate data and flush it (pass it to the system) once the buffer is full or a specific thing happened (e.g. text buffer got a newline character).

:cch:`std::endl` works like :cch:`'\n' << std::flush$$$chr << namespace::func`. In majority of situations the flush is redundant and only degrades performance by forcing unnecessary system calls. C++ standard library has a guuarantee that standard output is flushed before read operations on standard input. This means you can mix :cch:`std::cout` with :cch:`std::cin` without worrying that some data would not be output prior to read operations. For more information, see `CppCon 2017: Dietmar Kühl "The End of std::endl" <https://www.youtube.com/watch?v=6WeEMlmrfOI>`_ (3min).

Standard error stream is not buffered because errors are generally rare so the buffer would rarely be flushed, delaying output of important information. In the worst case a program could place error information in the buffer, then crash and the error would not be output at all. For this reason error streams output data immediately.

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
