def find_insert_position(arr, target):
    left, right = 0, len(arr) - 1

    while left <= right:
        mid = left + (right - left) // 2

        if arr[mid] == target:
            return mid  # Element found, return its index
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    # Return the position where the element should be inserted
    return left

# Example usage
arr = [1, 3, 5, 6, 8, 10, 12]
target = int(input("Enter the element to insert: "))

position = find_insert_position(arr, target)
print(f"The element should be inserted at index: {position}")
