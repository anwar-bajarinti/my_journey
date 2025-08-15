with open("text3.txt","r") as f:
    data=f.read()
word="anwar"
data=data.replace(word,"he")
with open("text3.txt","w") as f:
    f.write(data)