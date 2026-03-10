import math

def log_approx(x, num_terms=10):
    """
    Computes ln(x) (natural logarithm) using the fast-converging odd series.
    """
    if x <= 0:
        raise ValueError("log(x) is undefined for zero or negative numbers.")
        
    # Constant for ln(2), which we need to reconstruct the final answer
    LN2 = 0.6931471805599453
    
    # 1. Hardware Range Reduction
    # Get the mantissa (m) in range [0.5, 1.0) and exponent (e)
    m, e = math.frexp(x)
    
    # Shift m to [1.0, 2.0) to keep it closer to 1.0
    m = m * 2.0
    e = e - 1
    
    # 2. The substitution trick: z = (x-1)/(x+1)
    z = (m - 1.0) / (m + 1.0)
    z_squared = z * z
    
    # 3. Compute the series: 2 * (z + z^3/3 + z^5/5 + z^7/7 ...)
    series_sum = 0.0
    current_term = z  # Starts at z^1
    
    for i in range(1, num_terms + 1):
        denominator = (2 * i) - 1  # 1, 3, 5, 7...
        series_sum += current_term / denominator
        current_term *= z_squared  # Step up by z^2 for the next loop
        
    ln_m = 2.0 * series_sum
    
    # 4. Reconstruct the final answer: ln(x) = ln(m) + e * ln(2)
    return ln_m + (e * LN2)


# --- Test Cases ---
if __name__ == "__main__":
    # Test a wide variety of inputs
    test_points = [
        0.001, 
        0.5, 
        1.0, 
        math.e,  # ~2.71828...
        10.0, 
        100.0, 
        1000000.0
    ]

    print(f"{'Input x':<12} | {'Standard math.log':<22} | {'Series Approx':<22} | {'Abs Error':<12}")
    print("-" * 80)

    max_error = 0
    for x in test_points:
        std_val = math.log(x)
        # Using just 7 terms to show how incredibly fast this series converges
        my_val = log_approx(x, num_terms=7) 
        
        error = abs(std_val - my_val)
        max_error = max(max_error, error)
        
        print(f"{x:<12.6g} | {std_val:<22.15f} | {my_val:<22.15f} | {error:.2e}")

    print("-" * 80)
    print(f"Maximum Observed Error (7 terms): {max_error:.2e}")