def calculate_sqrt(number, tolerance=1e-7):
    """Calculates the square root of a number using the Newton-Raphson method."""
    
    # 1. Handle edge cases
    if number < 0:
        raise ValueError("Cannot calculate square root of a negative number")
    if number == 0 or number == 1:
        return float(number)

    # 2. Set up initial variables
    guess = number / 2.0
    iteration = 1
    
    print(f"--- Calculating sqrt({number}) ---")
    print(f"Initial guess: {guess}")

    # 3. Loop to refine the guess
    while True:
        # The Newton-Raphson formula
        next_guess = 0.5 * (guess + (number / guess))
        
        # Show the work
        print(f"Iteration {iteration}: {next_guess:.7f}")
        
        # Check if we are within our accepted tolerance
        if abs(guess - next_guess) < tolerance:
            print("Tolerance reached. Stopping.")
            break
            
        # Update the guess for the next loop
        guess = next_guess
        iteration += 1

    # 4. Return the final answer
    return next_guess

# --- Let's test it out! ---
if __name__ == "__main__":
    target_number = 25
    result = calculate_sqrt(target_number)
    print(f"Final Answer: {result}\n")
    
    # Let's try a non-perfect square
    target_number = 2
    result = calculate_sqrt(target_number)
    print(f"Final Answer: {result}")
