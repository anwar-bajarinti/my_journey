# a=list(map(int,input("enter elements with spaces").split()))# print(a)
def linear_search(arr, key):
    for i in range(len(arr)):
        if arr[i] == key:
            return i  # Return the index where the element is found
    return -1  # Return -1 if the element is not found

# Taking input from the user
n = int(input("Enter the number of elements in the array: "))
arr = list(map(int, input(f"Enter {n} elements separated by space: ").split()))
key = int(input("Enter the element to search: "))

# Performing Linear Search
index = linear_search(arr, key)

# Displaying the result
if index != -1:
    print(f"Element {key} found at index {index}.")
else:
    print(f"Element {key} not found in the array.")
