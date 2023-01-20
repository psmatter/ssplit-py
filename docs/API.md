##C++ SentenceSplitter library with Python interface

###A lightwight utility for c++ and python to process text into sentences.

###Python API

The default usecase for the module is simple, just import it, drop in some text and get a python list with the sentences, terminated by "\n".

splitter(language, text)

language: Country code (prefices in default location)
          or path of the preix file. 
          Default: language en (with argument None)

text    : Ascii/UTF-8 text string. Larger texts should be 
          split into more memory friendly portions 
          




```python
import splitter as split
text="This is a text.\n One line two sentences. We have more than one line. Here is another.\n We have more. \n"

print("Test input to splitter:",text)

t_list = split("en",text)

print("Python got ",len(t_list)," lines back, splittet as:")


for i in range(len(t_list)):
    print("set:",t_list[i])


print(*t_list, sep = ":\n")
```

