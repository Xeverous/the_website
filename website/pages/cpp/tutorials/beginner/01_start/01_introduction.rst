.. title: 01 - introduction
.. slug: 01_introduction
.. description: introduction to programming
.. author: Xeverous

.. TODO I have a feeling this whole article could be significantly improved. It lacks C, C++ history and needs better separation from universal programming knowledge and C/C++ specific knowledge.

Programming is the act of making computer programs. A computer program is just a sequence of instructions that can executed on a `Turing machine <https://en.wikipedia.org/wiki/Turing_machine>`_. The term is pretty complex but explained briefly it represents an abstract machine that can perform 3 tasks:

- read instruction/data
- write data
- move to the next instruction (where move is not necessarily one-by-one in the same direction)

Further developments in engineering led to creation of faster and smaller machines that realize this mathematical concept using electric energy. As you may already know, computers use binary system (base 2, as opposed to humans which primarily\ [1]_ use base 10) but said shortly, it's only a matter of representation and doesn't affect results at all. Math is the same, it's just a different form of writing. Computers use base 2 due to practical reasons - there were attempts at other systems but ultimately constructing a device that works with only 2 different current states is the simplest of all.

You might wonder why there are multiple programming languages. Like human languages, programming languages evolved separately over time but the cause of evolution is much different - the primary reason being how to best abstract underlying mathematical concepts. If you have seen the same mathematical problems written differently (usually different symbols) - the same thing happens in programming.

All widely used programming languages are based on English. The reason is simple: IT started and grew mostly in english-speaking part of the world.

Paragraphs below present simplified view of various key aspects of programming.

First computer programs
#######################

At first, there was nothing more than the *machine code*. A form of representation that the machine directly understands. Depending on the device architecture, it could be perforated paper tape, punched card or any other way of storing information on physical object. Each row (or column) of holes represented a single portion of an instruction or input data. Writing programs was a quite tedious and unforgiving task - a mistaken hole in the tape could not be repaired.

Assembly
########

As the time went, one of first major steps towards better abstaction was *assembly*. Once machines were capable of operating on text, the new way of programming was writing instructions using their shortcut names known as *opcodes* or *mnemonics*.

.. code::

    mov     eax, edi ; move value in EDI register to EAX register
    imul    eax, esi ; save into EAX result of integer multiplication EAX * ESI

One particular advantage of this approach was that programmers were no longer required to memorize binary representation of instructions. They could write instructions using their mnemonics and the *assembler* would later transform this text into binary code which machines can execute. Assembly languages also allowed to insert comments - arbitrary text which is ignored.

High-level programming
######################

As computers got more powerful, people started to think of better abstractions of writing code. A significant step was the emergence of high-level programming - a situation where the code wrote by a human (*source code*) is not undergoing simple 1:1 mapping to machine code but specific transformations defined by the programming language. A program which transforms source code into machine code is named *compiler*.

High-level programming offers multiple advantages:

- Abstraction - through programming language grammar (e.g. ``x * y`` instead of ``imul eax, esi``) - values can now be named, making them *variables*. The programmer no longer needs to remember what is put where in memory - they need only to remember variable names. Instructions can be represented using symbols and named functions. The code is significantly easier to read and write.
- Portability: a single compiler can generate machine code for multiple different machines from the same source code.
- Safety: writing machine code directly can be extremely error-prone. Programming languages can significantly limit amount of mistakes because compilers can analyze the code with much more information.
- Optimization: compilers can optimize programs during transformation to machine code.

Scripting and interpreted languages
###################################

Some programming languages have been designed to be *interpreted*, not *compiled*. Instead of transforming source code to machine code by a compiler and running an executable, the user launches an interpreter which executes code while reading it. This approach has both advantages and disadvantages. For more information, see https://stackoverflow.com/a/38491646/4818802.

Program execution
#################

At the beginning, programs were sequences of instructions run on softwareless machines. As machines got more advanced, they started to allow to run multiple programs simultaneously and independently. Programs no longer run on "bare metal" but on a specific layer known as operating system (OS). Core OS jobs are separating programs one from another (for security reasons), allocation/distribution of hardware resources (e.g. CPU time, GPU time, available memory) and providing a uniform way of execution for different hardware (so that programs are focused on system, not hardware).

One particulary important feature for programing languages is that many OSes allow 2 forms of machine code: *executables* and *dynamic libraries*.

- An **executable** (``.exe`` extension on Windows, file with "x" attribute on Unix systems) is a file which contains machine instructions and some metadata necessary to run the program.
- A **dynamic library** (``.dll`` on Windows, ``.so`` on Unix systems, ``.dynlib`` on Mac) is also a file which contains machine code but has 1 very significant difference from executables: it has no starting point. Dynamic libraries (also called shared libraries) are portions of machine code intended for reuse by other programs. Dynamic libraries are loaded at runtime, usually at the start of the application that wants to use them. The same library can be used by multiple executables, which saves memory as the OS needs to load it only once. Updating such library will affect all programs that use it.
- A **static library** (``.lib``, ``.a`` and more extensions) is compiled code but not in a format ready to execute. Static libraries are intermediate files produced by program build process, they are usually merged with other compiled code to form executables or dynamic libraries.

    Is running a single, statically linked executable on bare metal no longer a thing?

It still is, mostly in embedded systems where hardware has significantly lower computing power and there are much higher security concerns what is run on the device. Such devices are designed to perform very narrow set of tasks so one of the big reasons for an operating system does not apply. Reducing amount of software layers makes teting easier and increases safety.

    Is it possible to reverse the process? Obtain source code from static library / dynamic library / executable?

Not really. When source code is transformed into machine code, vast majority of information meaningful to humans is lost (unless it's a debug build). Reversing the process is like trying to form the recipe by analyzing the cake. You can find out what main ingredients were used and roughly their proportion, but there is no way to get certainty on all details how it was cooked. A very similar situation is with computer programs. Reversing the build process is known as **reverse engineering** and is most commonly used to develop cheats, security exploits, cracking and performing modifications not intended by program developers. Reverse engineering not only applies to machine code but also to file formats and network protocols.

Today's tools
#############

Nowadays the tools to write computer programs are pretty advanced so you will encounter few more terms:

**IDE** (integrated development environment) - A program (or collection of programs) with multiple features to ease the development of programs. Typical features are:

- smart editor with rich autocomplete and syntax highlighting
- refactoring and code generation tools
- build system integration
- debugger integration
- version control system integration

The C++ world
#############

Major C++ compilers are:

- MSVC (Microsoft Visual C++ compiler) - comes with Microsoft Visual Studio. The recommended compiler by Microsoft for their operating system.
- GCC (GNU compiler collection) - the standard compiler for most GNU/Linux distributions.
- Clang - a newer compiler based on LLVM project, an alternative to both above, default compiler on Mac OS.

GCC and Clang are available on Windows through various ports. For GCC the most popular ones are MinGW-w64 distributions (Minimalist GNU for Windows) which come with ported compilers, linkers, GNU make and other build tools.

There are more compilers but none are as popular as these and most of others are non-free and do not support newer C and C++ standards.

All of mentioned above compilers come together with other necessary tools. All of these tools are command-line programs with no graphic interface so if you have trouble using them it's recommended to use an IDE which automates build tasks.

    Which compiler should I choose?

It doesn't really matter as C++ is a standarized language. Any compiler is required to implement it according to the specification, so you should see no difference in behavior unless you want to use compiler-specific extensions.

If you haven't choosen a compiler yet, I recommend to use GCC or Clang as their diagnostics (error messages) are much better for beginners than the ones produced by MSVC (which is bundled with Visual Studio). Check out TODO link page for details on installation.

Most popular C++ IDEs:

- Visual Studio Code
- Visual Studio
- Qt Creator
- Eclipse CDT
- Code::Blocks
- KDevelop

**Debugger** - a program that simulates execution of other programs. You can pause the execution on choosen places (*breakpoints*) and edit program's state while viewing how it maps to the source code.

**Build configuration** - a set of options passed to the compiler and other tools that create programs. 2 common build configurations:

- debug - the program is built without optimizations and containts extra information for debuggers and other tools
- release - the program is built with optimizations, some code might be disabled (mostly diagnostics for programmers)

Debug builds are mostly useful when developing - debuggers and other tools operate better on such programs. Release builds are for testing and ... releasing them to the target users of the program.

A set of tools used to build a program is known as **toolchain**. The name comes from the fact that usually the output of one tool is the input to another, which forms a sequence of transformations. Intermediate build process products are generally incompatible across toolchains. GCC and Clang share some common parts in their toolchain.

Today's programs often consist of multiple subprojects. A software project, usually intended to be used by other software rather than being an application on its own is a **library**. C++ has its own standard library, which means any C++ program can use it.

----

.. [1] primarily - you can still find remnants of other systems, e.g. base 12 is present in date and time: 12 months, 24 hours, 60 minutes and 60 seconds.
