def insertion_sort(a):
    n = len(a)
    print("Original array:", a)
    print("-" * 40)

    for i in range(1, n):
        key = a[i]  # The element to be inserted at the correct position
        j = i - 1

        print(f"Inserting {key}...")

        # Move elements of a[0...i-1] that are greater than key to one position ahead
        while j >= 0 and a[j] > key:
            a[j + 1] = a[j]  # Shift element to the right
            j -= 1

            # Display the array after each shift
            print(f"Shifted {a[j+1]}: {a}")

        # Insert the key at the correct position
        a[j + 1] = key

        # Display the array after inserting the key
        print(f"Inserted {key}: {a}")
        print("-" * 40)
    
    print("Sorted array:", a)

# Example usage
arr = [12, 11, 13, 5, 6]
insertion_sort(arr)
