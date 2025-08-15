class father():
    def display(self):
        print("father class")
class son(father):
    def displaychild1(self):
        print("`son class")
class daughter(father):
    def displaychild2(self):
        print("daughter class")
a=son()
a.display()
a.displaychild1()
b=daughter()
b.display()
b.displaychild2()
