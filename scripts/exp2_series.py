import math

# --- 1. Maclaurin Series (Dynamic Taylor) ---
def exp2_maclaurin(x, num_terms=15):
    """Computes 2^x dynamically building the Maclaurin series for e^(x*ln(2))"""
    k = round(x)
    r = x - k
    
    LN2 = 0.6931471805599453
    z = r * LN2
    
    result = 1.0
    current_term = 1.0
    
    for i in range(1, num_terms):
        current_term = current_term * z / i
        result += current_term
        
    return math.ldexp(result, k)


# --- 2. Padé Approximant (Rational Series) ---
def exp2_pade(x):
    """Computes 2^x using a fast-converging Degree-3 Rational Function"""
    k = round(x)
    r = x - k
    
    LN2 = 0.6931471805599453
    z = r * LN2
    
    z2 = z * z
    z3 = z2 * z
    
    # Numerator P(z)
    P = 1.0 + (z / 2.0) + (z2 / 10.0) + (z3 / 120.0)
    # Denominator Q(z) - Identical coefficients, alternating signs
    Q = 1.0 - (z / 2.0) + (z2 / 10.0) - (z3 / 120.0)
    
    return math.ldexp(P / Q, k)


# --- 3. Square Root Bisection (Zero Polynomials) ---
def exp2_bisection(x, precision_bits=52):
    """Computes 2^x by extracting binary fraction bits via square roots"""
    k = math.floor(x)
    r = x - k
    
    result = 1.0
    current_sqrt = math.sqrt(2.0)
    
    for _ in range(precision_bits):
        r *= 2.0
        
        if r >= 1.0:
            result *= current_sqrt
            r -= 1.0
            
        if r == 0.0:
            break
            
        current_sqrt = math.sqrt(current_sqrt)
        
    return math.ldexp(result, k)


# --- BENCHMARK AND COMPARISON ---
if __name__ == "__main__":
    # A mix of integers, simple fractions, and messy decimals (positive and negative)
    test_points = [0.0, 1.0, -1.0, 0.5, -0.4, 3.14159265, -7.8, 10.25]

    print(f"{'x':<10} | {'math.exp2(x)':<18} | {'Method':<12} | {'Approximation':<18} | {'Abs Error':<10}")
    print("-" * 75)

    for x in test_points:
        std_val = math.exp2(x)
        
        # Calculate approximations
        mac_val = exp2_maclaurin(x)
        pad_val = exp2_pade(x)
        bis_val = exp2_bisection(x)
        
        # Calculate errors
        mac_err = abs(std_val - mac_val)
        pad_err = abs(std_val - pad_val)
        bis_err = abs(std_val - bis_val)
        
        # Print block for this specific x
        print(f"{x:<10.5f} | {std_val:<18.10g} | {'Maclaurin':<12} | {mac_val:<18.10g} | {mac_err:.2e}")
        print(f"{'':<10} | {'':<18} | {'Pade (Deg 3)':<12} | {pad_val:<18.10g} | {pad_err:.2e}")
        print(f"{'':<10} | {'':<18} | {'Bisection':<12} | {bis_val:<18.10g} | {bis_err:.2e}")
        print("-" * 75)
