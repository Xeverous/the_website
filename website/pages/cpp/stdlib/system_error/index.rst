.. title: &lt;system_error&gt;
.. slug: index
.. description: std::error_code and related error handling utilities
.. author: Xeverous

.. admonition:: note
  :class: note

  Originally started as `Boost.System project <https://www.boost.org/doc/libs/release/libs/system/doc/html/system.html>`_, now :cch:`<system_error>` is a part of C++11 standard library. The library got standarized only with minor renaming changes.

From Boost.System documentation:

    Error conditions originating from the operating system or other low-level application program interfaces (APIs) are typically reported via an integer representing an error code. When these low-level API calls are wrapped in portable code, such as in a portable library, some users want to deal with the error codes in portable ways. Other users need to get at the system specific error codes, so they can deal with system specific needs.

Goals
#####

The library serves an implementation of specific error handling design. Its core goals are:

- lightweight non-allocating error representation type, able to be passed by value but still offering some polymorphic behavior
- ability to define custom error numbers and categories
- ability to map custom error numbers to a generic category
- support for converting error values to string messages
- exception class supporting error representation type if there is a need to report via exception

Design
######

- Each error category is (preferably immutable) global object that implements error category interface, which primary function is returning string representation for the given error condition.
- The error representation type holds only 2 data members: error number (as integer) and a pointer to an instance of error category. There are 2 such types:

  - :cch:`std::error_code` represents platform-dependent error code
  - :cch:`std::error_condition` represents platform-independent error code (rarely used)

- Error numbers must only be unique within the same category.
- Error number :cch:`0` is a special value and must mean no error in every category.
- :cch:`std::system_error` is a dedicated exception type to hold error information when an exception object is desired

Synopsis:

.. cch::
    :code_path: synopsis.cpp
    :color_path: synopsis.color

Usage
#####

This design works best when:

- an application needs to work with multiple subcomponents where each has its own error numbering system
- the error passing mechanism must be lightweight
- there are no dynamically generated error descriptions - each category has fixed numbers of errors with predetermined descriptions

Implementation
##############

- define your error numbers (enumeration or an integer type)
- implement the category class

  - the class definition and its instance can be hidden from other code - you only need to expose a function that returns :cch:`const std::error_category&$$$keyword namespace::type&`
  - :cch:`override` the :cch:`name$$$func` function
  - :cch:`override` the :cch:`message$$$func` function
  - (optional) :cch:`override` the :cch:`default_error_condition$$$func` function if you wish to translate errors to a more generic category (such as :cch:`std::generic_category()$$$namespace::func()`), by default the function does not change the category

- (if error numbers are enumeration) specialize :cch:`std::is_error_code_enum`
- (optional) add `make_error_code$$$func` in the same namespace as the definition of error numbers
- when reporting errors use :cch:`std::error_code` constructor or call `make_error_code$$$func`

The last 3 steps can be repeated analogically for :cch:`std::error_condition`.

Example
#######

The program implements HTTP error numbers taking advantage of standard library features.

header:

.. cch::
    :code_path: example_header.hpp
    :color_path: example_header.color

source:

.. cch::
    :code_path: example_source.cpp
    :color_path: example_source.color
