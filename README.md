# The C++ website project

It is well-known that C++ has bad teaching reputation. This project aims to create a statically-hostable website (no backend required) that will contain community-maintaned official or pseudo-official C++ learning material.

Currently the project is in a very early state. No hosting has been set up yet as there isn't anything significant to display and there is huge volatility in article structure/order (which invalidates links).

More project info (building, writing etc) can be found in `notes` directory.

## Core goals

- Open-source collaborative project.
- Proper C++ teaching (that is, teaching C++, [not C or C with classes](https://www.youtube.com/watch?v=YnWhqhNdYyk)) also including exerices, common conventions and mistakes.
- Be ready to make any sort of cooperation with SG20 (C++ committee learning and teaching study group).

## Contributing

- More info about the project in [this reddit post](https://www.reddit.com/r/cpp/comments/ns4hl5/what_do_you_think_of_learning_c_through_online/).
- To avoid "design by committee" issues, currently I want to suspend merging article contributions. I don't want to end up with a bucket of random C++ articles with no order. Submissions are welcome, but the order of content can be significantly changed and there is no guuarantee when a PR can be merged.
- You can still help:
  - Suggest a unique and catchy name and/or logo for the project. Best if you can reference some C++ memes.
  - There are few pinned issues for discussion. You can contribute just by engaging in them.
  - If you think you can explain some specific part of C++ well (not just the language, tooling and other stuff is also welcome) open an issue and/or create a PR (it will be merged at some point). So far most of the trouble is in making good examples and figuring out best order of lessons.
  - If you have any experience with web tech (here: HTML, Jinja2, CSS, vanilla JS) or with static site generators the help will be valuable as I'm not a web developer. The current website build implementation is good enough to be rendered but still can get significant improvements. Any comments/suggestions on website build process are also welcome.
