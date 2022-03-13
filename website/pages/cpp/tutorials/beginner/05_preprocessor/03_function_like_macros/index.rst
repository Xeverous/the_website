.. title: 03 - function-like macros
.. slug: index
.. description: function-like macros
.. author: Xeverous

Here you can see a function-like macro used within regular code:

.. cch::
    :code_path: max.cpp
    :color_path: max.color

Doesn't look very appealing, does it? Why use preprocessor text replacement when such macros can easily be written as regular C++ code (usually with the help of templates)? The standard library already offers :cch:`std::max`. This is why macros with no solid justification are frowned upon in C++ (in C it's a very different story - there are far less language features).

Using macros inside preprocessor directives is fine - this is the bread and butter of writing multiplatform and multi-build-configuration code in C and C++. But when used directly within code, they can significantly impact readability apart from other issues explained in this lesson.

.. admonition:: tip
  :class: tip

  Avoid using macros within regular code. In most cases, the problem can be solved with templates or other language features. Use macros when you are sure there is no better alternative.

Multiple evaluation
###################

Let's revisit the previous example but with a small change:

.. cch::
    :code_path: multiple_evaluation.cpp
    :color_path: multiple_evaluation.color

Now you should see the problem - because the preprocessor operates on text, it often impacts code in very unpleasant ways:

- the variable :cch:`x` is actually incremented twice (or not, depending which value is larger)
- the function :cch:`f` may be called twice (at best a redundant operation, at worst the program will have different behavior)

For this reason, the convention is that macros should be called in a such way that there are no side effects. The input expressions should be as simple as possible to avoid accidentally invoking unwanted operations. Sometimes this means you will have to create a local variable that holds intermediate result to avoid putting computational expressions into macros.

Changed evaluation
##################

Another problem - macros may unintentionally work differently due to operator precedence:

.. cch::
    :code_path: changed_evaluation.cpp
    :color_path: changed_evaluation.color

In such cases the workaround is simple - just **correct macro definition to always enclose given text in parentheses**:

.. cch::
    :code_path: changed_evaluation_fixed.cpp
    :color_path: changed_evaluation_fixed.color

In fact, the macro from previous example should look like this:

.. cch::
    :code_path: max_fixed.cpp
    :color_path: max_fixed.color

Pretty dumb, isn't it? The preprocessor isn't very clever. Another reason to avoid macros.

The mechanism in detail
#######################

Each time a macro is invoked, the preprocessor expands it which may contain other macros inside. This allows further macro nesting and some powerful preprocessor tricks.

The preprocessor operates on text but more precisely on *tokens*. A *token* is the smallest entity made from text that forms something that has a meaning: an identifier, a number literal, a string literal, an operator and such. Whitespace characters (space, tab, newline and such) are used to separate tokens that would otherwise form a single, different token (e.g. :cch:`constint$$$var_local` identifier vs :cch:`const int` keywords).

3 tokens have special status for the preprocessor: ``,`` (separates arguments) , ``(`` and ``)`` (encloses macro and arguments). A macro argument can never contain an unmatched parenthesis or a comma that is not surrounded by matched parentheses but because preprocessor operates on tokens, it's possible to provide an empty-token argument.

.. cch::
    :code_path: identity.cpp
    :color_path: identity.color

Other characters do not have this special status and thus the preprocessor treats ``<>``, ``[]`` and ``{}`` like any other. The macro argument does not even need to have them matched as the preprocessor doesn't test matching apart for ``()``.

Stringification
###############

cppreference:

    In function-like macros, a ``#`` operator before an identifier in the *replacement-list* runs the identifier through parameter replacement and encloses the result in quotes, effectively creating a string literal. In addition, the preprocessor adds backslashes to escape the quotes surrounding embedded string literals, if any, and doubles the backslashes within the string as necessary. All leading and trailing whitespace is removed, and any sequence of whitespace in the middle of the text (but not inside embedded string literals) is collapsed to a single space.

Because the operation effectively turns an expression to a string, it's often called "stringification", "stringization" and such.

.. admonition:: warning
  :class: warning

  If the result of stringification is not a valid string literal, the behavior is undefined. In pracice all implementations known to me output a clear error.

This feature allows generating code that can both evaluate the expression as it is but also treat it as a string:

.. cch::
    :code_path: print.cpp
    :color_path: print.color

.. admonition:: tip
  :class: tip

  Reminder: adjacent string literals are concatenated (after preprocessing phase), thus there is no need for :cch:`<<` before :cch:`" = "$$$str`.

Because macro expansion proceeds recursively and there is a limited set of operations that can be done on each expansion, in some cases certain operations need to be delayed in order to work properly. For this reason, stringification is often not used directly but through another macro:

.. cch::
    :code_path: stringize.cpp
    :color_path: stringize.color

Output:

.. code::

    VALUE = 3
    x + y = 3

Token pasting
#############

The preprocessor operates on tokens and thus separate tokens remain separate even if as sequences of characters they would look like a single token:

.. cch::
    :code_path: separate_tokens.cpp
    :color_path: separate_tokens.color

If concatenation of separate tokens into a larger token is desired, there is a special preprocessor operator :cch:`##` that merges 2 adjacent tokens. The resulting token made from concatenation of characters from both input tokens must be valid - you can not create invalid tokens or any comment tokens (comments are removed from code before the preprocessor is run).

.. admonition:: warning
  :class: warning

  If the result of :cch:`##` is not a valid token or a comment token, the behavior is undefined. In pracice all implementations known to me output a clear error.

Similarly to stringification, the operation is commonly used through another macro to prevent situations where a macro name (instead of its expansion) would be used.

.. cch::
    :code_path: concat.cpp
    :color_path: concat.color

Additional conventions
######################

Some macros generate a lot of code - much more than a single subexpression or even entire statement. This causes few problems:

- If the macro creates some local objects, their names might clash between usages of the macro and/or other code.
- If the macro produces multiple statements, it can significantly impact code readability - it's not a function or other C++ construct and a human reading code may have trouble understanding how to connect other code with it. Additionally, if such macro is used under braceless :cch:`if` or other control flow statements, only the first statement from the macro expansion is covered by it.

A common solution to both problems is to enclose generated code within a do-while loop that runs exactly once. This guards the scope, makes a single statement and additionally allows ``;`` to be used after macro call to make it look as a single statement.

.. admonition:: tip
  :class: tip

  Reminder: do-while loops end with ``;``.

.. cch::
    :code_path: do_while_macro.cpp
    :color_path: do_while_macro.color

In some cases macros have to be used at global scope (when they generate classes, enumerations or any other non-imperative code). In such situation they can add a dummy code like :cch:`void no_op()$$$keyword func()` (no operation) at the end so that ``;`` immediatelly following the macro expansion forms valid, unused function declaration.

Problematic macros
##################

One particular header is known for the trouble it was causing in the past - :cch:`<windows.h>$$$0pp_header`. It was defining a macro just like the maximum one in this lesson, except it was named ``max``, not ``MAX``. It caused many accidental compilation errors because ``max`` is a popular name for functions and objects. :cch:`std::max(a, b)$$$namespace::func(var_local, var_local)` had to be written as :cch:`(std::max)(a, b)$$$(namespace::func)(var_local, var_local)` to avoid the macro call (the code as C++ still works but extra parentheses around the function name prevent preprocessor from considering it a macro call). This is a great example why macros and only macros should be written as UPPERCASE - otherwise there is a risk corrupting the code through accidental text replacements.

The problem is long gone since Microsoft made changes to :cch:`<windows.h>$$$0pp_header`. If the header is included while :cch:`WIN32_LEAN_AND_MEAN$$$macro_ref` is defined, it avoids including a lot of (mostly older) stuff, many lowercase and CamelCase macros in particular. Pretty much every new project that is compiled for windows will define this identifier to prevent nasty macros from destroying their code.

- https://devblogs.microsoft.com/oldnewthing/20091130-00/?p=15863
- https://stackoverflow.com/questions/11040133/what-does-defining-win32-lean-and-mean-exclude-exactly

If when writing a project you encounter a similar issue (from a different header), you have few options:

- rename your code
- just :cch:`#undef` it if it's not needed in your code (kind of bad if someone includes your headers and expects the macro to be present though)
- (if possible) organize your code so that the nasty includes are only present in specific *source files*
- (if there is no better way) use compiler extensions like :cch:`#pragma push` and :cch:`#pragma pop` to temporarily change preprocessor state

More tricks
###########

There are few more preprocessor features, all are pretty simple in theory but practice shows their real power is obtained by abusing preprocessor mechanism as much as possible. Because they are only used within certain niche applications and with each newer C++ standard there are less and less justified usages of macros, I'm not going to cover them in detail.

Variadic macros
===============

If a function-like macro is defined with ``...``, it's a *variadic macro*. ``...`` accepts any 1+ number of arguments (changed to 0+ in C++20) and can output them with :cch:`__VA_ARGS__` as a comma-separated list of tokens. Since C++20 there is also :cch:`__VA_OPT__(content)$$$macro_ref(spec)` which expands *content* only if ``...`` is non-empty.

X macros
========

Basically macros that abuse other macros for maximum power in code generation. Explanation on https://en.wikipedia.org/wiki/X_Macro.

One particular usage that is still relevant in C and C++ is generation of :cch:`enum` together with functions that convert between enum type and strings. Example such library: https://github.com/aantron/better-enums.

Maximum abuse
=============

`Boost.Preprocessor <https://www.boost.org/doc/libs/release/libs/preprocessor/doc/index.html>`_ is a library for metaprogramming in C and C++ through preprocessor.
