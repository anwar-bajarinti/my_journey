def count_occurrences(arr, key):
    count = 0
    for element in arr:
        if element == key:
            count += 1
    return count

# Taking input from the user
n = int(input("Enter the number of elements in the array: "))
arr = list(map(int, input(f"Enter {n} elements separated by space: ").split()))
key = int(input("Enter the element to count occurrences of: "))

# Counting occurrences
count = count_occurrences(arr, key)

# Displaying the result
if count > 0:
    print(f"Element {key} occurs {count} times in the array.")
else:
    print(f"Element {key} not found in the array.")
