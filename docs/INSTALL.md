## C++ SentenceSplitter library with Python interface

### A lightwight utility for c++ and python to process text into sentences.

### Install notes

As far as I happen to use ssplit on other systems, I will update the installation notes here.

Make sure to build/install with python3 -m setup or python3 setup.py. 

## Ubuntu 16 (Bionic)

```
apt-get install libpcre2-dev python3-dev g++-8
```

Edit the Makefile:
```
CC=g++-8
INCLUDE_PATH = $(SRCDIR)/ -I/usr/include/python3.6/
LIBS = -lpcre2-8 -lpython3.6m -lstdc++fs
```

Now ```python3 setup.py build``` and ```python3 setup.py install``` should work.

On the old Ubuntu box, python versions from 2.7 to 3.8 were installed. Pyhton3 was linked to python3.6. Due to 3.6 sysconfig issues, splitter.so went to /usr/lib/python3.6/site-packages/splitter, but was assumed to be in /usr/local/lib/python3.6/dist-packages/splitter. So even if the import worked, using splitter resulted in a TypeError. Since the 3.6 sysconfig did not have the dist dir in paths, the simplest solution was to copy splitter.so to /usr/local/lib/python3.6/dist-packages/splitter. 

The usage was a little different as from the 3.9 install:

```python
from splitter import splitter as split
t=split.splitter('en','1234')
t
['1234']
```
