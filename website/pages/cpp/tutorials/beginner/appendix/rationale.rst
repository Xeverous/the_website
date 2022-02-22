.. title: rationale
.. slug: rationale
.. description: rationale for beginner C++ tutorial
.. author: Xeverous

Below is a list of arguments and explanations why certain things in the beginner C++ tutorial are the way they are.

Common mistakes
###############

It's astonishing for me how many tutorials on the web do not post common mistakes and misunderstandings. The value by posting antiexamples is as good as for regular examples - the reader gets additional help in understanding the concept and often it may save a lot of (quite frustrating) time due to already knowing a common mistake.

Q&A style
#########

Majority of Q&A are actually fake. Only some of them have been experienced by me when explaining something to others. But the style often lets me to demonstrate how to ask questions (many are much more detailed and technically correct than an average student would state them) and create a feeling of a real class, as if some student did ask such question. Many of the questions predict what would be asked, some readers may be very satisfied by the feeling of a teacher that predicted what the student would want to ask for (but could not formulate the thought).

I do say rhetorical and non-rhetorical questions in real conversations too. This + technically-rich vocabulary + the way I structure my content (I pay huge attention how it's written, often rereading and rewriting paragraphs multiple times) are probably the primary features identifying my unique prose.

Order of lessons
################

You might not experience how hard it is unless you actually try it. Imagine a combination of 2 features (each with 3 subcases) which lead to 9 possible situations.

- Explain in order: A1, B1, C1, A2, B2, C2, A3, B3, C3 - someone can complain that 3 is explained very late.
- Explain in order: A1, A2, A3, B1, B2, B3, C1, C2, C3 - someone can complain that C is explained very late.
- Explain in order: A1, B2, C3, then make more examples of rarer cases - someone can complain that the material is unordered.

Good material needs not only to have as few cross-dependencies as possible but also be relatively structured so that the reader can come back for a refresh on a specific topic. Thus, some chapters (especially preprocessor content - variadic macros and X macros) have lessons which explicitly state that the reader does not need to read it now, only later if desired - the lesson is placed where it is only to be able to be found easier. This approach is much better than finishing the tutorial with the last chapter that contains unordered articles about random things not covered earlier.

OOP content
###########

Fraction class
==============

This class appears across a large span of lessons and by far it's the best class I have found to demonstrate various OOP principles in C++:

- The class represents a very simple mechanism. It should be well-known to any reader. At the same time it has 2 fields and is not a forced example like a class wrapping a single integer or a string.
- The class has very reasonable default state (0/1, simplest fraction form of zero).
- The class has an invariant (denominator can not be 0) - this greatly demonstrates purpose of classes.
- It can contain a non-brainded setter (due to invariant), non-brainded getter (approx => convertion to double, then division) and an action (simplification which uses GCD).
- It represents a mathematical concept and thus is a very good example to present operator overloading on, including mathematical operations and explicit convertions (to floating-point types) in addition to commonly overloaded comparison. Even better, most overloaded operators have perfectly matching difficulty level - they aren't 1-line functions but also don't span tens of lines and don't require huge knowledge.
- Constructor can be easily overloaded or use default paramaters.
- The class is easily printable and testable.

Basically, the class can be used to demonstrate many OOP principles and features that come before polymorphism.

No shape classes
================

This is a common yet very bad example for teaching OOP. "Every square is also a rectangle" - sure, I get it but when it comes to the code, **neither is an extension of the other** - the square is a corner case of the rectangle (which is a corner case of a quadrangle) and is much better explained with imperative/functional approach (optimization example for specific input data) than OOP. Additionally, if you implement it the OOP way there is a tendency to put some "common" data into the base class, only to realize that semantics and/or amount of variables in derived types can not be an extension of the base (square would be derived from rectangle but it needs less data members).

And if you implement it the reverse way (rectangle inherits square), derived types violate Liskov Substitution Principle because algorithms working on the base type no longer work on derived ones.

Pointers
########

These are very late in the tutorial. And this is intentional. They aren't inherently bad but they are inherently complex.

Reasons listed in `Kate Gregory - Stop teaching C <https://www.youtube.com/watch?v=YnWhqhNdYyk>`_ talk:

- At early states, beginners are still learning to remember the syntax. Pointers have significant syntax complexity.
- Pointers require significant leap in thinking, something which is better done later when people know more how the language works underneath. Otherwise they won't get the idea and you will end up with them treating it as vodoo randomly inserting ``*`` and ``&`` into code until compiler agrees.
- You can go as far as explaining polymorphism without use of pointers.
- Pointers are major cause of frustration, yet you don't really use them often in modern C++. High risk + low reward.

Other reasons:

- It's a teaching trap: thinking that you need to explain underlying mechanisms before explaining higher level concepts. Python proves you don't need to understand pointers in order to write code, yet so many "teachers" insist on teaching C as a prerequisite to C++ (as if you needed to learn latin before english). People use many devices every day (dishwasher, microwave, fridge, ...) without understanding in detail how they work - they just need to understand the interface (buttons).
- K&R book "The C programming language" has pointers at half of the book. And it's just C. With C++ we can push them even later.

Naming style
############

A lot of C++ code found on the internet uses camelCase or CamelCase style. This is against the convention and likely a bias from other languages, in which these styles are used. C++, just like C uses purely lowercase_name_style and it's also the recommended name by Core Guidelines.

Extra reasons to use this style:

- it's consistent with C++: the standard library and even keywords (e.g. :cch:`static_cast`) are lowercase
- ``ExportAsXml`` or ``ExportAsXML``? ``export_as_xml`` has no such problem
- there is a study which concludes that 3+ word names written as camelCase or PascalCase are significantly harder to read than snake_case names[citation needed]
