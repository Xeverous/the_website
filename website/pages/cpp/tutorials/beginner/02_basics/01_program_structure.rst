.. title: 01 - program structure
.. slug: 01_program_structure
.. description: structure of a C++ program
.. author: Xeverous

This lesson is aimed at briefly explaining how a C++ program is constructed. A lot of mechanisms mentioned in this lesson will be explained in-depth in later chapters. **You don't need to understand everything here.** It's more of a framework to understand what you need to know.

Hello world
###########

"Hello world" is a minimal program for the given programming language that can be successfully run and it's result can be observed. This generally causes hello world programs to contain a single *print* statement and any other code necessary to start and finish the program.

By *print* I mean any form of visual output. Generally it's going to be text displayed in the shell in which the program is run.

.. TODO when to explain shells and program return value execution?

.. TOCOLOR

.. code::

    #include <iostream> // include directive

    int main() // function name + extra info
    { // function body begins here
        std::cout << "hello, world\n"; // the print statement
        return 0; // return statement
    } // function body ends here

A C++ program can consist of multiple grammatical constructs so let's go one by one.

The first line is a *preprocessor include directive*. Generally, any line beginning with :cch:`#` will be for a special mechanism called *preprocessor*. Preprocessor isn't for writing instructions to execute, it's more of a mechanism to inform the compiler what is required to run the code that follows. In this case the code is informing the preprocessor to *include* input/output stream library - it will be needed to perform the print statement.

The first line also contains a comment. Comments are text which is ignored by the compiler. Throughout the tutorial, you will encounter lots of comments in the code.

The second line is empty. Whitespace (that is, invisible characters such as spaces, tabs, newlines) are generally ignored by the compiler. They are only used to separate code so whether it's 1 or multiple whitespace characters doesn't matter.

Next is the function name plus some extra information (here: just the keyword :cch:`int`). This extra information shouldn't be a concern for now. The significant part is that function names are followed by ``()`` to indicate they are actually functions.

.. admonition:: definition
    :class: definition

    A C++ program must contain exactly 1 global function named ``main``.

Next, there is the function body. Statements are put inside ``{}`` and by the convention, code inside ``{}`` is indented. The function body can consist of arbitrary number of statements (including even 0) and they are executed one by one. Most statements you will write will end with ``;`` which is analogical to ``.`` in english.

In the hello world program we have 2 statements:

- The first one performs the print operation. Quoted text is sent to the **st**\ andar\ **d** **c**\ haracter **out**\ put. The syntax used here is a bit different but don't worry - it will be explained soon.
- The second one specifies the result of the function (that is, what function *returns*). Throughout the tutorial, you will use a lot of functions and their results. In the special case of main function, its result is sent back to the operating system where the value :cch:`0` indicates successful execution.

.. admonition:: tip
    :class: tip

    Main function can have its return statement omitted. If it's not present and code reaches end of the function, the behavior is as if had :cch:`return 0;`.

..

    Couldn't the program just contain the include and print lines?

In some programming languages, such thing is actually possible but C++ places special rules on code outside any functions and for historical reasons the program begins execution at the main function. With programs consisting of multiple source code files, this approach is also easier to reason about - we don't need to think what is the order of code between files. We only need to know that execution starts in main function, and then it can call other functions (potentially written in different files) as it goes forward.

Exercise
########

- Edit the hello world program, e.g. change the printed message.
- Introduce random syntax errors to the hello world program (e.g. missing ``;`` or ``<<``) and observe compiler errors.
- Try removing include directive. Observe errors when program is built.
- Try removing the unnecessary return statement.
