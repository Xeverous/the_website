.. title: 03 - deduction
.. slug: index
.. description: deduction of template parameters
.. author: Xeverous

When a template is being used (*instantiated*), the compiler needs to "figure out" what types (or values in case of NTTP) should replace template parameters. This mechanism is known as **deduction**.

.. cch::
  :code_path: min_used.cpp

The example above is very trivial; however *template type deduction* itself is a rather complex feature. I won't describe it in detail because there are simply too many cases and too many possible combinations with other language features. Instead, you will learn specific deduction rules along the way, similarly how :cch:`const` is laid out in the beginner tutorial - not a chapter of its own but an addition to every other feature (const objects, const parameters, const functions, const methods, ...). Deduction intertwines significantly with various elements of the type system and introducing them all in a single lesson would roughly be copy-pasting cppreference or the standard specification.

The examples use ``::`` to avoid ambiguities with standard library functions. Because of ADL, calls to function templates can also search identical names in the standard library if the type of one of arguments also comes from the standard library namespace.

Deduction vs :cch:`auto`
########################

:cch:`auto` is based on the same mechanism. In fact, :cch:`auto` is specified to use *template type deduction*, as if the deduced type was a function template parameter and the initializer was the argument.

.. cch::
  :code_path: auto.cpp

You can observe that both sets of cases are identical:

- Template type deduction (and :cch:`auto`) strip top-level cv-qualifiers when used without qualifiers.
- Existing qualifiers remain and participate in deduction.
- The final type is built from both present and deduced type modifiers.

You can also observe that:

- :cch:`auto` does deduction only for a single initializer value - not (potentially multiple) function parameters.
- Templates can be required to deduce something like :cch:`std::vector<T>` (where the template parameter is only a part of the final type) while (as of writing this) you can not write something like :cch:`std::vector<auto> v = /* expr */;$$$namespace::type<keyword> var_local = 10com_multi;`.

In other words, deduction in templates covers significantly larger amount of (potentially more complex) situations.

:cch:`std::initializer_list` is a special case:

- templates can not deduce it directly
- :cch:`auto` can deduce it only when paired with *copy-list-initialization*

.. cch::
  :code_path: initializer_list.cpp

Deduction vs multiple parameters
################################

Each function parameter is deduced separately. If there is a conflict between deductions or the deduction can not be performed, the instantiation will fail.

.. cch::
  :code_path: deduction_failure.cpp

As you can see, deduction can fail for some arguments. What is important is that:

- there are no conflicts between deductions
- every template parameter has at least 1 successful deduction

Explicit specification
######################

There are no requirements between function arguments and template parameters. This means that:

- types of function template arguments do not have to be in the same order as template parameters
- not every parameter must be declared using a unique template parameter
- not all template parameters have to be used within the list of arguments

This in turn means that many function templates can not deduce their template parameters.

Undeduced template parameters and parameters that have conflicting deduction can be fixed by explicitly specifying them when instantiating the template:

.. cch::
  :code_path: explicit_specification.cpp

The order of template parameters is crucial. You generally want to have non-deducible template parameters first and deducible parameters later:

.. cch::
  :code_path: explicit_order.cpp

Default template arguments
##########################

Another way of dealing with non-deducible (but not conflicting) template parameters is to provide defaults. Below is a simplified implementation of :cch:`std::exchange` - a function which sets a new value and returns the old one.

.. cch::
  :code_path: default_template_arguments.cpp

The function could be implemented using just one template parameter for both arguments but:

- using 2 different template type parameters allows assignment of objects of a different type

  - in some cases this improves performance by avoiding creation of expensive objects (e.g. strings)
  - in some cases this is desired because the target object intentionally accepts objects of a different type (e.g. a fraction class accepting assignment from integer types)

- the default template argument functions as a fallback to :cch:`T` when the argument type can not be deduced

In short, such implementation (2 template parameters with default) results in best of both worlds: support for mixed-type assignments and support for non-deducible arguments.

Note another small thing: the default of the second template parameter depends on the first. Such dependency is not allowed within non-template default arguments:

.. cch::
  :code_path: default_arguments.cpp

Summary
#######

.. admonition:: definition
  :class: definition

  When a template is being instantiated, the compiler must know what to substitute template parameters with. There are 3 ways to provide this information:

  - explicitly specifying template parameters
  - template argument deduction
  - defaults for template parameters

  In case of combinations of multiple of these - the higher points on the list have higher priority.

.. admonition:: definition
  :class: definition

  Undeduced template parameters can be fixed by explicit specification or default template arguments. Conflicting deductions can be fixed only by explicit specification
