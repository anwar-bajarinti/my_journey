def binary_search(arr, key):
    low, high = 0, len(arr) - 1

    while low <= high:
        mid = low + (high - low) // 2  # Prevents overflow

        if arr[mid] == key:
            return mid  # Element found, return index
        elif arr[mid] < key:
            low = mid + 1  # Search in the right half
        else:
            high = mid - 1  # Search in the left half

    return -1  # Element not found

# Taking input from the user
n = int(input("Enter the number of elements in the sorted array: "))
arr = list(map(int, input(f"Enter {n} sorted elements separated by space: ").split()))
key = int(input("Enter the element to search: "))

# Performing Binary Search
result = binary_search(arr, key)

# Displaying the result
if result != -1:
    print(f"Element {key} found at position {result + 1}.")
else:
    print(f"Element {key} not found in the array.")
