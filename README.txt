##C++ SentenceSplitter library with Python interface

###A lightwight utility for c++ and python to process text into sentences.

README.txt for the old distutil distribution:

The splitter module is a text to sentences splitter for python3.9. The module is written in c++ for Debian Bullseye platform only. It may run in other environments, but I have no other environment around, so neither need not opportunity to port it. 

Usage:

```python
from splitter import splitter as split

splittedList = split("en",text_to_split)
```

Requires:

`apt-get install libpcre2-dev` 
`api-get install python3-dev`

Bulding:

run make pymodule (or python3 setup.py build) to see if the module builds on your site. Find a location for the prefixes (/usr/local/share/ssplit default, see src/ssplit.h) and copy them to that location. 

Now python3 test.py should produce some sentences. 

If successfull, install the module with pyhton3 setup.py install. 

By default, setup.py will install the module to Pythons "purelib" directory, which depends a bit on your pyhton environment. In case you want to have it elsewhere, set Install_Dir in setup.py. 

Thats it. 

---

Credits go to ugermann@github.com for the ssplit part, which is the basis of the library, moses-smt@github.com for the prefixes and many other internet sources, providing hints and howto's for c++ issues and python integration. 

Apache 2.0 License:

   Copyright 2023 psmatter@github.com 
   ...
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
   ...

   LGPL2 for the prefixes. (moses-smt@github.com)
   The prefixes are not part of the library, they can be replaced by
   custom made ones if the license is an issue for your use case.



