.. title: tabs vs spaces
.. slug: tabs_vs_spaces
.. date: 2020-08-21 00:09:52 UTC+02:00
.. description: tabs vs spaces - how to do both correctly
.. author: Xeverous

preface
#######

This article is not aimed to convince you to any of the sides. You very likely already have a very strong own opinion what is better. This article goals are:

- to list advantages/disadvantages of both
- to present common mistakes

Nothing can be worse than someone using one of the styles incorrectly and/or having no arguments for choosing such style.

spaces
######

Pros:

- Simpler to understand and from what I have seen, people make less mistakes with it.
- Well-suited for fixed showcases like prints and presentations - basically where code is treated as an image instead of text. Sufficient amount of spaces will guarantee that indents are clearly visible.

Cons:

- Many editors do not offer convenient behavior when code is indented using spaces. They still require multiple key presses for various editing tasks.
- It is easy to make off-by-one typos. Especially if you indent by 4 or more spaces and/or lack good editor support.
- People will argue how many spaces it should be. Most popular are 2, 4 and 8. There is no such problem with tabs.

tabs
####

Pros:

- The rendering is flexible. Everyone can set displayed tab length to their preference. If you think this is a problem and not an advantage, you are making one of common mistakes - read further.
- Less characters to type, much harder to misalign code off-by-one.

Cons:

- If you have a line limit, you will need to assume certain tab length in calculations.
- May cause interoperatibility issues with other (non-editing) tools that consume code to display it (usually partially) in a different form. Problematic if code is embedded inside other code.

how tabs work
#############

For the purpose of this article:

- **L** will represent configured tab length.
- spaces will be represented with ``.``.
- tabs will be represented with ``--->`` (where the amount of ``-`` may change depending on L and *tab stops*).

mistakes
########

misunderstanding tab stops
==========================

A common misconception is that tabs have fixed width, equal to L. This is false. Tabs have width *up to L* - tabs stop at multiplies of L, called *tab stops*. Example with L set to 8:

.. code::

    ------->------->Y
    ------->XXXX--->Y
    abc---->X------>Y
    abcd--->X------>Y
    abcde-->X------>Y
    abcdef->X------>Y
    abcdefg>X------>Y
    abcdefgh------->X------->Y

In the first line, tabs do have length equal to L. But in other lines, they are truncated by the presence of other characters. Once the length of them reaches L (which is the case of ``abcdefgh``), they "push" next tab character to the next tab stop.

using tabs elsewhere than line start
====================================

Tabs, if used, should be present only at the beginning of the line. Once any other character has been used, tabs should never appear. The following example showcases that you can not consistently use tabs for alignment:

.. code::

    --->fn(x+1,>y,->z);
    --->fn(x,-->y+1,z);
    --->fn(x,-->y,->z+1);

It looks even worse if L is changed to 8:

.. code::

    ------->fn(x+1,>y,----->z);
    ------->fn(x,-->y+1,z);
    ------->fn(x,-->y,----->z+1);

assuming tab length
===================

This is another mistake. **Tabs do not have predefined length and you should not write code assuming any.** Example:

.. code::

    ------->long_function_call(arg1, arg2,
    ------->------->------->...arg3, arg4,
    ------->------->------->...arg5, arg6);

The code above assumes L is 8, which makes the same code badly formatted if someone has L set to 4:

.. code::

    --->long_function_call(arg1, arg2,
    --->--->--->...arg3, arg4,
    --->--->--->...arg5, arg6);

Some people use this as an argument towards using spaces - wrong. This is not valid argument, because this is simply incorrect usage of tabs. The correct use is as follows (you can see it works regardless of L):

.. code::

    --->long_function_call(arg1, arg2,
    --->...................arg3, arg4,
    --->...................arg5, arg6);

    ------->long_function_call(arg1, arg2,
    ------->...................arg3, arg4,
    ------->...................arg5, arg6);

**Tabs are used for indent, spaces for alignment:**

- Tabs prepend the code, because it is a part of some outer scope. The indent size may change (depending on L), but all lines in the same scope will have the same indentation.
- Spaces align function arguments, because we want further arguments to be shifted specific number of characters. There is no indent due to scope, we simply align characters using fixed-length whitespace character (space).

mixing styles
=============

Any mixed style will fall into assumption of L. Example:

.. code::

    --->func();
    ....func();

After changing L to 8:

.. code::

    ------->func();
    ....func();

This is bad - code on the same scope has different visible indentiation.

summary
#######

- Use tabs only at the start of the line. Never after any other character (such lines are colored red in ``git diff`` output).
- Never assume any length. Use tabs to indent and spaces to align.
- If you are writing literal strings, prefer to write tabs using escaped form (e.g. ``\t``) instead of directly in source - directly written tabs may uncontrollably shift tab stops depending on changes in other parts of the string.
- Configure editor to correctly stick to your choosen style.
