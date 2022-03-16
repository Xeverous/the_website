.. title: 03 - identifiers
.. slug: 03_identifiers
.. description: C++ identifiers
.. author: Xeverous

One particular advantage of today's programming languages is that they allow to abstract where certain values are placed in memory. Instead of using machine's registers or memory cell names, we can name variables as we like and use these names. This significantly simplifies reading code; the actual memory placement is decided by the compiler (if two variables are used at the same time they will obviously get different memory locations).

Everything than can be later referred to through its name has an **identifier**. It's the name of the entity. Variables and functions will be simplest kinds of entities you will use right now.

Identifiers can consist of:

- lowercase letters (latin: ``a`` - ``z``)
- uppercase letters (latin: ``A`` - ``Z``)
- underscore symbol (``_``)
- digits (``0`` - ``9``), except digit as first character

...and many more possible characters from unicode - their rules are quite complex but if english and latin alphabet are not your native, you should be fairly sure what in your native writing system can be considered a letter and what a whitespace character. Just be aware that pretty much all code is written using latin alphabet only; if any other writing system appears it's usually exclusively inside comments (that is, no code uses non-latin identifiers).

.. admonition:: definition
    :class: definition

    All identifiers in C++ are case-sensitive. They must always be written exactly the same.

Example valid identifiers:

- ``func``
- ``x1``
- ``x2``
- ``y``
- ``foo_bar``
- ``a_b_c_d_e_f``
- ``XABCDX``
- ``WeIrD_nAmE``

Example invalid identifiers:

- ``if`` - this is a language *keyword*
- ``1x`` - identifiers can not start with a digit
- ``x@y`` - many symbols (including ``@``) can not be used inside identifers

Additionally, the C++ standard reserves following names (you should not use them):

- ``_X*`` - anything beginning with an underscore followed by an uppercase letter.
- Global ``_*`` - anything beginning with an underscore, placed at *file/namespace scope* (more on scopes later).
- ``*__*`` - anything containing 2 consecutive underscores.
- `Keywords <https://en.cppreference.com/w/cpp/keyword>`_.

Keywords
########

Keywords are identifiers which have special meaning, e.g. :cch:`if`, :cch:`else`, :cch:`const`. They are a part of the language grammar and can not be used to name entities. As you go through the tutorial, you will learn C++ keywords over time. If you accidentally write one while naming something, your code editor should differentiate it. Obviously you won't immediately remember all keywords - just be aware that there is a chance you might need to come up with a different name for a variable if you clash with a keyword.

Name conflicts
##############

In many situations it's possible to use the same identifier for different entities. They usually will be distinguished by syntax or scope. Unless otherwise noted, it's generally advised to avoid giving different things identical identifiers. Depending on the situation, the rules for distinguishing can be pretty complex.

Styles
######

As identifiers can not contain whitespace characters, few core naming styles have been established, these conventions are broadly used in the entire IT, not just programming.

- ``lowercase_name_style`` (sometimes referred to as snake case)
- ``UPPERCASE_NAME_STYLE``
- ``PascalCaseNameStyle`` (commonly referred to as upper camel case)
- ``camelCaseNameStyle`` (commonly referred to as lower camel case)

Generally, it's bad to mix these styles - any of the following names are against convention:

- ``Account_Manager``
- ``Accountmanager``
- ``PrintHTTPDocument``
- ``print_HTTP_document``

correct names:

- ``account_manager``
- ``AccountManager``
- ``accountManager``
- ``print_http_document``
- ``PrintHttpDocument``
- ``printHttpDocument``

C++ (following C convention) uses ``UPPERCASE_NAME_STYLE`` for *macros* and ``lowercase_name_style`` for almost everything else. All tutorial content on this website uses relevant styles - just simply follow them.

Conventions
###########

Apart from underscore style, C++ also has a lot of conventions regarding variables with certain purpose. For example, if you are iterating over multiple elements, a variable containing the index of the current element will very often be named ``i``. If a function is supposed to create an object from (usually multiple) smaller objects, it's name will typically begin with ``make_``. Throughout the tutorial, you will find many examples featuring idiomatic code and they will very often present commonly used identifiers.

All of conventional identifiers have been described in `naming article <link://filename/pages/cpp/utility/naming.rst>`_. But don't try to memorize them now - you will start to remember them with no effort once you start writing code.

Identifiers in examples
#######################

You may often encouner specific names such as ``foo``, ``bar`` and ``quux``. These do not have any attached meaning, they serve the same purpose as the name "John Doe" etc.

More about these and their history:

- https://en.wikipedia.org/wiki/Metasyntactic_variable
- `RFC 3092 <https://datatracker.ietf.org/doc/html/rfc3092>`_

Recommendations
###############

- A variable name should clearly specify what is refers to. Something like ``mana`` might be ambiguous but ``current_mana`` and ``maximum_mana`` will not.
- The more broadly something is used, the longer name it should have. Most variables are used in small contexts so anything that gets reused across lots of code should be clearly identifiable and searchable.
- If you need to write a comment to describe a variable's name, you have choosen a bad name.
- Variables and types represent data. They should be named using nouns. Functions represent actions. They should be named using verbs.
- Be consistent. If you like to write ``temperature`` as ``temp`` do it either always or never.
- Avoid using shortcuts, unless they are related to the project. It's hard to specify a clear border here as the topic is very subjective. Many projects include a glossary with explanations on shortcuts that appear in their documentation and code.
