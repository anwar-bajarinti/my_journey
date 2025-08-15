class father():
    def dis(self,a,b):
        self._a=a
        self.__b=b
class son(father):
    def display(self,c):
        print("son class")
        print(self._a)
        self._c=c
        print(self._c)
a=son()
a.dis(2,3)
a.display(10)
