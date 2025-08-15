import random
def get_winner(comp,user):
    if comp==user:
        return "Tie"
    elif(comp=="snake" and user=="water") or (comp=="water" and user=="gun") or (comp=="gun" and user=="snake"):
        return "Computer"
    else:
        return "User"
computer=random.choice(["snake","water","gun"])

print("User chose between snake,water and gun")
you=input("Enter your choice: ")
print(f"Computer chose {computer}")
print(f"User chose {you}") 
print(f"Winner is {get_winner(computer,you)}")
