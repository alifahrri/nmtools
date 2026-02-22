import math

def minimize_bounded(objective_function, lower_bound, upper_bound, tolerance=1e-5):
    """Finds the local minimum of a function within a strict interval [a, b]."""
    
    # 1. Set the Golden Ratio constant
    # We use the exact mathematical value of (sqrt(5) - 1) / 2, which is ~0.618
    R = (math.sqrt(5) - 1) / 2.0 
    
    a = float(lower_bound)
    b = float(upper_bound)
    
    # 2. Create two test points inside the boundaries
    distance = R * (b - a)
    x1 = b - distance
    x2 = a + distance
    
    f1 = objective_function(x1)
    f2 = objective_function(x2)
    
    iteration = 1
    print("--- Starting Bounded Search ---")
    print(f"Initial bounds: [{a:.5f}, {b:.5f}] (Width: {b - a:.5f})")

    # 3. Loop to narrow the boundaries
    while abs(b - a) > tolerance:
        if f1 < f2:
            # The minimum is between 'a' and 'x2'. Bring the right bound inwards.
            b = x2
            x2 = x1
            f2 = f1
            
            # Calculate new left test point
            distance = R * (b - a)
            x1 = b - distance
            f1 = objective_function(x1)
        else:
            # The minimum is between 'x1' and 'b'. Bring the left bound inwards.
            a = x1
            x1 = x2
            f1 = f2
            
            # Calculate new right test point
            distance = R * (b - a)
            x2 = a + distance
            f2 = objective_function(x2)
            
        print(f"Iteration {iteration:2}: Bounds [{a:.5f}, {b:.5f}] (Width: {b - a:.5f})")
        iteration += 1

    # 4. Return the midpoint of the final tiny interval
    final_x = (a + b) / 2.0
    return final_x

# --- Let's test it out! ---
if __name__ == "__main__":
    # Define a test function with a known minimum
    # f(x) = (x - 3)^2 + 2 
    # Based on the math, the lowest point (minimum) is exactly at x = 3
    def test_function(x):
        return (x - 3)**2 + 2
        
    # We will tell the algorithm to search anywhere between 0 and 10
    best_x = minimize_bounded(test_function, 0, 10)
    
    print(f"\nOptimization Complete.")
    print(f"Optimal input (x): {best_x:.7f}")
    print(f"Minimum output (y): {test_function(best_x):.7f}")
