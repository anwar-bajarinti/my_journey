class gf():
    def disgf(self):
        print("grandfather class")
class f(gf):
    def disf(self):
        print("father class")
class s(f):
    def diss(self):
        print("son class")
a=s()
a.disgf()   
a.disf()
a.diss()
