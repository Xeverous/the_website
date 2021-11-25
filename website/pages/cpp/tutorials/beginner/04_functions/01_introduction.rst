.. title: 01 - introduction
.. slug: 01_introduction
.. description: introduction to functions
.. author: Xeverous

You definitely have encountered the *function* term before. It's very likely you already have a rough image what a function is.

In mathematics, a function is a relation between two sets that associates each element of the first set to exactly one element of the second set.

In programming, a function is a **reusable piece of code** that given certain set of inputs *returns* (produces) an output (an object).

In both mathematics and programming:

- A function always *returns* a single value. No matter how many inputs a function gets, it always produces a single output.
- A function can *return* the same value for multiple, different inputs. For example, a square function *returns* 4 for both 2 and -2.
- A function may receive (invalid) inputs for which there is no result:

  - In mathematics: argument out of domain, logic error
  - In programming: any kind of error or undefined behavior

In programming:

- A function can return different value even if given the same input. For example, a date/time function can return different date/time each time it's *called* (used).
- A function can have side effects, they are never considered to be function's output.

.. admonition:: note
    :class: note

    Functions are one of fundamental programming elements. They allow to build complex programs without code duplication and letting to focus on small tasks one at a time (divide and conquer). In practice, almost every function calls other functions forming deep chains of code reuse.

..

    What if I really want to return multiple objects? I can imagine various situations where some computation could produce multiple results.

Functions by their core definition always return a single object. The trick is that the object can be of any type.

- In mathematics, a function can return a complex number or a matrix. These can hold multiple numbers.
- In programming, a function can return an object of user-defined type. Such type can consist of multiple types and hold many subobjects.

.. TODO structs when?

Syntax
######

Vast majority of functions are defined using the syntax below. Other ways (lambda expressions and member functions) will be presented later.

In order:

- return type
- function name
- function parameters
- function body

.. cch::
    :code_path: 01_introduction/syntax.cpp
    :color_path: 01_introduction/syntax.color

.. admonition:: note
    :class: note

    Unlike conditional statements and loops, a function body must always contain ``{}``.

.. admonition:: note
    :class: note

    Functions are called (used) by providing arguments between ``()``.

Functions create own scope for their local objects (objects defined inside functions), these objects are destroyed when the function returns - only returned value is retained. If the caller does not use the result (e.g. :cch:`f(x);` instead of :cch:`y = f(x);`) function still works the same but the returned data is lost.

There is no relation between names of function parameters and names of objects that are passed to the function. The compiler only cares whether types match. Names are only an abstraction for the programmer so that it's possible to express what should be done inside the function. Function call expressions are a way to connect separate parts of code.

Returning
#########

Returning is the act of providing function's result. The type of the object at the :cch:`return` statement should be the same as function return type or be implicitly convertible to it.

.. admonition:: definition
    :class: definition

    A function should never reach the end of its body without :cch:`return` statement.

The function below does not return on all control flow paths. If at runtime this function is called with zero, it will cause undefined behavior.

.. cch::
    :code_path: 01_introduction/missing_return.cpp
    :color_path: 01_introduction/missing_return.color

..

    Why such functions are allowed then? Can't the compiler check that a function can finish without returning?

The compiler can not analyze all possible operations and simulate all potential function usages - there are simply too many of them and many of them may be impossible or simply never happen. For these reasons, in the past it was generally accepted that a function may have hypothetical control flow path that results in reaching end of its body without hitting any return statement. Over time, it turned out that such approach is generally unsafe (bug prone) and results in code that is hard to read and reason about.

The new approach is simpler and more safe: **a function should cover all of its control flow paths (even if they seem to never be possible)**. The compiler can not simulate the function, so it simply checks whether all branches of any conditional instructions end in return statements. For backwards compatibility, C and C++ still allow functions with missing return statements, but compilers issue a warning.

Remember that main function has an exception: if control flow reaches its end, it's assumed to be :cch:`return 0;`.

Void functions
##############

Functions can have return type specified as :cch:`void` which means they return no data. This is very useful if the function is used for its side effects:

.. cch::
    :code_path: 01_introduction/void_return.cpp
    :color_path: 01_introduction/void_return.color

Such functions do not need to use :cch:`return` as there is no data to send back to the caller. If you want to exit such function prematurely (eg under specific condition), you can always write :cch:`return;`.

Function size
#############

There have been many guidelines on what's a good size for a function. 20, 50 and even 100 lines of code. **The core principle is that a function should perform exactly 1 task.** If you see an opportunity to split the task into smaller ones, do it even if the function is used only once. Such code is easier to read and test. Functions should be like Lego bricks - they should very easily compose into larger constructions and be easy to modify.

The same principle applies to the amount of function parameters. 4 is the reasonable maximum amount, however specific algorithms sometimes use up to 6. The more parameters a function has, the harder it's to understand and the more likely it has bugs and more likely the function can be refactored into multiple smaller ones.

There is no lower limit on size and arguments. Many useful functions can be as simple as 1 line:

.. cch::
    :code_path: 01_introduction/one_line.cpp
    :color_path: 01_introduction/one_line.color

.. TODO constexpr functions when?

Terminology
###########

A common mistake is to assume that function *arguments* means the same as function *parameters*.

- Function parameters are what function definition expects to be passed in (seen from inside the function).
- Function arguments are objects that are given for specific function call (seen from outside of the function).

Since both must match in order for the code to work, these terms usually mean the same thing. But if they don't, an example compiler error could mention that a specific *argument* does not match a type of a specific *parameter*.

Implementation
##############

Conditional statements and loops are jumps ahead/behind in machine code. Because compiled functions are separate blocks of reusable machine code, there must be 2 jumps for each function: one in (the call instruction), one out (the return instruction). The same function can be called from different places so it also needs to know where to jump back when it returns - the execution should continue in the place where the function was called.

In the example below, the first function is called from 2 other functions. You should be able to determine what will be the program's output. If not - compile, run and analyze the output. You should be able to build a mental image (a graph) how function calls interact.

.. cch::
    :code_path: 01_introduction/nested_calls.cpp
    :color_path: 01_introduction/nested_calls.color

The call stack
##############

When a function is called, the place where it should return is pushed onto the *stack*. This data is also accompanied by function arguments (unless the compiler decided to pass them through registers). Stack is a special memory region where function-local data is stored. Simplified diagram:

.. image:: https://upload.wikimedia.org/wikipedia/commons/8/8a/ProgramCallStack2_en.png
    :alt: program call stack

*Active frame* is the range of stack memory that holds information relevant to the function currently being executed. It contains return address (previous value of *stack pointer*) and any local data (arguments and objects defined inside the function). When this function returns, it will pop current frame (remove it from the stack), return to frame N-1 and change *stack pointer*.

.. image:: https://upload.wikimedia.org/wikipedia/en/6/60/ProgramCallStack1.png
    :alt: program call stack after return

The mechanism can now repeat: the current function can call another function (which would push new frame with return address equal to current *stack pointer*) or return (which would pop current frame and revert *stack pointer*). As the program is executed and functions are called and return, the stack goes up and down constantly reusing stack space.

The stack operates in LIFO manner (last in, first out) - latest objects put on top are also the first objects to be removed.

The main function would be the closest one to the stack origin (the bottom), since this is the first function to be called within a program. This also means that the main function is the last function to return.

    Why is the stack upside down? Shouldn't the origin be at memory address 0?

It could be, but that's how some (if not most) systems implement the stack. The stack memory moves downward from the end and the *heap memory* moves upward from the beginning. The memory in the middle can become whatever is needed.

Call stack in tools
===================

Various programming tools (especially debuggers) work in terms of inspecting *function call stack*. Below is an example of a possible call stack printed by `AddressSanitizer/LeakSanitizer <https://en.wikipedia.org/wiki/AddressSanitizer>`_ when it detects a *memory leak* bug:

.. code::

    ==26475==ERROR: LeakSanitizer: detected memory leaks

    Direct leak of 5 byte(s) in 1 object(s) allocated from:
        #0 0x44f2de in malloc /usr/home/hacker/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:74
        #1 0x464e86 in baz (/usr/home/hacker/a.out+0x464e86)
        #2 0x464fb4 in main (/usr/home/hacker/a.out+0x464fb4)
        #3 0x7f7e760b476c in __libc_start_main /build/buildd/eglibc-2.15/csu/libc-start.c:226

.. admonition:: note
    :class: note

    Main function may not be actually first due to implementation-specific reasons. Many platforms require extra work to be done before actual code can run. In most situations (without sanitizers) on GNU/Linux systems the first function is named ``_start`` but other magic names (starting with ``_``) can appear too.

The call stack alone is often enough to identify the problem. Through this information alone, you know which function called which and through that you can reason about control flow paths that the program has gone through. The source of a bug is usually found just before first unexpected function call.

Stack overflow
==============

.. admonition:: definition
    :class: definition

    A situation when stack memory is exhausted and an attempt is made to occupy even more is **stack overflow**. This has undefined behavior.

On GNU/Linux systems, Bash shell has a built-in command that can be used to check various resource limits, including stack memory. Example done on a 64-bit PC:

.. code::

    $ ulimit -a
    core file size          (blocks, -c) 0
    data seg size           (kbytes, -d) unlimited
    scheduling priority             (-e) 0
    file size               (blocks, -f) unlimited
    pending signals                 (-i) 15450
    max locked memory       (kbytes, -l) 65536
    max memory size         (kbytes, -m) unlimited
    open files                      (-n) 1024
    pipe size            (512 bytes, -p) 8
    POSIX message queues     (bytes, -q) 819200
    real-time priority              (-r) 0
    stack size              (kbytes, -s) 8192
    cpu time               (seconds, -t) unlimited
    max user processes              (-u) 15450
    virtual memory          (kbytes, -v) unlimited
    file locks                      (-x) unlimited

8 MiB doesn't seem to be much but in reality, unless forced on purpose, stack overflow is hard to achieve. Most complex programs I have seen nest few hundred function calls. Stack pointer is the same size as the architecture (8 bytes on 64-bit CPU), adding this to other control data and average few function parameters and average few local variables we get a guesstimate of 64-128 bytes of stack data per function. Assuming few hundred nested function calls, we get at most few hundred kilobytes. That's far less than 8 MiB.

    How then can programs process gigabytes (or even more) of data?

So far everything done in the tutorial was using *local variables* with *automatic storage* which use *stack memory*. Any large data is pretty much always allocated dynamically, using *heap memory*. Functions can work on this data but the data itself is allocated separately. This is related to indirect mechanisms (e.g. arrays, references, pointers) where a single variable (allocated on the stack) can refer to a huge block of memory (allocated on the heap). This single variable can then be used to refer to an arbitrary amount of objects.

    How is stack and heap memory related to RAM?

Both are a part of RAM, where stack memory is a small selected region. The selection (for each program and for itself) is made by the operating system. RAM itself is only a one huge array of memory cells with nothing predefined. It's up to the software (especially OS) to form some structure and give meaning to specific ranges of memory cells.

Processors contain SRAM (static RAM) which is a much faster memory than main RAM (dynamic RAM or DRAM). SRAM is typically used for the cache and internal registers of a CPU. Cache is closely related to currently executed function and its data so very often it will contain copies of the stack memory.

Recommendations
###############

- Unless there is a better reason, function parameters should be ordered in decreasing importance (most important parameters first).
- Variables are data. Functions are tasks. Variables should be named as nouns and functions as verbs.
- Before you write a function for some task, check whether it's not already in the standard library. A lot of common mathematical operations are already available in `cmath header <https://en.cppreference.com/w/cpp/header/cmath>`_.

Exercise
########

- Compile the function with missing return statement and observe any compiler warnings. Don't try calling it - you should never expect anything meaningful from undefined behavior.
- Remember Collatz conjecture from the control flow chapter? Now write a function that given a number, returns the next number. Modify the program from that lesson to use this function.
