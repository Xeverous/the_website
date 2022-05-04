.. title: 03 - enum flags
.. slug: index
.. description: enumeration types used for bit flags
.. author: Xeverous

.. admonition:: note
  :class: note

  This lesson requires knowledge about bit operations (AND, OR, XOR and bit shifts). Skip this lesson if you have skipped the lesson about these operations.

Motivation
##########

Enumerations explained in the previous lesson are a useful abstraction to represent a choice from finite number of predetermined possibilities. How about the case when each option is independent and multiple can be choosen at the same time?

Bitmasks
########

.. TOINCLUDE copy bitmask definition

A good example are file permissions on `POSIX <https://en.wikipedia.org/wiki/POSIX>`_ operating systems.

.. details::
    :summary: POSIX filesystem permissions

    Each object in the filesystem has 3 independent permissions (read, write, execute) for each of (owner, group, others) and few other that specify partially implementation-defined behavior.

    .. admonition:: note
      :class: note

      These settings are often misunderstood. The type of the object (directory, symlink, socket, pipe, etc.) affects how they are interpreted.

      - `explanation of rwx on files <https://www.hackinglinuxexposed.com/articles/20030417.html>`_
      - `explanation of rwx on directories <https://www.hackinglinuxexposed.com/articles/20030424.html>`_

C++17 added a filesystem library to the standard library (based on Boost.Filesystem). Synopsis for https://en.cppreference.com/w/cpp/filesystem/perms:

.. cch::
    :code_path: file_permissions.hpp
    :color_path: file_permissions.color

There are 12 independent settings in total and few aliases for common combinations. How does it work? Each value is a different power of 2 which in binary system will be a different bit. Each bit can be changed and tested separately through bit operations.

Literals have octal (base 8) notation for historical reasons - Unix file permissions have strong convention to be represented in octal. This even includes tools such as ``chmod``.

A more typical definition of a bit mask enumeration uses shifts with increasing values. Since bit shifts are multiplications (or divisions in case of :cch:`>>`) by powers of 2, they end up representing specific bits. Additionally, this clean and expressive way lets very easily add a new enumerator.

.. cch::
    :code_path: shift_example.hpp
    :color_path: shift_example.color

Common mistakes
###############

A value of a bitmask type does not necessarily equal to any of its bits as it can be a sum of multiple ones. The value should not be checked for equality but tested with AND operation:

.. cch::
    :code_path: comparison_mistake.cpp
    :color_path: comparison_mistake.color

Recommendation
##############

There are 2 approaches to bitmask enumerations:

- use :cch:`enum` and use implicit convertion to integer types to apply bit operations
- use :cch:`enum class` and overload bit operators to support required operations

The second requires more work to setup but is safer in practice (no implicit convertions and no name clashes). I would go for the first one only if there is a very frequent need to use enumerators as integers.
