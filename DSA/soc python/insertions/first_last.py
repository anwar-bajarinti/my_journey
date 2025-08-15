def find_first_and_last(arr, key):
    first = -1
    last = -1

    for i in range(len(arr)):
        if arr[i] == key:
            if first == -1:
                first = i  # Store the index of the first occurrence
            last = i  # Continuously update the index of the last occurrence

    return first, last

# Taking input from the user
n = int(input("Enter the number of elements in the array: "))
arr = list(map(int, input(f"Enter {n} elements separated by space: ").split()))
key = int(input("Enter the element to find first and last occurrence of: "))

# Finding first and last occurrence
first, last = find_first_and_last(arr, key)

# Displaying the result
if first != -1:
    print(f"First occurrence of {key} is at position {first + 1}.")
    print(f"Last occurrence of {key} is at position {last + 1}.")
else:
    print(f"Element {key} not found in the array.")
