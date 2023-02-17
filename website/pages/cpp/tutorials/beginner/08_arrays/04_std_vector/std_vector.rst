.. title: 04 - std::vector
.. slug: index
.. description: standard library dynamic array
.. author: Xeverous

:cch:`std::vector` works similarly to :cch:`std::array` but has few core differences:

- it allows to dynamically change the size: add and remove elements
- it dynamically allocates memory as needed (quite complex mechanism for this state of the tutorial)
- vector's data is put on heap memory, not on stack

Example:

.. cch::
    :code_path: std_vector_example.cpp
    :color_path: std_vector_example.color

.. code::

    1, 2, 3, 0, 10, 20, 30,
    size: 7
    capacity: 12

:cch:`std::vector` looks like an enhanced version of :cch:`std::array` but note that it implements its storage very differently. It's way too early to showcase how exactly vector is implemented but for now you should just know that dynamic memory allocation has its cost. In most cases this cost is justified as many operations can not be easily done without dynamic allocation.

    If strings also allocate dynamically, what's the difference between :cch:`std::string` and :cch:`std::vector<char>`?

If you actually thought about this (unlike most questions in the tutorial which are fake, only to make Q&A style content) then I have to inform you this is a really good question. Vector offers a more generic interface that can be used to store objects of any type, not just character types. The way a typical string is used make a separate type with different implementation quite valuable. The reasons for different implementations are:

- String is required to support (very undesirable) null-terminated C-string APIs - interfaces where instead of passing pointer+length (or other size information) only pointer is passed and it's expected that the end is marked with special :cch:`'\\0'` character called null terminator (recall lesson about string literals). This means that even empty string requries 1 object to allocate (not necessarily 1 byte because :cch:`std::wstring` and other string types operate on other, potentially larger character types). This requirement alone makes separate type completely justifiable as vector is designed to operate on any type and for many non-character types there is no magic zero value that could be designated for null terminator.
- String has a different allocation strategy. This is not required by the standard, but many implementations do it. Unlike vector, a typical string contains a quite small amount of data (e.g. button label, username, form address data, ID) - strings of large size are rare. For this reason, the string has a small statically allocated buffer inside and when the stored text would fit in it, it's put there to avoid dynamic allocation. In other words, if the string is small, it works like :cch:`std::array` instead of like :cch:`std::vector`. This complicates the logic but avoiding costly allocation pays off.

  - When vector is empty (default state) it does no allocation. Strings can not easily avoid allocation as even empty strings still have to contain a null terminator. Small bufer optimization (sometimes called short string optimization for this specific case) allows to avoid this problem by having a small static array.
  - Vectors do not implement small buffer optimization because in vast majority of cases the buffer would be too small to use. Still, there is :cch:`boost::container::small_vector` which uses this strategy and has the buffer size as one of its template parameters.

- Due to different usage patterns, vectors are typically passed as ranges (e.g. a pair of iterators, pointer + size) while strings are passed as a whole object. The reason for ranges is that many algorithms do not care how a given data structure layouts its memory, only what operations it performs (more on this in later chapters). Strings may have more expectations than just valid memory range.

In short, strings have different expectations and usage patterns which make separate implementation justifiable.

.. TODO explain .c_str()
.. TODO some vector exercises?
.. TODO explain how vector implementation works
