.. title: 01 - introduction
.. slug: index
.. description: introduction to error handling
.. author: Xeverous

.. TODO state somewhere "This chapter will also continue with I/O examples and showcase various utilities in action."

Errors are unavoidable. Sooner or later you will encounter one and this is just a part of the job. In fact, you probably have encountered a lot of them already. Time to tidy up the knowledge about them and learn how to best deal with different kinds of errors.

Classification
##############

First, I would classify errors by what they are actually doing and what is their usual cause. Problems falling into different categories will usually require different response.

- **typo** - a harmless mistake, usually within a string; in typical case, mistyped string does not cause any real problems and users will easily spot the mistake (majorty of strings within software have informative role and do not affect behavior in any way)
- **logical bug** - a mistake within code structure (e.g. wrongly written :cch:`if`) that causes the program to take different actions than desired, e.g. failing to apply promotion code for a specific product
- **undefined behavior** - a mistake within code that causes the program to corrupt itself or crash, a problem on technical level
- **operation failure** - something that the program relies upon failed (e.g. a file could not be saved on disk)
- **input error** - invalid data, something different than expected (e.g. letters given as telephone number)

The first 3 are caused internal factors - they come from mistakes in the program's code. Every program should aim to have none. There are numerous ways to deal with these (code review, automated testing, documentation, ...).

The last 2 are caused by external factors - they come from outside the program and the program should be prepared to handle them. No matter how free of typos, free of logic mistakes and UB software you write, some user will attempt to write "asdfgh" as their postal code and your program has to deal with it. Such things are simply outside program's control so instead of trying to get rid of them (which is not possible) the program must be prepared for their appearance.

Some errors might be a combination of both.

Approaches
##########

Typos and logical bugs are best dealt with by code review and automated testing. Tests simply proof that the program reacts correctly to predetermined situations. Some logical bugs may lead to UB so these 2 categories can overlap.

UB has numerous ways to prevent or detect it. By nature of UB once it happens you have no guarantees what your program will do. Thus, you should primarily aim to prevent it from happening rather than dealing with it.

Operation failures and input errors have a very wide set of possible approaches, each with different tradeoffs. Generally, error reporting and handling can be done in variety of ways, the most significant part being how it affects the function which has to report the failure and the function which has to deal with it (sometimes far apart on the stack). These aspects are by far the biggest error handling topic.

.. admonition:: warning
    :class: warning

    Error reporting is not the same as error handling. Quite often they are separate pieces of software, though error handling depends on the reported information. The main reason for this separation is that most errors have to be dealt with in a smart way, often by a significantly different operation - thus when an error appears the currently run function gathers necessary information and returns it to a parent function (sometimes many frames up the stack) so that it can perform an appropriate decision from high-level perspective.

Specific methodologies
######################

Each has different pros and cons.

- "garbage in, garbage out" (no error handling) - this simple approach ignores any checking and simply proceeds with operations, in the case of invalid input data the result will be meaningless (even if it looks correct). For obvious reasons, this approach can not be applied where invalid input data could cause UB. Commonly used for mathematical computations (especially floating-point which unlike integers have no UB on any operation) because it allows very simple interfaces, does not clutter the code with error handling logic and due to simplicity of implementation can result in very good performance. Outside pure computations this methodology has very low practical value because pretty much any other task is not as forgiving.
- retry it - generally only appropriate when the problem is temporary and has asynchronous nature - mainly networking. Otherwise (in deterministic systems) the operation will fail again with exactly the same error.
- report it and handle elsewhere - usually the problem can not be dealt with inside the function where it occurred, but some function up the stack could react to it and perform a different operation. There are numerous ways to report a problem, most require changing the function to have a different return type and/or additional paramater.
- kill/restart - the program can not deal with the error and the only thing possible is to kill or restart it (optionally log the problem or/and inform the user), done in 2 cases:

  - assertion failure - the program has detected an internal mistake (an update with bugfix is needed), the code can not proceed because running further with violated requirements will almost certainly end in UB
  - critical operation failure - the program failed to do something absolutely necessary (e.g. could not load configuration from disk, could not allocate memory)

"Garbage in, garbage out" doesn't need its own lesson, it's as simple as it gets. The code simply produces meaningless result if input data requirements were violated. Obviously only applicable if the worst case is just output of meaningless data.
