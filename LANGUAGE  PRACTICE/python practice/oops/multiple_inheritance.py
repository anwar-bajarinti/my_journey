class father():
    def displayf(self):
        print("father class")
class mother():
    def displaym(self):
        print("mother class")
class son(father,mother):
    def displays(self):
        print("son class")
a=son()
a.displays()
a.displayf()
a.displaym()