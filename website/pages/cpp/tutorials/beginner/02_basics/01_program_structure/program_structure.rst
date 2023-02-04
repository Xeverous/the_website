.. title: 01 - program structure
.. slug: index
.. description: structure of a C++ program
.. author: Xeverous

This lesson is aimed at briefly explaining how a C++ program is constructed. A lot of mechanisms mentioned in this lesson will be explained in-depth in later chapters. **You don't need to understand everything here.** It's more of a framework to understand what you need to know.

Hello world
###########

"Hello world" is a minimal program for the given programming language that can be successfully run and its result can be observed. This generally causes hello world programs to contain a single *print* statement and any other code necessary to start and finish the program.

By *print* I mean any form of observable output. Generally it's going to be text displayed in the shell in which the program is run.

.. TODO when to explain shells and program return value execution?

.. cch::
    :code_path: hello_world.cpp
    :color_path: hello_world.color

A C++ program can consist of multiple grammatical constructs so let's go one by one.

The first line is a *preprocessor include directive*. Generally, any line beginning with :cch:`#` will be for a special mechanism called *preprocessor*. Preprocessor isn't for writing instructions to execute, it's more of a mechanism to inform the compiler what is required to run the code that follows. In this case the code is informing the preprocessor to *include* input/output stream library - it will be needed to perform the print statement.

The first line also contains a comment. Comments are text which is ignored by the compiler. Throughout the tutorial, you will encounter lots of comments in the code.

The second line is empty. Whitespace (that is, invisible characters such as spaces, tabs, newlines) are ignored by the compiler (unless within quotes). They are only used to separate code so whether it's 1 or multiple whitespace characters doesn't matter.

Next is the function name plus some extra information (here: just the keyword :cch:`int` which specifies that the function returns an integer). This extra information shouldn't be a concern for now. The significant part is that function names are followed by ``()`` to indicate they are actually functions.

.. admonition:: definition
    :class: definition

    A runnable C++ program must contain exactly 1 global function named ``main``.

Next, there is the function body. Statements are put inside ``{}`` and by the convention, code inside ``{}`` is indented. The function body can consist of arbitrary number of statements (including even 0) and they are executed one by one, top to bottom. Each statement ends with ``;`` which is analogical to ``.`` in human languages.

In the hello world program we have 2 statements:

- The first one performs the print operation. Quoted text is sent to the **st**\ andar\ **d** **c**\ haracter **out**\ put. The syntax used here is a bit different but don't worry - it will be explained soon.
- The second one specifies the result of the function (that is, what function *returns*). Throughout the tutorial, you will use a lot of functions and their results. In the special case of main function, its result is sent back to the operating system where the value :cch:`0` indicates successful execution.

.. admonition:: tip
    :class: tip

    Main function can have its return statement omitted. If it's not present and code reaches end of the function, the behavior is as if it had :cch:`return 0;`.

..

    Couldn't the program just contain the include directive and the print statement? Why a function is needed?

In some programming languages, such thing is actually possible but C++ places special rules on code outside any functions and for historical reasons the program begins execution at the main function. With programs consisting of multiple files containing the source code, this approach is also easier to reason about - there is no need to think what is the order of code between files. We only need to know that the execution starts in the main function, and then this function can call other functions, potentially written in different files.

Printing values
###############

Standard character output (:cch:`std::cout`) accepts many kinds of data. Expressions of different types are separated by ``<<``. :cch:`\\n` is a special control character that denotes new line (AKA line break or line feed character).

.. cch::
    :code_path: printing.cpp
    :color_path: printing.color

Since the first expression in the next statement is also text, the 2 statements can be combined into 1:

.. cch::
    :code_path: printing_combined.cpp
    :color_path: printing_combined.color

Sometimes you might also see :cch:`std::endl` (end-line) used instead of new line character:

.. cch::
    :code_path: printing_endl.cpp
    :color_path: printing_endl.color

The output of this code is the same, however :cch:`std::endl` is not just a new line character. It does something more, something which shouldn't really be done explicitly - it flushes the buffer. Outputting any data to the operating system is a task which requires some extra work (very often system-specific). Buffering the output, while not necessary is very often done for performance reasons. C++ standard streams accumulate data as it is passed in and only output it in bulk when needed. The reason for this is that regardless of data size, communication with operating system is an expensive (in computation and/or time) operation so it should be avoided when possible.

C++ standard streams automatically flush the buffer when necessary, so you shouldn't really be concerned with what is happening underneath. Using :cch:`std::endl` forces it to flush the buffer more than necessary, which generally only slows down the whole program. If you see examples online which use :cch:`std::endl`, you can simply rewrite them to use new line character.

For now, this should be enough to let you print values of different objects. In later lessons, you will learn about standard input (:cch:`std::cin`) and how to create first user-interactive programs that read text.

Watch out for these syntax problems:

- double operator: :cch:`std::cout << << "text";$$$namespace::var_global 2oo 2problem str;`
- unwanted semicolon: :cch:`std::cout << "text"; << "text";$$$namespace::var_global 2oo str1problem 2oo str;`
- operator with no operand: :cch:`std::cout << "text" <<;$$$namespace::var_global 2oo str 2problem;`
- wrong operator: :cch:`std::cout >> "text";$$$namespace::var_global 2problem str;`

Exercise
########

- Edit the hello world program, e.g. change the printed message.
- Introduce random syntax errors to the hello world program (e.g. missing ``;`` or ``<<``) and observe compiler errors.
- Try removing include directive. Observe errors when program is built.
- Try removing the unnecessary return statement.
