class father():
    def display(self):
        print("father class")
class son(father):
    def displaychild(self):
        print("`son class") 
a=son()
a.display()
a.displaychild()