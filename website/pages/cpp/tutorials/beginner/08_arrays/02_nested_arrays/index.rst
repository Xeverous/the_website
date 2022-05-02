.. title: 02 - nested arrays
.. slug: index
.. description: arrays of arrays
.. author: Xeverous

An array holds multiple objects of the same type. This type can also be an array!

Syntax
######

Notice order of layers. The outer layers of multidimentional arrays appear on the left in declarator syntax.

.. cch::
    :code_path: syntax.cpp
    :color_path: syntax.color

For multidimentional arrays, only the first (outermost) layer can have inferred size:

.. cch::
    :code_path: syntax_size.cpp
    :color_path: syntax_size.color

Multidimentional traversal
##########################

When looping over multidimentional arrays, pay attention in which order layers are accessed:

.. cch::
    :code_path: traversal.cpp
    :color_path: traversal.color

The example above aims to present that a working set of nested loops may cause very inefficient memory traversal. Both sets of loops work but only the first one accesses elements in order of increasing memory addresses. The second one correctly accesses each element exactly once, but does it in a very "jumpy" way which will generally limit effectiveness of cache - modern hardware is designed to access memory sequentially.

For this reason, when looping over nested arrays you should start with outer layers first and go into inner layers in nested loops.

.. TODO add infographic

Translated indexes
##################

Multidimentional arrays are often replaced with 1D arrays that map multidimentional indexes to a single dimention in order to simplify code that uses them.

Here is the same program as above but realized using this method instead:

.. cch::
    :code_path: traversal_translated.cpp
    :color_path: traversal_translated.color

In such case looping over elements is much easier, you only need a small helper function to translate 2D index into 1D.

    Which approach is more efficient?

I don't think there is any significant difference between both, assuming there is any. In the case of the first, when ``[]`` operator is nested it basically does the same thing as the helper function in the later example. It just hides the same computation inside *pointer arithmetics* while in the second example it is done explicitly. The goal of both is to move in a such way that memory is accessed sequentially.

    How would 3D to 1D translation look like?

.. cch::
    :code_path: translation_3d.cpp
    :color_path: translation_3d.color

..

    Is it possible to do a reverse index translation? From 1D back to multidimentional?

.. cch::
    :code_path: translation_reverse.cpp
    :color_path: translation_reverse.color

Exercise
########

Recall previous task with printing multiplication table. Now modify it so that first it fills an array with values and then loops over the array to print contained values. Do it in both ways (nested array and translated index).
