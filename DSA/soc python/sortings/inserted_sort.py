def insertion_sort(a):
    n = len(a)
    for i in range(1, n):
        key = a[i]  # The element to be placed at the correct position
        j = i - 1

        # Move elements of a[0...i-1] that are greater than key to one position ahead
        while j >= 0 and a[j] > key:
            a[j + 1] = a[j]  # Shift element to the right
            j -= 1

        a[j + 1] = key  # Place the key at its correct position

    return a

# Example usage
arr = [12, 11, 13, 5, 6]
sorted_arr = insertion_sort(arr)
print("Sorted array:", sorted_arr)
