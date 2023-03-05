from lib import splitter 
text="This is a text.\n One line two sentences. We have more than one line. Here is another.\n We have more. \n"

print("Test input to splitter:",text)

t_list = splitter.splitter("en",text)

print("Python got ",len(t_list)," lines back, split as:")


for i in range(len(t_list)):
    print(i+1,":",t_list[i])


print(*t_list, sep = ":\n")

print("------------------------")

text='This is anoter text. We have sentences but no linebreaks. 3 sentences.'

t_list = splitter.splitter("en",text)

for i in range(len(t_list)):
    print(i+1,":",t_list[i])
