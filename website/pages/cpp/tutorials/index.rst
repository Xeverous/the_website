.. title: tutorials
.. slug: index
.. description: C++ tutorials
.. author: Xeverous
.. index_path: .

- `beginner C++ tutorial <link://filename/pages/cpp/tutorials/beginner/index.rst>`_
- `accelerated C++ tutorial <link://filename/pages/cpp/tutorials/accelerated/index.rst>`_
- `C++ templates tutorial <link://filename/pages/cpp/tutorials/templates/index.rst>`_

beginner vs accelerated
#######################

- If this is your first time learning a specific programming language, use the beginner tutorial. Apart from C++, it also introduces many other things that are ubiquitous in the whole programming world.
- If you already have significant experience in a similar language (especially Java or C#), you can use the accelerated tutorial which skips common programming details that at this point would be boring for you. It still explains all the needed things, just from a different perspective and in a different order. This tutorial can also be used as a refresher if you are picking up C++ again after a longer break.
- If your only experience is C, use the beginner tutorial (only skipping the preprocessor articles). There are multiple reasons for it:

  - The accelerated tutorial assumes you are already familar with many OOP and other concepts (that are not in C) and therefore does not explain them or only lists differences from other languages.
  - The beginner C++ tutorial **does not start from teaching C**. It is actually one of the biggest mistakes ever that any C++ teacher can make, so big that I made a `separate article <link://filename/pages/other/on_teaching_cpp.rst>`_ about this problem.

templates tutorial
##################

C++ templates are very powerful, much more powerful that C# or Java generics - they are *Turing-complete*. This is where the C++ *Standard Template Library* draws its power from. The tutorial starts from simple function templates, goes through increasingly more advanced topics, explains arcane exploits of the C++ language specification and ends on magic techniques that are behind expert-level C++ template metaprogramming. This is perhaps *the only* freely available complete C++ TMP guide on the internet.

Before attempting to become a C++ template wizard, you should be fairly prepared - uncontrolled magic can do as much harm as benefit. That is, you should complete at least one of the other C++ language tutorials. The templates tutorial assumes that you already know non-template parts of C++ very well.
