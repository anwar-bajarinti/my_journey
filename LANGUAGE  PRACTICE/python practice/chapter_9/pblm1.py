with open("text2.txt") as f:
    data=f.read()
if "twinkle" in data:
    print("Twinkle is present")
else:  
    print("Twinkle is not present")