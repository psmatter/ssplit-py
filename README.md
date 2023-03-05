## C++ SentenceSplitter Python module

### A lightwight utility for python to process text into sentences.

Written in c++, the module is meant for python3.9 with linux (Debian Bullseye).

### Introduction

I found the ssplit-cpp utility from [ugermann\@github.com][https://github.com/ugermann/ssplit-cpp] to work quite well for splitting text into sentences. All in all the task is less trivial then one might think and from flexibility, language support, ressources and speed ssplit performs great.

In one way or another, the NLP tools have some trainable approaches to split text insto sentences but handling, speed and ressource needs are a handicap. 

The original tool is commandline only, I wanted to have it in python. So I decided to wrap it into a python module. 


### Usage:

From the python side: 

```python
import splitter as split

splittedList = split("en",text_to_split)
```

See doc directory for further information. 

For productive, large scale text processing purposes I'd suggest to use the original tool from ugerman\@github.com. This module is meant more for splitting smaller text portions. 

### Prerequisites

The module is compiled with the vanilla g++, coming with Debian Bullsyes. To compile ist, libpcre2-8 and the python dev kit is needed:

`apt-get install libpcre2-dev` 
`apt-get install python3-dev`

Provide a place for the language prefix files. (default: /usr/local/share/ssplit) and set the `#define PREFIX_DIR` in `src/ssplit.h` accordingly. Copy the files from prefixes directory to that location. 


### Build and Installation

Build the project. A Makefile is provided. Use `make pymodule` or  ` python3 setup.py build` to see if the module gets compiled. If so (check with `python3 test.py`) run `python3 setup.py install` to install the module globally. Now `import splitter` should work outside the project directory. 

See the docs directory for further information. 

### Notes

My first approach was to make the ssplit part separate from the module as shared library. When I started with the pythonic setup, I found it quite tiresome and time consuming, to design the build and installation as I desired it to be. Also I didnt want to use more tools than necessary.  

So the build is done with coreutils. In setup.py a factorial is provided, so the project does not depend on the Makefile. As this is my first python module, I am sure there still is potential for improvement. 

An issue with coreutils is the install path. As installed from the debian maintenance, the modules are installed in the site-packages directory. This may differ for other installations. (I guess the current place to be is /usr/local/lib~/dist-packages). Check setup.py for Install_Dir. 


If there are issues, issue them. I will see what I can do to fix them. 

Make sure the text fed into the splitter is UTF8 or ASCII only. 


### Credits

Credits go to ugerman\@github.com for the ssplit part, which is the basis of the library, moses-smt\@github.com for the prefixes and many other internet sources, providing hints and howto's for c++ issues and python integration. 

### License

Apache License 

   Copyright 2023 psmatter\@github.com 


   Copyright 2019 University of Edinburgh

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.


   LGPL2 for the prefixes. \(moses-smt\@github.com\)
   The prefixes are not part of the library, they can be replaced by
   custom made ones if the license is an issue for your use case.



