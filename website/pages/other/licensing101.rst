.. title: licensing 101
.. slug: licensing101
.. description: licensing software, art and other works - everything you need to know
.. author: Xeverous

.. admonition:: note
    :class: note

    This is not a legal advice. The article aims to explain licensing and related concepts for software and other works but should not be used as a definitive way of making decisions. If you have a question concerning specific situation consult a law professional.

.. admonition:: note
    :class: note

    A lot of links in this article refer the GNU project and FSF (Free Software Foundation) websites. This is not by accident - FSF played a major role in initiating the free (read *freedom*, not *zero price*) software movement.

You very likely have seen different projects with different licenses. So what is it all about?

Why license
###########

There are numerous reaons why you should license your work:

- it allows others to do specific things with your work that you want
- it prevents others from doing specific things with your work that you do not want
- it makes the situation much clearer for everyone (especially for potential contributors)
- it's much better than writing a list of rules by your own as already existing licenses are very detailed and are legally recognized by various institutions

    What happens if I don't license my work?

All works (not just software) automatically get "All rights reversed" unless stated otherwise. This isn't inherently bad, but generally makes any sort of reuse and redistribution illegal so if you want even slightest incentive for others to make use of your work other than just looking at it, you should decide on a specific license. Note that if you publish your work somewhere (especially online), you implicitly agree to this place's rules which might immediately grant some rights for users (e.g. ability to see and copy it). More info on https://choosealicense.com/no-permission/.

If you want the opposite - maximum freedom for users with no desire to preserve specific rights as the author, you can state that you dedicate your work to the *public domain* and voluntarily resign from all rights.

Public domain
#############

*The public domain consists of all the creative work to which no exclusive intellectual property rights apply. Those rights may have expired, been forfeited, expressly waived, or may be inapplicable.*\ [wiki_PD]_

Almost any work sooner or later will become public domain. Various jurisdictions place different periods for different works (from 10 years to the point of author's death and many different conditions) so the situation is a bit complicated. Fortunately for vast majority of works by the time they go to the public domain all potential benefits were already gained by the author.

There is only 1 thing which you can not do with public domain work: claiming you did it. The fact who did the work is irrevocable.

Proprietary licenses
####################

This isn't main focus of the article but it's worth to mention proprietary licenses as a contrast to all open licenses.

Such licenses are typically very restrictive:

- usually allow to obtain the work only in the final form (e.g. compiled code, raster image without layers) without access to the source (e.g. source code, vector graphics with layers and metadata)
- they limit or disallow copying
- they disallow modifications and reverse engineering

The main point of such licenses is to prevent users from using the work in ways other than the very narrow set intended by the author. The main motivation is to prevent copying, reverse engineering and other uses which can significantly harm profits of the author.

Majority of commercial products use proprietary licenses. Usually each product has it's own specific license. I'm not aware of any reusable proprietary license.

Open licenses
#############

The main goal of open licenses is allowing users to do much more than a typical proprietary license and at the same time preventing absolute exploitation of the author's work. Various open licenses aim to create a win-win situation where users can enjoy larger freedom and the author can keep benefits of the work (not necesserarily money).

When choosing an open license, the primary difference between them is the level of openness:

- High: allowing basically any type of redistribution and derivative work which can greatly increase work popularity and reusability but also significantly limit potential benefits of the author.
- Low: allowing a smaller set of priviledges for the users but keeping a lot of author's rights.

We can say that public domain is the ultimate "maximum open" variant and typical proprietary license is the ultimate "minimum open" variant. Obviously there are lots of licenses in between.

No matter the type of the work, vast majority of open licenses share these elements:

- distribution and modification: the work can be freely distributed and modified

  - some licenses require an attribution of the original work
  - some licenses require to state changes
  - some licenses require source discloure and/or same license for derivative work

- private use: derivative works can violate license requirements as long as the use remains private
- limited liability / no warranty / no trademark - even though not required, most licenses will state explicitly that they grant no warranty and trademark rights
- commerciality: explicit permission or prohibition of commercial use of the work

There are 2 main kinds of open licenses:

- permissive
- copyleft[wiki_copyleft]_\ [GNU_copyleft]_

Both grant a large array of rights but copyleft licenses have 2 additional requirements:

- all derivative work must be under the same license
- all derivative work to be available in the preferred working form (that is source code with no obfuscation)

Advantages of copyleft:

- The work is protected from some forms of reuse which could be generally thought as theft and abuse. Basically same fair play game as with SA variants of CC licenses, which force derivative works to "give back" to the original author.
- If someone creates a copyleft-derivative work and commercializes it, everyone can do it aswell as the license requires source disclosure. In practice this incentivizes people to cooperate instead of agressively copying and selling each other's versions.

Disadvantages of copyleft:

- A lot of potential users (especially programmers and businesses who would like to use the project as a 3rd party library) will be turned off by the license as it effectively forces them to license their entire project under exact same terms.
- It significantly limits *license compatibility* of such work.
- It's very hard to get large amount of uses of a copyleft project in a place where there are alternatives with permissive licenses.

License domains
###############

Not every license is applicappble to every type of work. We can distinguish 2 primary domains in which majority of open licenses operate:

- software
- creative works (sounds, images, modelling etc.) (not necesserarily in digital or analog form) referred later as *art*

Some works require more specific licenses:

- Databases - there are various concerns regarding privacy.
- Fonts - modern font formats often combine art with some software. Designing a typeface is definitely an artistic work but because of various technical peculiarities modern fonts also embed a sort of virtual machine code that instructs rendering software how to handle specific details. This makes fonts a combination of both, a situation which some deemed significant enough to design licenses specifically for fonts.
- Hardware - I see more and more projects with the goal of open hardware specification. Hardware is definitely different from software but I don't know exact reasons why they need separate license. Probably `dual-use <https://en.wikipedia.org/wiki/Dual-use_technology>`_ concerns.

Obviously you should choose an appropriate license, made for your type of work. Otherwise, the exact terms and conditions become unclear and you risk various problems caused by dubious interpretation.

    What if my work mixes multiple types?

Generally, you can apply multiple licenses and/or divide your work into smaller parts. More further down the article.

Art licenses
############

We start with licenses for art as their situation is simpler than software and many of readers may be familair with Creative Commons or at least have reused some of the work under one of their licenses (usually work available on Wikipedia or its sister websites).

*Creative Commons is a global nonprofit organization that enables sharing and reuse of creativity and knowledge through the provision of free legal tools.*\ [CC]_

The organization has created a set of licenses with varying rights and conditions for users. All of the variants are different compositions of their core elements. We will start with the simplest one and move towards more rich variants.

CC0
===

CC0 is the equivalent of public domain. It's primary purpose is to satisfy authorities where a dedication to the public domain meets any problems. The license text effectively grants users all rights to the work just like public domain but the fact that the license is an explicit legal text make it beneficial in some jurisdictions.

A lot of work licensed under CC0 also lists public domain as a choice so that the user can choose one from both according to their needs (more on applying multiple licenses later).

CC-BY
=====

This license is like CC0 but adds one condition - **attribution of the author**. Every copy and derivative project must contain information who did the original work.

To avoid interpretation problems, many authors explicitly state in their project how their work should be referenced (usually author's name and a link to original source).

This license gives almost unlimited freedom for users of the work (as long as attribution condition is satisfied, everything is allowed including commerciality and any modifications) but at the same time ensures that the author will not be forgotten. For some projects alone (if they become popular enough) it's enough to guuarantee significant recognition for the author.

CC-BY-SA
========

Like CC-BY but with added condition, known as **share-alike**. It requires any derivative work to be licensed exactly the same.

The primary benefit of SA is that if any derivative work appears, author of the original work can automatically reuse it because all modifications are under same license. This creates a situation where all editors play a fair game of reusing other's work.

CC-BY-ND
========

Like CC-BY but with added condition: **no derivative work**.

CC generally discourages ND variants as disallowing derivative work significantly reduces project reusability and popularity. The whole point of openness is to allow other people to modify the work.

CC-BY-NC
========

Like CC-BY but with added condition: **non-commercial**.

CC generally discourages NC variants as disallowing commerciality significantly reduces incentive to reuse the work. In many cases the lack of NC is what makes the project so popular which ultimately leads to monetary benefit of the author.

Other CC variants
#################

Based on previous explanations you should easily understand remaining variants:

- CC-BY-NC-SA
- CC-BY-NC-ND

CC summary
##########

An image for easier remembering:

.. image:: https://creativecommons.org/wp-content/uploads/2019/11/cc_license_spectrum-633x1024.png
    :alt: CC license spectrum

If you are working on some project and are undecided on its license, Creative Commons recommends CC-BY-SA. ND and NC greatly disincentivize users (read: potential investors) while BY and SA are standard elements of `free cultural works <https://en.wikipedia.org/wiki/Free_content>`_.

CC Licenses briefly explained: https://creativecommons.org/about/cclicenses/

CC FAQ: https://creativecommons.org/faq

Software licenses
#################

The situation here a bit more complex than with art as software faces many technical peculiarities. The primary organization in play here was `FSF <https://en.wikipedia.org/wiki/Free_Software_Foundation>`_ but numerous other organizations have created their licenses too, many of which also are in wide use today. A lot of software licenses have analogical elements to CC licenses, they just are better suited towards licensing code.

As previously, we start with most permissive ones but in this case I list only popular ones. The spectrum is much wider here, some licenses aren't a straight increase/decrease in conditions and permissions. There are many more software licenses than mentioned in this article.

The Unlicense, BSD 0-clause
===========================

Both analogically equivalent to CC0 - public domain but as an explicit legal text. No conditions whatsoever.

BSL
===

Boost software license is one of the most permissive software licenses, only requiring license and copyright notice in the source form.

It's not strictly analogous to CC-BY because in case of BSL the attribution is only required for distribution in the source form. Compiled code and other binary forms are not required. This detail makes BSL more appealing for some projects, e.g. embedded where providing a license notice with the final form can be troublesome.

zlib license
============

Like BSL, but has an additional condition that modified source must be marked as such.

MIT
===

MIT and Apache 2.0 are the most popular of the permissive type of licenses, analogic to CC-BY. MIT, unlike zlib, doesn't require to state changes but all works have to reproduce license text, not just source form.

GNU recommends to call MIT license as Expat due to (probably past) ambiguities. See https://www.gnu.org/licenses/license-list.html#Expat for more information.

Apache 2.0
==========

Apache 2.0 license is very similar to MIT, with following differences:

- it explicitly states it does not grant any trademark rights, even though licenses without such a statement probably do not grant any implicit trademark rights under any jurisdiction
- it explicitly provides an express grant of patent rights from contributors

Patenting software is a controversial topic. Critics argue that you can't patent code or algorithms, just like you can not patent other abstract ideas like mathematical formulas or stock characters. In jurisdictions where patenting software is not a thing, Apache 2.0 license is basically same as MIT.

BSD
===

Berkley Software Distribution refers to multiple permissive licenses. They have no explicit numbering but their short names refer to the amount of clauses it had, newer versions having less.

- BSD 4-clause - has an "advertising clause" that requires an acknowledgment of the original source in all advertising material (GNU considers this clause non-free, incompatible with GPL)
- BSD 3-clause "new" - has no advertising clause
- BSD 3-clause "clear" - has no advertising clause and explicitly does not grant any patent rights
- BSD 2-clause "simplified" - like 3-clause "new" but without forbidding of using names of copyright holder and contributors to promote and endorse derivative works
- BSD 0-clause - no conditions, no mention of patents but at the same time no explicit dedication to the public domain

`This article on GNU's website <https://www.gnu.org/licenses/bsd.html>`_ explains why the advertising clause in the 4-clause version was problematic.

MPL
===

Mozilla Public License is on the border between typical permissive licenses like MIT and copyleft licenses like GPL.

This license text is pretty long (compared to others) but offers specific compromise between permissive and copyleft approach:

- Modifications of the *Covered Software* must be released under same license. If *Covered Software* is not *Incompatible with Secondary Licenses* it may also be released under *Secondary Licenses*.

  - Incompatibility is present when the license has its *Exhibit B* attached.
  - *Secondary Licenses* are GNU GPL 2.0, GNU LGPL 2.1, GNU AGPL 3.0 or any later version of these.

- *Larger Work* can be distributed under other licenses as long as the *Covered Software* is made compliant with MPL.

  - *Covered Software* must have attached full license or *Exhibit A* (short license notice) and disclosed source code.

*Covered Software* means *Source Code Form* to which the initial *Contributor* has attached the notice in *Exhibit A*, the *Executable Form* of such *Source Code Form*, and *Modifications* of such *Source Code Form*, in each case including portions thereof. For definitions of other terms, see exact license text. I only wrote enough to make it understandable (it's pretty long compared to other licenses).

In short, MPL works as GPL for the *Covered Software* (being interchangable with GNU licenses if without *Exhibit B*) but *Larger Work* can be distributed on different terms. This makes MPL projects protected like GPL ones but only to to point of modification. If someone creates something on top of MPL code, only modified portions of MPL code are under copyleft requirements.

GNU licenses
============

FSF released 3 licenses, each with different level of copyleft:

- LGPL: Lesser General Public License
- GPL: General Public License
- AGPL: Affero General Public License

GPL is the standard copyleft license - all derivative works have to be licensed under same license and have source code disclosed. Analogical to CC-BY-SA.

LGPL is like GPL but permits dynamically linked code to be distributed under different license. This is slightly less restrictive than GPL and slightly more restrictive than MPL because MPL permits any larger work while LGPL specifically states that for this "border" to work the larger work must be linked dynamically. If compiled LGPL source code is linked statically to other compiled source code, the entire object must be licensed under LGPL.

AGPL is the stricter version of GPL, stating that use over network is also considered distribution. When a modified version is used to provide a service over a network, the complete source code of the modified version must be made available. This is to prevent abuses of network-related projects where someone could use network connection to create a barrier that would allow to bypass requirements of modified GPL software.

GPL 2.0 is incompatible with GPL 3.0. The latter explicitly states it allows 3.0 or any newer version, the former does not. GPL 3.0 was made to address abuses like `Tivoization <https://en.wikipedia.org/wiki/Tivoization>`_ which effectively blocked one of GNU's intended `4 essential freedoms <https://www.gnu.org/philosophy/po/free-sw.ml-en.html#four-freedoms>`_. Additionally, GPL 3.0 disallows `DRM <https://en.wikipedia.org/wiki/Digital_rights_management>`_ which Richard Stallman likes to call "Digital Restrictions Management". A full explanation is available at https://www.gnu.org/licenses/rms-why-gplv3.html.

GNU generally recommends:

- GPL 3.0 for new projects
- `LGPL 3.0 for some projects due to pragmatic reasons <https://www.gnu.org/licenses/why-not-lgpl.html>`_
- `CC-BY-ND for essays of opinion and scientific papers <https://www.gnu.org/licenses/licenses.html#OtherWorks>`_
- GFDL for documentation

Full article on https://www.gnu.org/licenses/license-recommendations.html.

GPL FAQ: https://www.gnu.org/licenses/gpl-faq.html.

Extra licenses
##############

Licenses aimed at specific works that aren't strictly art or software.

GPL for Fonts
=============

GPL can be used for fonts, with and without its exception. Without the exception, a document embedding the font also has to be licensed under GPL.

- https://www.gnu.org/licenses/gpl-faq.html#FontException
- https://www.fsf.org/blogs/licensing/20050425novalis

SIL OFL 1.1
===========

Copyleft license for fonts but incompatible with GPL.

(sic. from https://www.gnu.org/licenses/license-list.html#SILOFL) *Its only unusual requirement is that when selling the font, you must redistribute it bundled with some software, rather than alone. Since a simple Hello World program will satisfy the requirement, it is harmless. Neither we* [GNU] *nor SIL recommend the use of this license for anything other than fonts.*

GFDL
====

*The GNU Free Documentation License is a form of copyleft intended for use on a manual, textbook or other document to assure everyone the effective freedom to copy and redistribute it, with or without modifications, either commercially or non-commercially.*

GFDL main purpose is to be GPL equivalent for documentation. More on https://www.gnu.org/licenses/licenses.html#FDL.

FreeBSDDL
=========

Permissive non-copyleft free documentation license, compatible with GFDL.

ODbl
====

`Open Data Commons Open Database License <https://choosealicense.com/licenses/odbl-1.0/>` is meant to be GPL equivalent for databases. It is not compatible with GPL and GFDL due to (sic.) *inconvenient requirements about signing contracts which try to create an effect like copyleft for data that is not copyrightable*\ [GNU_ODbl]_\ but GNU states (sic.) *there is no reason to avoid using data released this way*.

Linux kernel
############

The Linux kernel is very often given as an example of a great open project. Some noteworthy facts:

- The project is licensed under GPL 2.0, without "or any later version" clause and with an explicit syscall exception (Linux-syscall-note) so that programs that rely only on kernel's interface are not considered derivative works. This allows non-GPL code to run on Linux without license violations (GCC has similar explicit exception for the runtime of its toolchain).

  - Linus Torvalds has described licensing Linux under the GPL 2.0 as the "best thing I ever did".[Torvalds_GPLv2]_
  - Linus Torvalds decided not to adopt GPL 3.0 for the project and continues to be against it.[Torvalds_GPLv3]_
  - Linux kernel for a long time has been including binary blobs, which are proprietary, in its source tree and main distribution.

- Even though the primary goal of GPL is FOSS, **`not all GNU/Linux distributions are considered free by GNU <https://www.gnu.org/distros/free-distros.html>`_**. The views of Richard Stallman (FSF) and Linux Torvalds (Linux) regarding free/open/proprietary software are significantly different.

Applying a license
##################

For software there is a very strong convention: a file named ``LICENSE`` or ``COPYING`` (extension may vary, usually none or ``txt``) in the root directory of the repository. Additionally, very often all source code files will contain a comment at the top with short license notice. If distributed in the compiled form, it should be bundled with documentation.

For other works, if they use a medium capable of transmitting text or image (especially books and movies), the license (either a note/link or its full form) is provided at the beginning/cover or at the end of the work. Almost any type of creative work has at least a place to put the title and/or author's name so if there is no better place for a license notice this can be used too.

SPDX
====

*The Software Package Data Exchange® is an open standard for communicating software bill of material information, including components, licenses, copyrights, and security references. SPDX reduces redundant work by providing a common format for companies and communities to share important data, thereby streamlining and improving compliance.*

*The SPDX specification is an international open standard (ISO/IEC 5962:2021).*

SPDX is probably best known for `it's list of license IDs <https://spdx.org/licenses/>`_ which are commonly found within comments at the top of files belonging to open projects.

.. image:: https://spdx.dev/wp-content/uploads/sites/41/2017/12/spdxbookmark_small.png
    :alt: SPDX infographic

Multiple licenses
#################

There is nothing stopping you from offering the same work under multiple licenses (as long as the work is yours or all contributors agreed to it). Some projects have multiple (usually similar) licenses in order to achieve higher license compatibility with potential derivative works. Some projects are offerred under both open source and proprietary licenses - the goal is to allow users to obtain proprietary license (for a price) if they do not want to satisfy requirements stated in the open one.

Typical combinations are:

- CC0/The Unlicense + dedication to the public domain
- MIT (Expat) + Apache 2.0
- MPL/LGPL/GPL + any later version of these + proprietary

Changing a license
##################

It's possible to change a license. You just need to have an agreement from contributors as they have provided their work under specific terms.

In some projects, there is a contributor agreement required prior to any contributions, some may state that contributors grant patent rights and allow the owner to change the license. If not, the owner must ask contributors for the permission to change the license. See https://en.wikipedia.org/wiki/Software_relicensing for many historical examples.

Be aware that users of the work might react negatively to license change, especially if the new license has more requirements and/or is incompatible with already existing derivative works.

Lastly, law does not apply to the past: all previous versions of the work retain the license they were released with. Even if you change the license, everyone has the right to continue using old versions of the work under terms these versions were released.

License compatibility
#####################

It's possible to create a project where multiple subprojects are licensed differently, the final work just has to:

- satisfy all requirements of licensed subprojects
- offer no more rights than licensed subprojects

This means that **generally**:

- ...the most restrictive license has to be applied to the whole work.
- ...permissive licenses are compatible with each other as all of them allow relicesing derived works, usually with no or simple requirements like attribution.
- ...copyleft licenses are not compatible with each other as almost every one requires the project under exactly the same license.

Examples
========

Suppose a project where:

- one part is under MIT
- one part is under GPL
- one part is your own work

Then, no matter how you want your work to be licensed, the entire project must be licensed under GPL.

Another example:

- one part is Apache 2.0
- one part is modified MPL
- one part is LGPL
- one part is your own work

Then, as long as you link LGPL part dynamically, you only need to release changes to the MPL part. The entire work can have a different license.

When it comes to CC licenses for creative works the situation is trivial - each variant has clear list of conditions. If there is no SA (share-alike) (copyleft) condition, you can create derivative works with different license.

Resources about license compatibility:

- https://en.wikipedia.org/wiki/License_compatibility (contains some diagrams)
- https://www.gnu.org/licenses/license-compatibility.html
- list of licenses (in)compatible with GPL and GFDL: https://www.gnu.org/licenses/license-list.html
- permission/condition/limitation matrix of various licenses: https://choosealicense.com/appendix
- https://creativecommons.org/share-your-work/licensing-considerations/compatible-licenses

.. Unfinished graph of license compatibility

.. GNU AGPL 3.0+ -> GNU GPL 3.0+ -> GNU LGPL 3.0+ -> MPL 2.0 (without Exhibit B) -> Apache 2.0 -> Expat | X11 | ISC -> BSL 1.0 -> BSD 0-clause -> Unlicense | CC0
.. GNU GPL 2.0+ -> GNU LGPL 2.1
.. GNU GPL 2.0+ -> Artistic License 2.0
.. BSD 4-clause -> BSD 3-clause new -> BSD 2-clause -> Expat | X11 | ISC
.. GNU GPL 2.0+ -> BSD 3-clause clear -> BSD 2-clause
.. GNU GPL 2.0+ -> EPL 2.0 with designation
.. GNU GPL 2.0+ -> Zlib
.. GNU GPL 3.0 -> Freetype
.. GNU GPL 3.0 -> CC BY-SA 4.0
.. GNU AGPL 3.0+ -> CeCILL 2.1
.. GNU GPL 2.0+ -> CeCILL 2.1

.. GFDL -> FreeBSDDL

.. Projects under EUPL can be made compatible with CeCILL 2.1 and GPL 2.0+ but `there is some effort requried <https://www.gnu.org/licenses/license-list.html#EUPL-1.1>`_

FAQ
###

    Are there software license equivalents of CC's ND and NC variants?

No. I presume the reasons are:

- NC is just pointless. Sooner or later any worthy software finds commercial application and forbidding this would basically block the development. If you are scared someone could reuse your work for their financial benefit just use one of the strongest copyleft licenses (GPL or AGPL) - if they do you will be able to do the same.
- ND is even more pointless. Code is constantly changed.

..

    If I choose a license that has no NC condition or equivalent (that is, it allows derivative works to be sold) isn't it removing primary benefit of my work? I could create something and someone else could gain all the money for selling my altered work.

Not always. The lack of NC may greatly increase popularity of your work which in turn can led you to obtain numerous benefits including sponsorship or a specific job offer. So it's possible that without non-commercial condition you can actually end up with more money. Whether a given work would be better with or without NC is a question really hard to answer. IMO Jimmy Wales (founder or co-founder of Wikipedia) gives very good answers when asked why the website is free (just search for any interview).

    GCC and related libraries (especially libgcc and libstdc++) are licensed under GPL. Does it mean if I use these in my projects all my work has to be licensed under GPL?

GCC and related libraries are licensed under GPL, but the contain *Runtime Library Exception*. This exception allows to ignore GPL requirements as long as (sic.) *all Target Code was generated by Eligible Compilation Processes*. Exact details are explained on https://www.gnu.org/licenses/gcc-exception-3.1-faq.html. In the simplest case, if you are using GNU libraries as your runtime (e.g. libstdc++ as the implementation of the C++ standard library) (statically or dynamically) code depending on it is not considered derivative work and GPL does not apply to it.

    If my C or C++ code includes Linux system headers, isn't my work derivative given Linux is licensed under GPL 2.0?

Similarly to GCC's *Runtime Library Exception* Linux has *Linux syscall exception* which does not consider works derivative if they only use the headers to compile the program.

    Can I compile non-GPL code with GCC without license requirements?

Yes. In such case GCC is only a tool used to create the work. It's not a part of the work.

    Are FOSS, CC, FSF or other movements/organizations against copyright or capitalism?

Absolutely not. Open licenses are just a different form of copyright, often aimed at making best use of capitalism based on the idea of voluntary trade between parties. Open licenses specify how this "trade" is supposed to happen and given the fact that any "trade" (here: use of the work under specific conditions stated in the license) is voluntary it's a win-win situation for both parties. It's not so rare to see a company which will sponsor a FOSS project and/or ask the maintainers to do some modifications for a price. Other companies develop projects with copyleft licenses and offer private proprietary licenses (Qt is a good example of such project).

    Did someone really asked the previous question?

No, but some people greatly misinterpret the meaning of FOSS movement and some people involved in free software movement have even been accused of communism [citation needed]. All such accusations had no solid reasoning and were usually (if not only) from proprietary software companies made in order to stop them from sharing FOSS that was seen as a competition.

FOSS vs open-source
###################

FOSS stands for *free and open source software*. **The word free here does not mean "zero price" but "freedom".**\ [GNU_free]_ FOSS does not have to be non-commercial.

Open-source is a subset of FOSS. A prime example of a project that is open-source but not *free* (in FSF terminology) is Visual Studio Code:

- The repository is open and licensed under MIT
- Official Microsoft's releases have `specific, different non-open license <https://code.visualstudio.com/license>`_ and contain closed-source telemetry
- The extension marketplace is proprietary to Microsoft and only Microsoft products are allowed to use it
- Several extensions are proprietary to Microsoft, this includes some of Microsoft's official C++, C# and remote development tools

The FOSS version of VS Code is VS Codium - https://vscodium.com/

More information:

- https://www.gitpod.io/blog/open-vsx/
- https://github.com/VSCodium/vscodium/blob/master/DOCS.md

Intellectual property
#####################

`GNU criticizes this term <https://www.gnu.org/philosophy/not-ipr.html>`_ as it tries to bundle copyright, patenting, trademark and other laws under one term which only causes more confusion and uncertainty.

Cryptography
############

Various jurisdictions place requirements on cryptographic software. Today's assymetric algorithms are practically unbreakable. Some jurisdictions place hard requirements like intentional backdoors for the government and other jurisdictions consider such actions a violation of their consitutional law (privacy and free speech).

More information: http://www.cryptolaw.org/

License violations
##################

Majority of license violations are for projects under GPL and other copyleft licenses.

- https://www.gnu.org/licenses/gpl-violation.html
- https://gpl-violations.org lists more than 100 cases

Generally, if any lawsuit appears, it can be separated into 2 parts:

- requirement to cease the violation
- recompensation for damages

If a GPL-like license is violated, requiring to release all source code is only the first part - ensuring compliance. The second part is more complex and its finale will generally depend where the lawsuit was filed and what organizations were involved. In some cases the parties finish on a monetary agreement.[wiki_litigation]_

Limitations and exceptions to copyright
#######################################

Various jurisdictions define different terms that limit copyright or provide some exceptions. These aim to prevent abusive licensing and help general public interest. There is no large international consensus on copyright limitations and exceptions so I list only core elements:

- `Idea-expression distinction <https://en.wikipedia.org/wiki/Idea%E2%80%93expression_distinction>`_ - ideas can not be copyrighted, only their expression. For example, a book or a movie can be copyrighted but the idea of specific character/story (e.g. femme fatale) can not. This exception also applies to abstract science - it's not possible to copyright mathematical formulas or discovered laws of physics.
- Threshold of originality - the work must be original enough, must contain sufficient effort in order to be copyrightable. How exactly the threshold is defined and whether given work achieves it is very subjective.
- Fair use/dealing - ability to ignore copyright under specific circumstances for the benefit of general public (usually very extreme circumstances like saving lifes in a natural disaster). The simplest case is the right to quote - you don't need to ask the author for permission when your work quotes parts of other's work.

More
####

Additional resources you might be interested in:

- https://tldrlegal.com/ - software licenses in plain english
- https://www.gnu.org/philosophy/philosophy.html
- https://en.wikipedia.org/wiki/Limitations_and_exceptions_to_copyright
- https://en.wikipedia.org/wiki/Fair_dealing
- https://en.wikipedia.org/wiki/Fair_use
- https://en.wikipedia.org/wiki/Right_to_quote
- https://en.wikipedia.org/wiki/Threshold_of_originality
- https://en.wikipedia.org/wiki/Freedom_of_panorama

----

.. [CC] https://creativecommons.org/faq/#what-is-creative-commons-and-what-do-you-do
.. [GNU_free] https://www.gnu.org/philosophy/free-sw.html
.. [GNU_copyleft] https://www.gnu.org/licenses/copyleft.html
.. [GNU_ODbl] https://www.gnu.org/licenses/license-list.html#ODbl
.. [wiki_copyleft] https://en.wikipedia.org/wiki/Copyleft
.. [wiki_PD] https://en.wikipedia.org/wiki/Public_domain
.. [wiki_litigation] https://en.wikipedia.org/wiki/Open_source_license_litigation
.. [Torvalds_GPLv2] https://web.archive.org/web/20070210224351/http://hotwired.goo.ne.jp/matrix/9709/5_linus.html
.. [Torvalds_GPLv3] https://www.youtube.com/watch?v=PaKIZ7gJlRU
