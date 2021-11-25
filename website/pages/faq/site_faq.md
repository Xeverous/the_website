<!--
.. title: site FAQ
.. slug: site_faq
.. description: frequently asked questions about the website itself
.. author: Xeverous
-->

## Site content

### Why tutorials are build over feature X, Y, Z but not incrementally over consecutive C++ standards?

This not a good idea. If you play any online game - do you learn it how it is at the given moment or read patch notes for every update since the beginning? It's good to know what things have been introduced in what order, but it doesn't do well in terms of learning. A lot of features can be mixed together, so the order of presentation matters, not the chronological order of their introduction.

It's better to study a complete feature in one go than to jump back to it periodically because there was a language update. It makes searching hard (unstructured lessons) and requires jumping between features when learning which may be confusing and counter-productive. Plus you are not going to remember when everything was exactly introduced anyway.

However, newer features are explicitly marked and most chapters about certain features do go upfront from the start to the latest changes. Where possible, I did go from the past to newer stuff, where not I focused more on the best order to understand things with least struggle.

### Why is not the C++ tutorial written in the order of low level to high level features? Why is `std::string` so early and pointers so late?

**There is a huge bias, especially in "teachers" that you need to learn C before C++. It is horribly wrong and does more harm than good.** The fact that 99% of C is valid C++ is irrelevant. 99% of C is really bad C++. Both languages have vastly different conventions and even some features have usage/syntax differences. **A lot of C habits need to be unlearned when moving from C to C++.**

C++ was built mostly on 2 languages: C and Simula. C brought the syntax and low-level features while Simula brought type safety and high-level features. But no one mentions you need to learn Simula before C++. Also, no one mentions you need to learn C before C#. Or to learn anything before Python, which hides a ton of things.

People are writing website scripts in JavaScript, making fun with Python modules without even knowing what are and how to use pointers. **You do not need to learn pointers and all the complicated stuff before using any of the high-level features of any programming language.**

**Placing pointers at the start of the tutorial results in a big wall for beginners: a lot to remember, a hard to debug problems, a lot of confusion and frustration. And all of this in a language that was designed to abstract away this details into simpler, easier to understand code.** Even in the book "the C programming language", pointers arrive as late as at the half of the book.

A more thorough explanation can be found in [Kate Gregory's talk - "Stop teaching C"](https://www.youtube.com/watch?v=YnWhqhNdYyk).

## Site creation

### What was the hardest part of writing the content?

**1\. Deciding whether X amount of text for an explanation of ABC is enough. Deciding between simple explanations and technically correct statements.** I might write 2X but will it not overwhelm the reader? Is more, simpler text always better? Some readers may find 0.5X to be enough (and more text to be redundant or boring) while some may find 2X + examples to be necessary to understand the thing. What about corner cases? More text = more confusion or better explanation? I think I may spend to much time on text-meta and think too deeply about each site user.

Regardless of text, I'm sure more examples are always a good idea. They don't distract the user much and each gives a chance to look how something is used.

Sometimes I struggle with creating examples - especially for design patterns. And it's better not to provide bad examples.

**2\. The order of presented features. Circular dependencies.** Multiple ones are very often mixed together and they don't offer much alone. Sometimes there are like 3 things, and I struggle to find a way to showcase them because A needs B, B needs C and C needs A.

It was easy with lambdas - they were build on top of ordinary functions and further lambda features were mostly going upwards in depth, not adding a lot of complexity - this is why lambda expression chapter is pretty straightforward, then adding more about mutability and generic programming.

It was hard with templates and pointers. Both by their nature are hard to grasp, and even short examples use a lot of features. Many features were added as syntax sugar or more complex versions of existing ones. The depth comes from mixing complex features, not from diving deeper into one. Some examples are overly trivial and may not represent well real use cases but at least they don't overwhelm the reader - at first stages it's more important to understand how it works, not what are applications of it.

Still, as with first point - I find that more examples are always better.

### What was the motivation to create the site?

**A vast majority of online content about C++ is garbage (and by garbage I do not mean outdated). Not only websites - there are many bad books too!!! Nothing has really motivated me so strong as the amount of trash tier content.** So many sites copy-paste average C or "C without C-only features" and claim it to be C++ "because we added a class", "because it compiles as C++":

- cprogramming (ironically most of their C++ is C)
- geeksforgeeks (take any exercise, C and C++ solutions are often the same code or have marginal differences)
- code project (countless beginner level mistakes in most articles)

A unique exception is thisPointer.com. It has some good idiomatic STL examples.

learncpp.com is regarded as one of the best sites for learning C++. Site is good but it still has many mistakes. Still, I rate it \#1 after mine which hopefully will be \#0 for you.

There is a C++ language tutorial on cplusplus.com. It is not bad, assuming we read it in 2003. Most content on the site is just outdated. Tutorial is pretty fast and compact, but:

- does not give any reasoning about desicions - readers do not learn, they just follow recomemndations with no understanding
- many features lack recommendation - reader can remember them, but has no idea what's their purpose and when to use them
- even for old C++98/03, the site does not mention many features
- some features are not presented in very convenient order
- the site does not seem to be maintained

Initially, I wanted to contribute to learncpp.com, but [Alex said](https://www.learncpp.com/site-news/report-an-issue/comment-page-2/#comment-310505) some of my points are on the todo list and prefers to have only own articles.

There are few other very good sites:

- [Fluent C++](https://www.fluentcpp.com/) - by Jonathan Boccara
- [Sutter's Mill](https://herbsutter.com/) - by Herb Sutter, known for [Guru of the week](https://herbsutter.com/gotw/)

...but since they are more blog-oriented for periodic news and posts, I disregarded them from being "C++ tutorial sites" and planned to build own guide based on plain markdown repository. I wanted a structured, step-by-step guide, not random blog posts about certain problems - 90% of C++ problems are already solved by Stack Overflow but it is not structured in any way for incremental learning.

Soon then, I realized GitHub has opened GitHub Pages and allowed for free static website hosting.

Other consequences

- I learn one of countless web frameworks.
- I learn HTML5 and CSS3.
- I will consolidate my skills and knowledge (and even use the site myself).
- The site is a great point for my CV (resume).

### What is used to build this website? Why these tools?

I started with [Jekyll](https://jekyllrb.com/) (static site generator using Ruby language and Liquid template engine) because GitHub just recommended it. I realized quite fast that this was not the framework for me - it did not support non-blog sites well and had significantly limited customizability. After watching its tutorials, where a person explains how does a for loop work it was clear for me that I am not the target audience. The fact that Jekyll documentation is not very thorough and I have no Ruby skills did not help either. And argh, the incremental build was still an experimental feature - scripting languages are already slow - imagine that in an addition you needed to wait for a full rescan and rebuild after every change.

There are tons frameworks, just see [the list of static site generators](https://www.staticgen.com/). But:

- A vast majority of these frameworks are only suited for blogs. That is, you just throw all posts in 1 directory and the framework renders a timeline, RSS feeds etc for you. No way to reorder posts, no way to make framework extensions and sometimes even no or limited ways of customizing HTML and CSS,
- The majority of remaining frameworks are dedicated to generate documentation. Again, not for my needs.

Only few frameworks covered my needs:

- The ability to put articles in any order, including hierarchical structure.
- The ability to fully customize HTML and CSS templates. No assumptions, no unremoveable parts.
- No forced JavaScript. No user-side HTML generation.
- No forced frontend frameworks (Bootstrap and similar).
- **Ability to extend generation mechanism, e.g. custom templates or extensions to Markdown / Restructured Text format.** Bold, italic and fenced code blocks are not enough for me.
- Ability to store some data (binary assets or configuration files) that can be used during generation.

After filteting all undesired frameworks, I was left only with 3 to choose from:

- [Hugo](https://gohugo.io/)
- [Statik](https://getstatik.com/)
- [Nikola](https://www.getnikola.com/)

Hugo is by far the most popular across these (as far as GitHub stars tell) and supports all what I need but ... it requires a lot of initial setup and learning. Also, I would need to learn Go in order to satisfy my large customization needs.

Statik is an interesting choice. Its ability to have custom ORM and data model (for each page) really shines, I have not seen such thing in any other framework. You can find informative table on its homepage. If you have needs to generate pages in specific layout from complex, relational data - I would definitely recommend Statik.

Nikola is just a bunch of plugins. They really advertise as such on their homepage. It is really just a build command which triggers certain plugins in certain order. There are lots of built-in plugins but the fact that you can extend/swap/remove anything from any build step opens huge customization possibilities.

I had to resign from Statik, because it does not support Markdown (or other text format) extensions. And I really really wanted to invoke custom templates from my pages. I was left with Hugo and Nikola. Nikola won because Python.

### Who is behind the site?

So far all the content is written by me ([/u/Xeverous](https://www.reddit.com/user/Xeverous/) on reddit, [Xeverous](https://github.com/Xeverous) on GitHub).

### Can I post on this site?

Yes, just [open an issue](https://github.com/Xeverous/the_website/issues) or make a pull request.

I do not have any strict rules regarding content, but would generally accept anything on topic. In terms of writing itself - the tutorials are mine so I will have the final word on everything (you can always discuss and criticize my wording) but if you want to write your own article - write however you want - just like I have the final word for any of my posts, you have for yours. I will not go in your way of writing, unless you violate some obvious rules like no abusive content, spam, harassment etc.

Note: you have the freedom to choose different license for your articles.

### Can I help with the website?

Yes, and not necessarily by adding content. You can propose anything related to the website build system. I am pretty sure there is a lot of place for improvement. HTML and CSS are not my primary skills. There is also a bunch of Python code that could probably be simplified.

### Why is the content free? Would not selling books or online courses be better for you?

This is a question that can not be answered in 1 sentence, especially to people who ask this with a very strong incentive on money. I have met enough narrow-minded people, constantly approaching my work with attitude like "Why are you working on this?", "Why are you doing something for free?", "Why are you contributing to open source instead of making money from wiriting game bots?".

The answer is hard to grasp and I am not a person that could easily explain this without person-to-person contact so I will suggest instead to:

- Read some interviews with Larry Wales, a co-founder of (non-profit) Wikipedia. He gives a really good and thought-provoking answers on various questions.
- Read [Philosophy of the GNU Project](https://www.gnu.org/philosophy/philosophy.en.html)
