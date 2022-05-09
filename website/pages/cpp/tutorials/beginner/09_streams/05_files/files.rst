.. title: 05 - files
.. slug: index
.. description: reading and writing files using C++ streams
.. author: Xeverous

Reading and writing files doesn't differ much from using other streams - the core difference is initialization.

File streams
############

File streams are an extension of already presented streams, they have few more functions specifically for dealing with files.

There are 3 main types (all defined in :cch:`<fstream>`):

- :cch:`std::ifstream` - input file stream
- :cch:`std::ofstream` - output file stream
- :cch:`std::fstream` - file stream supporting both input and output

Generally you should use one of the first 2 as situations where the same file is both read and written are very rare.

Opening a file
##############

2 things must be provided: *path* and *mode*.

How exactly a path is interpreted depends on the platform and its file system - C++ standard library will pass it unmodified to the underlying system interface. Generally:

- If an absolute path is given (e.g. ``/etc/ssh/shh_config``) the file will be searched at this exact location.
- If a relative path is given (e.g. ``ssh_config`` or ``ssh/shh_config`` - basically any path without root (root is ``/`` on unix systems, drive letter with ``:`` on Windows)) a file will be searched at the location that is combined from executable's *working directory* and the given path.

.. admonition:: note
    :class: note

    Working directory may not be the same as the directory where the executable is placed (though it often is). If the program is launched from a terminal, the working directory is usually a part of the shell's prompt (on many shells it can be changed by the ``cd`` command and can also be checked by the ``pwd`` command). If the program is launched from a graphical interface, typical implementation sets working directory to the same where executable is.

The mode further specifies behavior

- :cch:`std::ios_base::app` (only for output streams) - any data will be appended at the end of the file
- :cch:`std::ios_base::trunc` (only for output streams) - truncate the file (as if the file was removed and recreated)
- :cch:`std::ios_base::ate` (only for input streams) - seek to the end of file after opening (as if entire file has already been read)
- :cch:`std::ios_base::bin` - open the file in *binary mode* (default is textual)
- :cch:`std::ios_base::in` - open the file for reading, added automatically for input streams (but not added for streams that support both directions)
- :cch:`std::ios_base::out` - open the file for writing, added automatically for output streams (but not added for streams that support both directions)

.. admonition:: note
  :class: note

  Just like with state flags, you can also write :cch:`std::ios::bin` and such as a shortcut.

- Append flag is commonly used for logging and other diary-like files which are expected to grow over time as the application logs more information (similar to ``>>`` redirection in many shells).
- Truncate flag is commonly used for files that are expected to be refreshed and rewritten every time the application is relaunched (similar to ``>`` redirection in many shells).
- Binary mode is used when the file contains binary data (not text) to avoid any automatic convertion and when the convertion of textual data is undesirable.
- Other flags are hardly ever used.

Binary mode
###########

There are 2 modes in which a C++ stream can operate on a file:

- binary - data is read and written exactly as given (in terms of bytes)
- text - some characters are changed to accomodate for platform-specific conventions of textual files:

  - Windows: outputting ``\n`` actually outputs ``\r\n``, reading ``\r\n`` actually reads ``\n``
  - some other minor details listed on https://en.cppreference.com/w/cpp/io/c/FILE#Binary_and_text_modes

.. admonition:: warning
  :class: warning

  Do not confuse modes with formatted and unformatted I/O. They are 2 separate things that work independently.

.. admonition:: note
  :class: note

  If you are reading or writing files which content (values of subsequent bytes) do not represent text in any encoding (e.g. sound, image) always use binary mode. Otherwise binary data (e.g. color of pixels) could be understood as specific characters and get unwanted convertion such as LF to/from CRLF on Windows. Binary files should be always read and written as exactly the same sequence of bytes. All automatic convertions in textual mode are made only for handling of text, applying them to binary data will simply modify it in undesirable ways.

File to string
##############

A common need is to read entire file into one string object for later processing. There are tons of ways to do this in C++ and there has been somewhat a hot debate what is most idiomatic or most performant. In addition to this, specific applications should not actually read entire file into one object (imagine multi-gigabyte database) but read specific chunks and process them as more data in put into the buffer of limited size - such approach reduces memory usage and allows for concurrent disk operations and data processing.

Still, for majority of applications the benefits of concurrent reading/writing/processing (and any other performance improvements) are not worth the trouble caused by complication - majority of programs read small files (megabytes at best) or files which need to be read entirely anyway (images, sounds, models and other files for games and simulatory applications).

For these reasons, here is a couple of functions that can be used to read entire file contents to 1 array-like object:

TODO paste function implementations from notes
