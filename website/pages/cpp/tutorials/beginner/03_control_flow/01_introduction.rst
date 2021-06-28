.. title: 01 - introduction
.. slug: 01_introduction
.. description: introduction to structured programming
.. author: Xeverous

I'm pretty sure you have encountered flowcharts like the one below, probably countless times.

.. image:: https://upload.wikimedia.org/wikipedia/commons/9/91/LampFlowchart.svg
    :alt: lamp flowchart

The core thing that makes them dynamic are blocks which ask for an aswer. Depending on it, a different path should be followed. Some of flowcharts may even form loops (arrow points to some previosly visited block) so that you traverse the same path multiple times (each time doing something slightly different) untill the condition no longer holds and then move forward (to yet unvisited blocks).

Similarly, one of key aspects of computer programs is the ability do something *depending* on something else. It seems to be so obvious yet this chapter has multiple lessons. Is this really that hard?

Why control flow is not just jumps
##################################

In the machine code, we can differentiate 4 types of instructions:

- reads
- writes
- computations
- jumps

All that the processor is doing is simply executing instructions one after another and occasionally jumping to a different instruction than the next if some condition has been satisfied.

The same thing could be also done in programming - but - imagine a 10000+ line program containing thousands of instructions and hundreds of statements like "if x is 0, jump to line ...". Humans get lost at roughly 7 (+/-2) things\ [1]_ they need to focus on. Such program would be orders of magnitude more complex than any human could ever grasp, yet today we have programs containing millions of lines of code and they are still developed further.

When first high-level programming languages appeared (reminder: low-level means 1:1 transformation of source code to machine code) the abstraction for a jump was very simple: :cch:`goto` keyword or something similar. You just wrote a condition and if it was true, the program would jump to a specified line or label.

As you may guess, it was extremely easy to get lost within such program. After just few :cch:`goto` statements, it was almost impossible to add any new functionality without breaking behavior of existing functionality. There was clearly a need for something more, something that could abstract program's control flow structure so that programmers don't get lost in a web of jump statements.

Structured programming
######################

Programs you have seen so far were either exclusively or mostly imperative. They simply had a list of statements that were executed in order of their appearance.

Continuing to write programs in such style with the addition of jump statements will change their understandability from trivial to unimaginable. Thus, I won't showcase how to use :cch:`goto` in C++ as it's almost inherently harmful. It's so harmful that:

- :cch:`goto` is pretty much never used in C++, almost universally hated\ [2]_ and presented as a source of problems.
- :cch:`goto` is used in C only with specific control flow patterns. Such patterns are very common in C++ too but they can be done without :cch:`goto` - in C++ the compiler can do automatically what needs to be done manually with :cch:`goto` in C.
- Majority of newer programming languages do not have :cch:`goto` and thus never allow *unstructured control flow*.

So what's the deal with structured programming? It's all about having some framework that improves program clarity and maintability by usage of *structured control flow statements*.

Theorem
#######

The *structured program theorem*\ [3]_, also called the *Böhm–Jacopini theorem* states that a program can compute any computable function if it combines subprograms in just three specific ways:

- sequence: executing subprograms (statements) in order of their appearance
- selection: executing 1 of 2 subprograms based on a boolean value
- iteration: repeated execution of a subprogram as long as a boolean value is true

For vast majority of programming languages:

- The first point doesn't require any explanation, it's just the simplest form of imperative code.
- The second point is represented as *conditional statements*.
- The third point is represented as *loops*.

Apart from these, C++ also contains one more structured form of control flow - exceptions. However, **exceptions are intended exclusively for error handling** and thus they won't be showcased in this chapter.

If you feel overwhelmed by this theory - just move on to the next lesson. For many it's easier to see actual examples than to read theoretical lecture.

----

.. [1] https://en.wikipedia.org/wiki/The_Magical_Number_Seven,_Plus_or_Minus_Two
.. [2] https://en.wikipedia.org/wiki/Goto#Criticism
.. [3] https://en.wikipedia.org/wiki/Structured_program_theorem
