.. title: home
.. slug: index
.. description: homepage
.. author: Xeverous
.. breadcrumb: False
.. pretty_url: False

Welcome to my website, a project where I post various C++-related materials and organize them in a way that allows incremental learning.

The goal of this project is to create a website that new and existing C++ users can learn from, something similar to what other languages already have. Contrary to other learning material available online:

- This website is completely free.
- This website is an open-source project where people can contribute (though I still reserve the final decision about every change to myself).
- This website aims to have additional stuff like: common mistakes, FAQ-style content, deeper understanding of the language philosophy (e.g. why C++ has no :cch:`finally$$$keyword` keyword) and trivia (exercises not so much because for this I think there are already tons of materials online).

This project is incomplete. It is under continuous improvement and thus you may find missing/unfinished lessons, gaps in numbering, TODOs and other markings that I ``grep`` for when working on the project. As I'm not a web developer (and prefer vanilla to huge frameworks), various aspects of web tech (mostly CSS) may be inkorekt and some content may be pǝʇʇɐɯɹoɟ ʎlpɐq.

Current goals for the content:

- beginner C++ tutorial (from start up to classes, inheritance, polymorphism, operator overloading and exceptions) - mostly complete
- accelerated C++ tutorial (for people who already know another language and understand various programming concepts - this tutorial will be more of an analogy and examples than explaining stuff and will have significantly different layout/order of lessons; can also be used as a refresher of already obtained C++ knowledge) - barely started
- advanced C++ tutorial (pointers, dynamic allocation, placement-new, alignment, padding and other low-level topics) - not started yet
- C++ templates tutorial (probably first free online tutorial with all the template knowledge) - has first few lessons

..

  Wait what, why pointers so late?

Because they should be. One of the biggest mistakes in teaching C++ is starting with teaching C and/or hard to understand mechanisms such as pointers. Often while students still struggle to write syntaxically correct code, "teachers" introduce one of the hardest parts of the language for no reason other than "[...] is built on pointers so you should learn them first before you are allowed to use [...] from the standard library".

This couldn't be more wrong. Few year old kids understand how to use various household devices before even starting any education in math and physics. The same "teachers" may also teach Python on another class without even touching topics such as data structures and garbage collection (or that the reference implementation is in C). Why should we be forced to go the painful bottom-up way when learning C++?

The famous "The C programming language" book has pointers somewhere in the middle. With C++ they can be pushed even later. Watch `Kate Gregory - Stop teaching C <https://www.youtube.com/watch?v=YnWhqhNdYyk>`_ CppCon talk to know more about common C++ teaching mistakes. The order of lessons in the beginner C++ tutorial was heavily influenced by this talk.

  Concurrency?

No plans for it as of now. I would have to learn it first :). It would also be rather hard for me to accept contributions with content I do not understand yet.

  How can I help?

- The biggest amount of work by far is ordering of lessons and finding good examples. Writing articles (when materials are already prepared) is relatively easy. By *good examples* I mean stuff like the :cch:`fraction$$$type` class that can be found in the first OOP chapter in the beginner tutorial. The class is so good that I use it to explain numerous features across multiple lessons. See the `rationale article <link://filename/pages/cpp/tutorials/beginner/appendix/rationale.rst>`_ which explains why it's so good in detail.
- CSS: whatever you can improve. Please don't make PRs importing thousand-lines-long Bootstrap or other frameworks - such changes will be rejected.
- non-tutorial articles: if you have a topic that is C++ related or generally useful in the programming world (e.g. explaining Unicode, software licensing, an idea for a cheatsheet) you are encouraged to contribute. As of writing this, all the content is mine but I can easily add author information to pages with separate articles.
- Whatever else: just open an issue. Link to the repo at the bottom of every page.

  How is this website built?

To describe the process in detail would require a separate article (as well as the history of evolution of this project build process) but (if you have never written a static (backend-less) website):

- Articles are written in a text file format (not markdown!) that supports various forms of formatting enrichment. The format of choice is reStructuredText due to 1) actually having a standard specification (unlike Markdown which renders differently depending on the implementation) 2) supporting Python extensions that can go as far as introducing custom format keywords and output generation steps.
- Each article is processed through a set of parsers/plugins that convert it to HTML. After this stage each file contains a HTML subtree of the final page.
- Page parts are processed though a HTML templating program (here: Jinja2 - a part of Django framework) that allows to conveniently deduplicate HTML code and give some overall structure for generated pages by embedding Python code in HTML template files.
- Non-article files (CSS, JS and potentially other data) is copied as-is to the output directory.
- Everything is tied together by the Nikola framework (one among many such frameworks) that has been **heavily customized** and *augmented by plugins* so that I can do stuff like :cch:`this` or :cch:`that$$$func` or :cch:`that$$$var_local`.

See `reStructuredText test page <link://filename/pages/meta/rest_test/rest_test.rst>`_ for what the build process is currently capable of.

News
####

- 2023.03.10: Bugfix index page link (missing trailing slash).
- 2023.03.05: Initial release of a functioning website (beginner C++ mostly complete and others barely started). `Reddit post. <https://www.reddit.com/r/cpp/comments/11j8pa7/opensource_c_tutorials_website_project_first>`_
- 2021.06.04: `First reddit post <https://www.reddit.com/r/cpp/comments/ns4hl5/what_do_you_think_of_learning_c_through_online>`_ that announces the project.
