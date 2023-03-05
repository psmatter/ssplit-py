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


