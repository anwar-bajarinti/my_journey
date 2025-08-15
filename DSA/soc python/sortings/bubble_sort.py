def bubble_sort(arr):
    n = len(arr)
    
    for i in range(n - 1):  # Number of passes
        swapped = False
        for j in range(n - 1 - i):  # Compare adjacent elements
            if arr[j] > arr[j + 1]:
                # Swap if elements are in the wrong order
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        
        # If no swaps were made, the array is already sorted
        if not swapped:
            break

# Example usage
arr = [64, 34, 25, 12, 22, 11, 90]
print("Original array:", arr)

bubble_sort(arr)
print("Sorted array:", arr)
