def quick_sort(arr):
    if len(arr) <= 1:  # If the array has 0 or 1 element, it's already sorted
        return arr

    pivot = arr[len(arr) // 2]  # Choose the middle element as the pivot
    left = [x for x in arr if x < pivot]  # All elements less than the pivot
    middle = [x for x in arr if x == pivot]  # All elements equal to the pivot
    right = [x for x in arr if x > pivot]  # All elements greater than the pivot

    # Recursively sort the left and right parts and combine them
    return quick_sort(left) + middle + quick_sort(right)

# Example array to sort
a = [3, 7, 9, 33, 7, 11, 46, 23]
sorted_array = quick_sort(a)
print(sorted_array)
