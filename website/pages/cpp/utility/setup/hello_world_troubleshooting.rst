.. title: hello world troubleshooting
.. slug: hello_world_troubleshooting
.. description: solving problems with C++ environment setup
.. author: Xeverous

The `"hello horld" <https://en.wikipedia.org/wiki/"Hello,_World!"_program>`_ should print a string on the terminal.

.. TOINCLUDE hello world

Below I wrote a list of common environment setup problems, ordered by toolchain. There are many more possile problems (I only listed ones I know well), usually an answer is found on Stack Overflow. If you have a reddit account, you can also ask on `/r/cpp_questions <https://www.reddit.com/r/cpp_questions/>`_.

Windows
#######

Can not launch the executable
=============================

This can be caused by an antivirus program, which assumes unknown executables are suspicious. To workaround, most antiviruses have an option to exclude specified directories from automatic scanning.

Strange x86 / x86_64 error when launching the executable
========================================================

You have a 32-bit computer but build the project for 64-bit. Your processor architecture can not run this instruction set.

Solution: change settings so that 32 bit programs are built instead.

- GCC / Clang: add ``-m32`` to compiler and linker flags
- MSVC: open project properties and the linker settings

Works, but disappears immediately
=================================

This is a correct behaviour, since the only task for the program was to print the text and close (sometimes it may not even open a terminal if build with specific compiler/linker options). It's actually a feature in some IDEs that they stop the program when it finishes so the window does not disappear.

There are multiple workarounds:

- fiddle with IDE settings
- run the program in a console terminal (the program will close, but the terminal will not)
- insert :cch:`std::cin.get();` at the end of :cch:`main` function - this will wait for a key press; may not work if you mix it with other input methods - if this is the case use these (identical) methods instead (I don't want to explain stream peculiarities here)

Windows + MinGW
###############

- Windows XP or later
- any port of GCC toolchain (MinGW or MinGW-w64)
- any IDE other than Visual Studio (*Visual Studio Code* is different from *Visual Studio*)

IDE can not find the compiler
=============================

This problem usually appears where after installing (or just unpacking) a compiler it's not automatically added to the ``PATH`` environmental variable. This variable is used by many programs to search for other programs.

Copy the path of your compiler binary directory and append it to the ``PATH`` in *Control Panel* -> *environmental variables* (this is a pretty deeply hidden option, search the internet for screens if you can't find it).

The path should be a sequence of directories leading to the one where the compiler executable resides. For example, if your compiler path is ``C:\MinGW\bin\g++.exe`` (the ``bin`` directory for various GCC ports is usually full of executables and some ``dll`` files) the added path should be ``C:\MinGW\bin``. MinGW-w64 distributions may have longer paths such as ``C:\mingw-w64\i686-7.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin``).

- If the variable ``PATH`` does not exists in the list, just add it (name it ``PATH`` and the value is the actual path)
- if ``PATH`` already exists, append your path to it after semicolon: ``C:\foo;C:\bar;C:\compiler\bin``. Newer Windows versions offer improved interface which presents ``PATH`` as an array of values - then just add a new entry.

Changes to environmental variables require to close all console terminals (e.g. cmd). If it doesn't work, try restarting the system.

After ``PATH`` is set, you should be able to call the compiler from the command line, regardless of the working directory:

.. code::

    C:\Users\admin>g++ --version
    g++ (i686-posix-dwarf-rev1, Built by MinGW-W64 project) 7.2.0
    Copyright (C) 2017 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

IDE sees the compiler but can not find make
===========================================

This problem is similar to the one above - this time the ``make`` program can not be found.

Go to your compiler installation directory and check that ``make`` actually exists in the ``bin`` directory. You may find something like ``mingw-make32.exe`` or ``i686-w64-mingw32-make.exe``. It is because various GCC distributions prefix some executable names with architecture name in case someone wanted to have a multi-architecture toolchain installed in 1 place. I hardly doubt you want to compile now for something other than x86 (i686) / x86_64 (these are the architecture names of standard 32-bit and 64-bit PC).

If this is the case - simply copy the executable and give the copy a ``make.exe`` name. Do not just rename - copy and leave both variants - this is because some other tools might have hardcoded expectation of the original name.

You might also find more executables with prefixed names - in case of problems do the same.

Test that it works by calling make from the command line:

TODO make --version

Nothing happens when the executable is launched
===============================================

If you are trying to launch it from the Explorer (the file/directory browsing program), open command line in this directory (as a shortcut you can click the path and just write "cmd") and attempt to launch it from the terminal. This sometimes results in displaying what has gone wrong.

Missing dll
===========

This means that the program has been built successfully but some compiled code is missing - usually the implementation of the C++ standard library (``libstdc++-6.dll``) or other *dynamically linked libraries* that are needed in order to run (they vary depending on the compiler).

These files can be found in the ``bin`` directory of the compiler's installation. To avoid `DLL Hell <https://en.wikipedia.org/wiki/DLL_Hell>`_, simply copy required files to your executable's directory.

An alternative would be to use *static linking* instead, which copies required machine code into the executable. See https://stackoverflow.com/questions/26103966/how-can-i-statically-link-standard-library-to-my-c-program for more information.

Windows + Visual Studio
#######################

Often referred to as MSVC (Microsoft Visual C/C++ compiler).

something ``stdafx.h`` or ``fatal error C1010``
===============================================

This comes from a popular feature known as *precompiled headers*. The purpose of it is to speed up building process, though I have to admit that no IDE does it in a so intrusive way as Visual Studio (this is the only implementation of precompiled headers I know which requires changes in code).

You have few options:

- Create a file named ``stdafx.h`` and add it to your project (the file can be empty)
- Disable precompiled headers
- Change precompiled headers to use a non-code-intrusive way (I heard this is somehow possible)
- Use a different project wizard (VS has a lot of options in the "new project" menu)

See https://stackoverflow.com/questions/4726155/ for more information.

GNU+Linux
#########

Also applies if using Clang compiler.

Permission denied when trying to launch the program
===================================================

Check that the executable is actually an executable. Verify that it has ``x`` flag on by using ``ls -l /path/to/executable``. If not, add the flag by ``chmod +x /path/to/executable``.

IDE can not find the compiler
=============================

Some distributions may come with GCC already, but it may have only C components installed or have an old version of the C++ compiler. Check the version of both ``gcc`` and ``g++``. On some system configurations ``gcc --version`` might print a different number from ``g++ --version``.

Various distributions offer C and C++ compilers in their package managers (``apt``, ``yum``, etc.), installing them using commands like ``sudo apt install g++`` is the simplest way although the delivered programs may not be very recent.
