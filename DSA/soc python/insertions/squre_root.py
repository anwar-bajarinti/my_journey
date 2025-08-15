def square_root(number):
    if number < 0:
        raise ValueError("Square root of negative numbers is not supported.")

    if number == 0 or number == 1:
        return number

    left, right = 0, number
    result = 0

    while left <= right:
        mid = (left + right) // 2
        square = mid * mid

        if square == number:
            return mid  # Found exact square root
        elif square < number:
            result = mid  # Store the closest valid mid
            left = mid + 1  # Search in the right half
        else:
            right = mid - 1  # Search in the left half

    return result  # Return the integer part of the square root

# Example usage
num = int(input("Enter a number: "))
sqrt_value = square_root(num)
print(f"The integer part of the square root of {num} is: {sqrt_value}")
