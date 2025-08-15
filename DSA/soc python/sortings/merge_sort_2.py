def merge_sorted_arrays(arr1, arr2):
    i = j = 0
    result = []

    # Merge while both arrays have elements
    while i < len(arr1) and j < len(arr2):
        if arr1[i] <= arr2[j]:
            result.append(arr1[i])
            i += 1
        else:
            result.append(arr2[j])
            j += 1

    # Append remaining elements
    result.extend(arr1[i:])
    result.extend(arr2[j:])

    return result

# Example usage
arr1 = [1, 3, 5, 7]
arr2 = [2, 4, 6, 8, 10]

merged_array = merge_sorted_arrays(arr1, arr2)
print("Merged Array:", merged_array)
