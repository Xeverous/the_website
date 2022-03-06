.. title: 03 - formatting
.. slug: index
.. description: (un)formatted I/O with C++ streams
.. author: Xeverous

All streams in C++ can do formatted or unformatted I/O.

- Unformatted I/O always behaves in the same way.
- Formatted I/O means that resulting data is dependent on stream's state and currently used *locale*.
- :cch:`operator<<` and :cch:`operator>>` are intended for formatted I/O.
- Unformatted I/O and more formatted I/O is available through stream's member functions.

Locale is a pretty complex feature intended for localization which can affect formatted I/O and specific text operations. Due to the size and uniqueness of the feature, it's explained in a separate article TODO link (outside the tutorial). Custom locales are rarely used and the default "C" locale is universal to the point of being able to completely ignore this topic for now.

There are 2 sets of stream manipulators: permanent and non-permanent (not a formal name, I selected these words for teaching purpose):

- Non-permanent manipulators only affect next I/O operation. After the operation, the stream behaves as previously.
- Permanent manipulators affect all future I/O operations untill another one of the same group is applied. For each group of permanent manipulators, one is the default.

TODO give many examples on how to print everything, based on notes from LCPP and old repository/content/cpp_tutorial/from_scratch/08_io_and_text/03_formatted_output.md
