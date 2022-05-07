.. title: 02 - states
.. slug: index
.. description: C++ streams (error) states
.. author: Xeverous

Stream states
#############

Each C++ stream has a state that holds information about special events (mainly errors). Error handling itself is complex enough that it's covered in separate chapter. For now, you should remember that **after any error, all subsequent I/O on the same stream will fail immediately untill the error state is explicitly cleared**.

Streams have defined convertion to :cch:`bool` so they can be put into conditional statements like :cch:`if` and :cch:`while` to check for any non-ideal state:

.. cch::
    :code_path: stream_operator_bool.cpp
    :color_path: stream_operator_bool.color

Each C++ stream has a state that informs about potential errors. The state is stored on a specific *bitmask type* called :cch:`std::ios_base::iostate`.

.. admonition:: tip
  :class: tip

  A *bitmask type* is a type that supports a finite number of independent non-zero values each representing unique bit. Multiple values can be stored in 1 object of bitmask type and retrieved separately. The simplest bitmask example is an integer or enumeration type where different bits are represented by constants that are different powers of 2.

  Come back to `lesson about bit operators <link://filename/pages/cpp/tutorials/beginner/02_basics/08_operators/operators.rst>`_ for more information.

There are 3 possible flags (values implementation-defined):

- :cch:`std::ios_base::badbit` - represents unrecoverable error (a crucial operation such as memory allocation failed).
- :cch:`std::ios_base::failbit` - represents recoverable error (ususally a retryable operation such as formatted I/O failed).
- :cch:`std::ios_base::eofbit` - set when all data has been processed and there is no possibility of continuing (e.g. end of file, closed socket). If reading interactively (e.g. :cch:`std::cin` which was not redirected to ream from a file), the EOF can be sent to the program through the console:

  - Unix console terminals: ctrl+D (though does not work in Git Bash on Windows)
  - Windows cmd: ctrl+Z
  - Windows Power Shell: ctrl+Z

There is also :cch:`std::ios_base::goodbit` which has value 0 - if comparison of stream's state is equal to goodbit, it means no error bit flags are set.

.. admonition:: tip
  :class: tip

  Because :cch:`std::ios` is an extension of :cch:`std::ios_base` (*derived type* precisely), you can write :cch:`std::ios::failbit` and such as a shortcut.

The table below showcases how different functions behave for different states:

TODO table from https://en.cppreference.com/w/cpp/io/ios_base/iostate
TODO this table needs CSS support for background and reST support for column span.

If any of error flags is set:

- it will stay permanently until explicitly cleared
- all I/O on this stream will fail immediately

Correct reaction to different flags is crucial in implementing robust I/O. Generally:

- if bad bit is encountered, the entire I/O should be redone as stream's state is not recoverable
- if fail bit is encountered:

  - if reading interactively: it should be cleared and last I/O operation should be retried
  - if reading from premade input (e.g. file) - stop processing, similarly to bad bit

- if EOF (end of file) is encountered, this means no more data will be given and any I/O-handling code should proceed processing the data

Simple handling
###############

The following program reads numbers untill anything wrong happens.

.. cch::
    :code_path: stream_simple_handling.cpp
    :color_path: stream_simple_handling.color

Notes:

- This program doesn't differentiate between error conditions (recoverable, unrecoverable, EOF). This approach is only useful if you want to stop upon any problem.
- EOF alone does not make convertion to :cch:`bool` evaluate to :cch:`false`, but any operation after reaching EOF will fail and set failbit so eventually the loop will stop. This behavior is desirable because last characters in the input can result in both successful read and setting EOF - in such case we still want to accept last chunk of data and stop in the next iteration.

Advanced error handling
#######################

The following program reacts differently to different problems:

- failed I/O - operation is tried again
- EOF - reading stops
- badbit - reading stops, warning is printed

.. cch::
    :code_path: stream_advanced_handling.cpp
    :color_path: stream_advanced_handling.color

This program is much more detailed and while it deals with different situations appropriately, I wouldn't call it's code to be easy to write - there are lots of ways to make potential bugs:

- different order of conditions inside the loop - faulty logic or at least unclear error messages
- missing clear - the loop would endlessly stay in fail state
- missing ignore - the loop would endlessly process fautly data
- missing breaks - faulty logic or endless loop

For this reason C++ streams get a lot of criticism - they support a lot of customization but at the same time doing even simple I/O operations is complicated and contains many opportunities to commit a bug that results in endless loop or invalid data. Additionally each formatted I/O operation can treat whitespace differently. My recommendation is thus:

- For non-interactive input (e.g. text from file), use the simple approach of testing convertion to :cch:`bool` (basically first example).
- For interactive input use line-oriented functions (explained in a later lesson) and do any input validation yourself - this will detatch your code from dealing with stream states, allow custom (potentially very complex) validation and make retrying operations easier.
